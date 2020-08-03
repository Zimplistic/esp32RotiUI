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
#include "modules.h"

LUALIB_API const LUA_REG_TYPE ui_map[];
LUALIB_API int luaopen_ui( lua_State *L );

#endif //CONFIG_LUA_RTOS_LUA_USE_UI
