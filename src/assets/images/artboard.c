#include "lvgl.h"
#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_ARTBOARD
#define LV_ATTRIBUTE_IMG_ARTBOARD
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_ARTBOARD uint8_t artboard_map[] = {
	/*Pixel format: Red: 8 bit, Green: 8 bit, Blue: 8 bit*/
};

const lv_img_dsc_t artboard = {
  .header.always_zero = 0,
  .header.w = 0,
  .header.h = 0,
  .data_size = 0,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = artboard_map
};
