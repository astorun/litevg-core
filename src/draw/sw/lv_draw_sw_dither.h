/**
 * @file lv_draw_sw_dither.h
 *
 */

#ifndef LV_DRAW_SW_DITHER_H
#define LV_DRAW_SW_DITHER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw_sw.h"

#if LV_USE_DRAW_SW

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_draw_sw_dither_color_line(const lv_dither_dsc_t * dsc, lv_color_t * color_buf, int32_t x, int32_t y,
                                  int32_t width);
void lv_draw_sw_dither_mask_line(const lv_dither_dsc_t * dsc, lv_opa_t * mask_buf, int32_t x, int32_t y,
                                 int32_t width);
void lv_draw_sw_dither_buf_area(const lv_dither_dsc_t * dsc, lv_draw_buf_t * draw_buf, const lv_area_t * area,
                                const lv_area_t * origin_area);

#endif /*LV_USE_DRAW_SW*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DRAW_SW_DITHER_H*/
