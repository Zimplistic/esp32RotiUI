#include "lvgl.h"
#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_RECIPE
#define LV_ATTRIBUTE_IMG_RECIPE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_RECIPE uint8_t recipe_map[] = {
	/*Pixel format: Red: 8 bit, Green: 8 bit, Blue: 8 bit*/
};

const lv_img_dsc_t recipe = {
  .header.always_zero = 0,
  .header.w = 0,
  .header.h = 0,
  .data_size = 0,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = recipe_map
};
