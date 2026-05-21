/**
 * @file lv_dither.h
 *
 */

#ifndef LV_DITHER_H
#define LV_DITHER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../config/lv_conf_internal.h"
#include "../lv_types.h"

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LV_DITHER_ALGORITHM_TYPE_STABLE_ERROR_DIFFUSION = 0,
} lv_dither_algorithm_type_t;

typedef enum {
    LV_DITHER_ALGORITHM_TILED_FLOYD_STEINBERG = 0,
} lv_dither_algorithm_t;

typedef enum {
    LV_DITHER_COLOR_MODE_GRAYSCALE = 0,
    LV_DITHER_COLOR_MODE_COLOR,
} lv_dither_color_mode_t;

typedef struct {
    uint8_t enable;
    lv_dither_algorithm_type_t algorithm_type : 4;
    lv_dither_algorithm_t algorithm : 4;
    lv_dither_color_mode_t color_mode : 4;
    uint16_t strength;
    uint16_t seed;
    uint16_t tile_size;
} lv_dither_dsc_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_dither_dsc_init(lv_dither_dsc_t * dsc);
void lv_dither_dsc_normalize(lv_dither_dsc_t * dsc);
bool lv_dither_dsc_is_enabled(const lv_dither_dsc_t * dsc);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DITHER_H*/
