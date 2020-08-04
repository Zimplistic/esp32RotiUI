#ifndef ROTI_MAIN_SCREEN_H
#define ROTI_MAIN_SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

/**********************
 *      INCLUDES
 **********************/

#include "lvgl.h"

/**********************
 *       WIDGETS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void roti_main_screen_create(lv_obj_t *parent);

/*Cb function to comunicate with Roti App*/
extern lv_event_cb_t roti_main_screen_btn_minus_cb;
extern lv_event_cb_t roti_main_screen_btn_plus_cb;
extern lv_event_cb_t roti_main_screen_btn_play_cb;

/*References to the screen elements*/
extern lv_obj_t *roti_main_scr_label_NoRoti;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ROTI_MAIN_SCREEN_H*/
