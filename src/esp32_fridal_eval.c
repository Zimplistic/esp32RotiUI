/*
 * (C) Copyright 2020
 * Zimplistic Private Limited
 * Sicris Rey Embay, sicris@zimplistic.com
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "lcd.h"
#include "touchscreen.h"
#include "string.h"
#include "lvgl.h"

#include <sys/debug.h>
#include <sys/panic.h>
#include <sys/mount.h>

#include <drivers/gpio.h>

#include <pthread.h>

static const char *TAG = "main";

#define IRAM_BSS_ATTR

#define BUFFER_SZ_IN_PIXEL    (CONFIG_LCD_PARALLEL_LINE_COUNT * CONFIG_LCD_H_RES)
IRAM_BSS_ATTR static rgb_t pixel[BUFFER_SZ_IN_PIXEL];

IRAM_BSS_ATTR static lv_disp_buf_t disp_buf;
IRAM_BSS_ATTR static lv_disp_drv_t disp_drv;
IRAM_BSS_ATTR static TaskHandle_t xTaskHandleLvglWorker;
IRAM_BSS_ATTR static TaskHandle_t xTaskHandleLvgl;
IRAM_BSS_ATTR static xQueueHandle xLvglWorkerQueue;

typedef struct {
    lv_disp_drv_t * disp_drv;
    lv_area_t * area;
    lv_color_t * color_p;
} gfx_flush_req_t;


static void _app_gfx_flush(
        lv_disp_drv_t  * disp_drv,
        const lv_area_t * area,
        lv_color_t * color_p)
{
    gfx_flush_req_t req;
    req.disp_drv = disp_drv;
    req.area = (lv_area_t *)area;
    req.color_p = color_p;
    if(pdPASS != xQueueSend(xLvglWorkerQueue, (void*)&req, (TickType_t)0)) {
        ESP_LOGE(TAG, "Failed post to LVGL worker queue!\n");
    }
}

static void *_lvgl_workTask(void *pvParam) {
    gfx_flush_req_t req;
    esp_err_t ret = ESP_OK;
    
    ESP_LOGI(TAG, "LVGL worker task running..\n");

    while(1) {
        if(pdPASS == xQueueReceive(xLvglWorkerQueue, &req, portMAX_DELAY)) {
            ret = lcd_writePixels(req.area->x1, req.area->x2,
                        req.area->y1, req.area->y2, req.disp_drv->buffer->buf_act, req.disp_drv->buffer->size);
            if(ESP_OK != ret) {
                ESP_LOGE(TAG, "%s:%d: Error%d", __FUNCTION__, __LINE__, ret);
            }
            lv_disp_flush_ready(req.disp_drv);
        }
    }
    return NULL;
}

static pthread_t lua_lvgl_thread;
static pthread_t lua_lvgl_worker_thread;
static lv_obj_t * main_screen;
static lv_obj_t * slider_label;

static void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        snprintf(buf, 4, "%u", lv_slider_get_value(slider));
        lv_label_set_text(slider_label, buf);
    }
}

IRAM_ATTR static void uiTest(void)
{
    lv_obj_t * label;
    lv_obj_t * slider;
    main_screen = lv_disp_get_scr_act(NULL);

    label = lv_label_create(main_screen, NULL);
    lv_label_set_recolor(label, true);
    lv_label_set_text(label, "Hello World!\nTest #ff0000 red# #00ff00 green# #0000ff blue#\n");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    slider = lv_slider_create(main_screen, NULL);
    lv_obj_set_width(slider, LV_DPI * 2);
    lv_obj_align(slider, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_event_cb(slider, slider_event_cb);
    lv_slider_set_range(slider, 0, 100);   

    slider_label = lv_label_create(main_screen, NULL);
    lv_label_set_text(slider_label, "0");
    lv_obj_set_auto_realign(slider_label, true);
    lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);    
}


IRAM_ATTR static void *_lvgl_mainTask(void *pvParam)
{
    uiTest();
    lcd_set_bl_state(1);
    ESP_LOGI(TAG, "LVGL main task running..\n");
    while(1) { 
        usleep(portTICK_RATE_MS * 1000);
        lv_tick_inc(portTICK_RATE_MS);
        lv_task_handler();
    }
    return NULL;
}

static bool _touch_ft6336_cb(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    int16_t x;
    int16_t y;

    if(ESP_OK == touchscreen_getCoord(0, &x, &y)) {
        if((x != -1) && (y != -1)) {
            /* hack: rotate to landscape */
            data->point.x = LV_HOR_RES_MAX - y;
            data->point.y = x;
            data->state = LV_INDEV_STATE_PR;
        } else {
            data->state = LV_INDEV_STATE_REL;
        }
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    return false;
}

