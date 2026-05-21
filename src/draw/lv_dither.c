/**
 * @file lv_dither.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl_public.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_dither_dsc_init(lv_dither_dsc_t * dsc)
{
    lv_memzero(dsc, sizeof(*dsc));
    dsc->algorithm_type = LV_DITHER_ALGORITHM_TYPE_STABLE_ERROR_DIFFUSION;
    dsc->algorithm = LV_DITHER_ALGORITHM_TILED_FLOYD_STEINBERG;
    dsc->color_mode = LV_DITHER_COLOR_MODE_COLOR;
    dsc->strength = 1023;
    dsc->seed = 0;
    dsc->tile_size = 64;
}

void lv_dither_dsc_normalize(lv_dither_dsc_t * dsc)
{
    if(dsc->strength > 1023) dsc->strength = 1023;
    if(dsc->tile_size < 16) dsc->tile_size = 16;
    if(dsc->tile_size > 256) dsc->tile_size = 256;
    if(dsc->algorithm_type != LV_DITHER_ALGORITHM_TYPE_STABLE_ERROR_DIFFUSION) {
        dsc->algorithm_type = LV_DITHER_ALGORITHM_TYPE_STABLE_ERROR_DIFFUSION;
    }
    if(dsc->algorithm != LV_DITHER_ALGORITHM_TILED_FLOYD_STEINBERG) {
        dsc->algorithm = LV_DITHER_ALGORITHM_TILED_FLOYD_STEINBERG;
    }
}

bool lv_dither_dsc_is_enabled(const lv_dither_dsc_t * dsc)
{
#if LV_USE_DITHER
    if(dsc == NULL) return false;
    if(!dsc->enable) return false;
    if(dsc->strength == 0) return false;
    return true;
#else
    LV_UNUSED(dsc);
    return false;
#endif
}
