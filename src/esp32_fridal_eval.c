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

#include "roti_main_screen.h"

static const char *TAG = "ui";

static lv_obj_t * main_screen;

static void lua_event_call(char * function_name)
{
    /*Send event to lua engine*/
    lua_State *L = get_lua_state();
    if (L == NULL)
    {
        ESP_LOGE(TAG, "lua_State is null");
        return;
    }
    /*Call lua function*/
    lua_getglobal(L, function_name);
    if (lua_pcall(L, 0, 0, 0) != 0)
    {
        ESP_LOGE(TAG, "Error %s", lua_tostring(L, -1));
        lua_pop(L, -1);
    }
}

/*cb functions for main screen*/
static void roti_scrn_btn_minus(lv_obj_t *btn, lv_event_t evnt)
{
    if (evnt == LV_EVENT_RELEASED)
    {
        ESP_LOGI(TAG, "minus pressed, ent: %d", evnt);
        lua_event_call("roti_main_minus_btn");
    }
}

static void roti_scrn_btn_plus(lv_obj_t *btn, lv_event_t evnt)
{
    if (evnt == LV_EVENT_RELEASED)
    {
        ESP_LOGI(TAG, "plus pressed, ent: %d", evnt);
        lua_event_call("roti_main_plus_btn");
    }
}

static void roti_scrn_btn_play(lv_obj_t *btn, lv_event_t evnt)
{
    if (evnt == LV_EVENT_RELEASED)
    {
        ESP_LOGI(TAG, "play pressed, ent: %d", evnt);
//        lua_event_call("roti_main_play_btn");/*TODO: uncomment this code*/
    }
}

lv_event_cb_t roti_main_screen_btn_minus_cb = roti_scrn_btn_minus;
lv_event_cb_t roti_main_screen_btn_plus_cb = roti_scrn_btn_plus;
lv_event_cb_t roti_main_screen_btn_play_cb = roti_scrn_btn_play;
extern lv_obj_t *roti_main_scr_label_NoRoti;

static int uiTest(void)
{
    main_screen = lv_disp_get_scr_act(NULL);
    roti_main_screen_create(main_screen);
    return 0;
}

static int roti_main_no_roti_lable_update(lua_State *L)
{
    uint16_t no_roti = luaL_checkinteger(L, 1);
    if(roti_main_scr_label_NoRoti != NULL)
    {
        char buf[3];
        sprintf(buf, "%d", no_roti);
        lv_label_set_text(roti_main_scr_label_NoRoti, buf);
    }
    return 0;
}

const LUA_REG_TYPE ui_map[] = {
        { LSTRKEY( "test"  ),            LFUNCVAL( uiTest ) },
        { LSTRKEY( "no_roti_lbl"  ),            LFUNCVAL( roti_main_no_roti_lable_update ) },
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