void _lvgl_main_thread_init()
{
    // Create and run a pthread for the Lua interpreter
    pthread_attr_t attr;
    struct sched_param sched;
    int res;

    debug_free_mem_begin(lua_lvgl_thread);

    // Init thread attributes
    pthread_attr_init(&attr);

    // Set stack size
    pthread_attr_setstacksize(&attr, 8192);

    // Set priority
    sched.sched_priority = tskIDLE_PRIORITY + 1;
    pthread_attr_setschedparam(&attr, &sched);

    // Set CPU
    cpu_set_t cpu_set = CPU_INITIALIZER;

    CPU_SET(CONFIG_LUA_RTOS_LUA_TASK_CPU, &cpu_set);

    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_set);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create thread
    res = pthread_create(&lua_lvgl_thread, &attr, _lvgl_mainTask, NULL);
    if (res) {
        panic("Cannot start lua");
    }

    pthread_setname_np(lua_lvgl_thread, "lua_lvgl");
    debug_free_mem_end(lua_lvgl_thread, NULL);
}

void _lvgl_worker_thread_init()
{
    // Create and run a pthread for the Lua interpreter
    pthread_attr_t attr;
    struct sched_param sched;
    int res;

    debug_free_mem_begin(lua_lvgl_worker_thread);

    // Init thread attributes
    pthread_attr_init(&attr);

    // Set stack size
    pthread_attr_setstacksize(&attr, 2048);

    // Set priority
    sched.sched_priority = tskIDLE_PRIORITY + 2;
    pthread_attr_setschedparam(&attr, &sched);

    // Set CPU
    cpu_set_t cpu_set = CPU_INITIALIZER;

    CPU_SET(CONFIG_LUA_RTOS_LUA_TASK_CPU, &cpu_set);

    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_set);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create thread
    res = pthread_create(&lua_lvgl_worker_thread, &attr, _lvgl_workTask, NULL);
    if (res) {
        panic("Cannot start lua");
    }

    pthread_setname_np(lua_lvgl_worker_thread, "lua_lvgl_worker");
    debug_free_mem_end(lua_lvgl_worker_thread, NULL);
}

void esp32_fridal_test()
{
    lv_indev_drv_t indev_drv;

    /* Initialize LCD */
    ESP_ERROR_CHECK(lcd_init());

    /* Initialize Touch */
    ESP_ERROR_CHECK(touchscreen_init());

    /* Initialize LVGL */
    lv_init();
    lv_disp_buf_init(&disp_buf, (void *)(&pixel[0]), (void *)0, BUFFER_SZ_IN_PIXEL);
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = _app_gfx_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);
    /* register touchscreen */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = _touch_ft6336_cb;
    lv_indev_drv_register(&indev_drv);

    /*Using thread*/
    _lvgl_main_thread_init();

    /* Create worker task for Flushing */
    xLvglWorkerQueue = xQueueCreate(1, sizeof(gfx_flush_req_t));
    if(!xLvglWorkerQueue) {
        ESP_LOGE(TAG, "%s:%d: Failed to create LVGL worker Queue!\n", __FUNCTION__, __LINE__);
        return;
    }
    _lvgl_worker_thread_init();

    ESP_LOGI(TAG, "Goodbye app_main()\n");
}
