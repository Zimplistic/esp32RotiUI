/*
 * (C) Copyright 2020
 * Zimplistic Private Limited
 * Toan Dang, toan.dang@zimplistic.com
 */

#include "sdkconfig.h"

#if CONFIG_LUA_RTOS_LUA_USE_UI

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
#include "luartos.h"
#include "lua.h"
#include "lauxlib.h"

static const char *TAG = "ui";

static lv_obj_t * main_screen;
static lv_obj_t * slider_label;

static void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        snprintf(buf, 4, "%u", lv_slider_get_value(slider));
        lv_label_set_text(slider_label, buf);

        /*Send event to lua engine*/
        lua_State *L = get_lua_state();
        if (L == NULL)
        {
            ESP_LOGE(TAG, "lua_State is null");
            return;
        }
        /*Call lua function*/
        lua_getglobal(L, "ui_cb_test");
        if (lua_pcall(L, 0, 0, 0) != 0)
        {
            ESP_LOGE(TAG, "Error calling callback Lua function: %s", lua_tostring(L, -1));
            lua_pop(L, -1);
        }
    }
}

static int uiTest(void)
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
    return 0;
}

const LUA_REG_TYPE ui_map[] = {
        { LSTRKEY( "test"  ),            LFUNCVAL( uiTest ) },
        { LNILKEY, LNILVAL }
};

//static const LUA_REG_TYPE ui_trans_map[] = {
//    { LSTRKEY( "__metatable" ),        LROVAL  ( ui_trans_map ) },
//    { LSTRKEY( "__index"     ),        LROVAL  ( ui_trans_map ) },
//    { LSTRKEY( "__gc"        ),        LFUNCVAL ( ui_trans_gc ) },
//    { LNILKEY, LNILVAL }
//};

LUALIB_API int luaopen_ui( lua_State *L ) {
//    luaL_newmetarotable(L,"lvgl.trans", (void *)lvgl_trans_map);
    return 0;
}

#endif //CONFIG_LUA_RTOS_LUA_USE_UI
