#include "roti_main_screen.h"

/**********************
 *       WIDGETS
 **********************/
lv_obj_t *roti_main_scr_btn_Minus = NULL;
lv_obj_t *roti_main_scr_btn_Plus = NULL;
lv_obj_t *roti_main_scr_label_NoRoti = NULL;


/**********************
 *  STATIC VARIABLES
 **********************/
static lv_style_t style_screen;
static lv_style_t style0_cook;
static lv_style_t style0_button_1;
static lv_style_t style0_button_2;
static lv_style_t style0_label_1;
static lv_style_t style0_button_3;
static lv_style_t style0_label_2;
static lv_style_t style0_label_3;
static lv_style_t style0_label_4;

LV_IMG_DECLARE(menu);
LV_IMG_DECLARE(recipe);
LV_IMG_DECLARE(play);
LV_IMG_DECLARE(artboard);
LV_IMG_DECLARE(minus);
LV_IMG_DECLARE(roast);
LV_IMG_DECLARE(oil);
LV_IMG_DECLARE(thickness);
LV_IMG_DECLARE(plus);

LV_FONT_DECLARE(montserrat_semibold_50);
LV_FONT_DECLARE(poppins_medium_12);
LV_FONT_DECLARE(montserrat_semibold_24);

void roti_main_screen_create(lv_obj_t *parent)
{
	lv_style_copy(&style_screen, &lv_style_scr);
	style_screen.body.main_color = lv_color_hex(0x000000);
	style_screen.body.grad_color = lv_color_hex(0x000000);
	lv_obj_set_style(parent, &style_screen);

#ifdef LV_USE_BTN
	lv_style_copy(&style0_cook, &lv_style_btn_rel);
	style0_cook.body.main_color = lv_color_hex(0x363636);
	style0_cook.body.grad_color = lv_color_hex(0x363636);
	style0_cook.body.radius = 2;
	style0_cook.body.border.color = lv_color_hex(0x000000);
	style0_cook.body.border.opa = 255;
	style0_cook.body.padding.top = 20;

	lv_obj_t *cook = lv_btn_create(parent, NULL);
	lv_obj_set_pos(cook, 207 * 1.5, 181 * 1.3);
	lv_obj_set_size(cook, 94 * 1.5 , 38 * 1.3);
	lv_btn_set_style(cook, LV_BTN_STYLE_REL, &style0_cook);
#endif // LV_USE_BTN

#ifdef LV_USE_IMG
	lv_obj_t *image_1 = lv_img_create(cook, NULL);
	lv_obj_set_pos(image_1, 32 * 1.5 , 4 * 1.3);
	lv_obj_set_size(image_1, 30 * 1.5, 30 * 1.3);
	lv_img_set_src(image_1, &oil);
#endif // LV_USE_IMG

#ifdef LV_USE_BTN
	lv_style_copy(&style0_button_1, &lv_style_btn_rel);
	style0_button_1.body.main_color = lv_color_hex(0x363636);
	style0_button_1.body.grad_color = lv_color_hex(0x363636);
	style0_button_1.body.radius = 2;
	style0_button_1.body.border.color = lv_color_hex(0x000000);

	lv_obj_t *button_1 = lv_btn_create(parent, NULL);
	lv_obj_set_pos(button_1, 113 * 1.5, 181 * 1.3);
	lv_obj_set_size(button_1, 94 * 1.5, 38 * 1.3);
	lv_btn_set_style(button_1, LV_BTN_STYLE_REL, &style0_button_1);
#endif // LV_USE_BTN

#ifdef LV_USE_IMG
	lv_obj_t *image_2 = lv_img_create(button_1, NULL);
	lv_obj_set_pos(image_2, 32 * 1.5, 4 * 1.3);
	lv_obj_set_size(image_2, 30 * 1.5, 30 * 1.3);
	lv_img_set_src(image_2, &roast);
#endif // LV_USE_IMG

#ifdef LV_USE_BTN
	lv_style_copy(&style0_button_2, &lv_style_btn_rel);
	style0_button_2.body.main_color = lv_color_hex(0x363636);
	style0_button_2.body.grad_color = lv_color_hex(0x363636);
	style0_button_2.body.radius = 2;
	style0_button_2.body.border.color = lv_color_hex(0x000000);

	lv_obj_t *button_2 = lv_btn_create(parent, NULL);
	lv_obj_set_pos(button_2, 19 * 1.5, 181 * 1.3);
	lv_obj_set_size(button_2, 94 * 1.5, 38 * 1.3);
	lv_btn_set_style(button_2, LV_BTN_STYLE_REL, &style0_button_2);
#endif // LV_USE_BTN

#ifdef LV_USE_IMG
//	lv_obj_t *image_3 = lv_img_create(button_2, NULL);
//	lv_obj_set_pos(image_3, 47, -6);
//	lv_obj_set_size(image_3, 0, 0);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
//	lv_obj_t *image_5 = lv_img_create(button_2, NULL);
//	lv_obj_set_pos(image_5, 47, 4);
//	lv_obj_set_size(image_5, 0, 0);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	lv_obj_t *image_6 = lv_img_create(button_2, NULL);
	lv_obj_set_pos(image_6, 32 * 1.5, 4 * 1.3);
	lv_obj_set_size(image_6, 50 * 1.5, 50 * 1.3);
	lv_img_set_src(image_6, &thickness);
#endif // LV_USE_IMG

#ifdef LV_USE_IMGBTN
	lv_obj_t *image_button_1 = lv_imgbtn_create(parent, NULL);
	lv_obj_set_pos(image_button_1, 229 * 1.5, 87 * 1.3);
	lv_obj_set_size(image_button_1, 0, 0);
	lv_imgbtn_set_state(image_button_1, LV_BTN_STATE_REL);
	lv_imgbtn_set_toggle(image_button_1, false);
	lv_imgbtn_set_src(image_button_1, LV_BTN_STATE_REL, &artboard);
#endif // LV_USE_IMGBTN

#ifdef LV_USE_IMGBTN
	lv_obj_t *image_button_2 = lv_imgbtn_create(parent, NULL);
	lv_obj_set_pos(image_button_2, 18 * 1.5, 19 * 1.3);
	lv_obj_set_size(image_button_2, 38 * 1.5, 38 * 1.3);
	lv_imgbtn_set_state(image_button_2, LV_BTN_STATE_REL);
	lv_imgbtn_set_toggle(image_button_2, false);
	lv_imgbtn_set_src(image_button_2, LV_BTN_STATE_REL, &menu);
#endif // LV_USE_IMGBTN

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_1, &lv_style_transp);
	style0_label_1.text.color = lv_color_hex(0xffffff);
	style0_label_1.text.sel_color = lv_color_hex(0x5596d8);
	style0_label_1.text.font = &montserrat_semibold_50;
	style0_label_1.text.letter_space = 0;
	style0_label_1.text.line_space = 2;
	style0_label_1.text.opa = 255;

	lv_obj_t *label_1 = lv_label_create(parent, NULL);
	lv_label_set_text(label_1, "10");
	lv_label_set_align(label_1, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(label_1, 131 * 1.5, 70 * 1.3);
	lv_obj_set_size(label_1, 53 * 1.5, 52 * 1.3);
	lv_label_set_style(label_1, LV_LABEL_STYLE_MAIN, &style0_label_1);
	/*Adding reference to update the label*/
	roti_main_scr_label_NoRoti = label_1;
#endif // LV_USE_LABEL

#ifdef LV_USE_BTN
	lv_style_copy(&style0_button_3, &lv_style_btn_rel);
	style0_button_3.body.main_color = lv_color_hex(0x000000);
	style0_button_3.body.grad_color = lv_color_hex(0x000000);
	style0_button_3.body.radius = 2;
	style0_button_3.body.border.color = lv_color_hex(0x363636);
	style0_button_3.body.border.opa = 255;

	lv_obj_t *button_3 = lv_btn_create(parent, NULL);
	lv_obj_set_pos(button_3, 70 * 1.5, 19 * 1.3);
	lv_obj_set_size(button_3, 230 * 1.5, 38 * 1.3);
	lv_btn_set_style(button_3, LV_BTN_STYLE_REL, &style0_button_3);
#endif // LV_USE_BTN

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_2, &lv_style_transp);
	style0_label_2.text.color = lv_color_hex(0xffffff);
	style0_label_2.text.sel_color = lv_color_hex(0x5596d8);
	style0_label_2.text.font = &poppins_medium_12;
	style0_label_2.text.letter_space = 0;
	style0_label_2.text.line_space = 2;
	style0_label_2.text.opa = 255;

	lv_obj_t *label_2 = lv_label_create(button_3, NULL);
	lv_label_set_text(label_2, "Roti, Aashirwad Multigrain");
	lv_label_set_align(label_2, LV_LABEL_ALIGN_CENTER);
	lv_label_set_recolor(label_2, true);
	lv_obj_set_pos(label_2, 35 * 1.5, 11 * 1.3);
	lv_obj_set_size(label_2, 161 * 1.5, 16 * 1.3);
	lv_label_set_style(label_2, LV_LABEL_STYLE_MAIN, &style0_label_2);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_3, &lv_style_transp);
	style0_label_3.text.color = lv_color_hex(0xffffff);
	style0_label_3.text.sel_color = lv_color_hex(0x5596d8);
	style0_label_3.text.font = &poppins_medium_12;
	style0_label_3.text.letter_space = 0;
	style0_label_3.text.line_space = 2;
	style0_label_3.text.opa = 255;

	lv_obj_t *label_3 = lv_label_create(parent, NULL);
	lv_label_set_text(label_3, "LETS COOK");
	lv_obj_set_pos(label_3, 125 * 1.5, 124 * 1.3);
	lv_obj_set_size(label_3, 65 * 1.5, 16 * 1.3);
	lv_label_set_style(label_3, LV_LABEL_STYLE_MAIN, &style0_label_3);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_4, &lv_style_transp);
	style0_label_4.text.color = lv_color_hex(0xffffff);
	style0_label_4.text.sel_color = lv_color_hex(0x5596d8);
	style0_label_4.text.font = &montserrat_semibold_24;
	style0_label_4.text.letter_space = 0;
	style0_label_4.text.line_space = 2;
	style0_label_4.text.opa = 255;

	lv_obj_t *label_4 = lv_label_create(parent, NULL);
	lv_label_set_text(label_4, "03:00");
	lv_label_set_align(label_4, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_pos(label_4, 124 * 1.5, 143 * 1.3);
	lv_obj_set_size(label_4, 68 * 1.5, 26 * 1.3);
	lv_label_set_style(label_4, LV_LABEL_STYLE_MAIN, &style0_label_4);
#endif // LV_USE_LABEL

#ifdef LV_USE_IMGBTN
	lv_obj_t *image_button_3 = lv_imgbtn_create(parent, NULL);
	lv_obj_set_pos(image_button_3, 19 * 1.5, 73 * 1.3);
	lv_obj_set_size(image_button_3, 40 , 40 );
	lv_imgbtn_set_state(image_button_3, LV_BTN_STATE_REL);
	lv_imgbtn_set_toggle(image_button_3, false);
	lv_imgbtn_set_src(image_button_3, LV_BTN_STATE_REL, &plus);
	lv_imgbtn_set_src(image_button_3, LV_BTN_STATE_PR, &plus);
	/*Adding for communicating with UI App*/
	lv_obj_set_event_cb(image_button_3, roti_main_screen_btn_plus_cb);
	roti_main_scr_btn_Plus = image_button_3;
#endif // LV_USE_IMGBTN

#ifdef LV_USE_IMGBTN
	lv_obj_t *image_button_4 = lv_imgbtn_create(parent, NULL);
	lv_obj_set_pos(image_button_4, 19 * 1.5, 125 * 1.3);
	lv_obj_set_size(image_button_4, 40 , 40 );
	lv_imgbtn_set_state(image_button_4, LV_BTN_STATE_REL);
	lv_imgbtn_set_toggle(image_button_4, false);
	lv_imgbtn_set_src(image_button_4, LV_BTN_STATE_REL, &minus);
	lv_imgbtn_set_src(image_button_4, LV_BTN_STATE_PR, &minus);
	/*Adding for communicating with UI App*/
	lv_obj_set_event_cb(image_button_4, roti_main_screen_btn_minus_cb);
	roti_main_scr_btn_Minus = image_button_4;
#endif // LV_USE_IMGBTN

#ifdef LV_USE_IMG
	lv_obj_t *image_4 = lv_img_create(parent, NULL);
	lv_obj_set_pos(image_4, 278 * 1.5, 21 * 1.3);
	lv_obj_set_size(image_4, 0, 0);
	lv_img_set_src(image_4, &recipe);
#endif // LV_USE_IMG

#ifdef LV_USE_IMGBTN
	lv_obj_t *image_button_5 = lv_imgbtn_create(parent, NULL);
	lv_obj_set_pos(image_button_5, 217 * 1.5, 81 * 1.3);
	lv_obj_set_size(image_button_5, 70, 70);
	lv_imgbtn_set_state(image_button_5, LV_BTN_STATE_REL);
	lv_imgbtn_set_toggle(image_button_5, false);
	lv_imgbtn_set_src(image_button_5, LV_BTN_STATE_REL, &play);
	lv_imgbtn_set_src(image_button_5, LV_BTN_STATE_PR, &play);
	/*Adding for communicating with UI App*/
	lv_obj_set_event_cb(image_button_5, roti_main_screen_btn_play_cb);
#endif // LV_USE_IMGBTN

}
