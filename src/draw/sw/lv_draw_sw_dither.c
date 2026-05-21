/**
 * @file lv_draw_sw_dither.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw_sw_dither.h"

#if LV_USE_DRAW_SW

/**********************
 *  STATIC PROTOTYPES
 **********************/
static int32_t dither_delta(const lv_dither_dsc_t * dsc, int32_t x, int32_t y, uint32_t channel);
static inline uint8_t clamp_u8(int32_t v);
static inline uint8_t quantize_5(uint8_t v, int32_t delta);
static inline uint8_t quantize_6(uint8_t v, int32_t delta);
static void dither_rgb888(const lv_dither_dsc_t * dsc, uint8_t * r, uint8_t * g, uint8_t * b, int32_t x, int32_t y);
static void dither_rgb565_px(const lv_dither_dsc_t * dsc, uint16_t * px, int32_t x, int32_t y, bool swapped);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_sw_dither_color_line(const lv_dither_dsc_t * dsc, lv_color_t * color_buf, int32_t x, int32_t y,
                                  int32_t width)
{
    if(!lv_dither_dsc_is_enabled(dsc)) return;

    lv_dither_dsc_t normalized = *dsc;
    lv_dither_dsc_normalize(&normalized);

    for(int32_t i = 0; i < width; i++) {
        uint8_t r = color_buf[i].red;
        uint8_t g = color_buf[i].green;
        uint8_t b = color_buf[i].blue;
        dither_rgb888(&normalized, &r, &g, &b, x + i, y);
        color_buf[i] = lv_color_make(r, g, b);
    }
}

void lv_draw_sw_dither_mask_line(const lv_dither_dsc_t * dsc, lv_opa_t * mask_buf, int32_t x, int32_t y,
                                 int32_t width)
{
    if(!lv_dither_dsc_is_enabled(dsc)) return;

    lv_dither_dsc_t normalized = *dsc;
    lv_dither_dsc_normalize(&normalized);

    for(int32_t i = 0; i < width; i++) {
        int32_t v = mask_buf[i] + dither_delta(&normalized, x + i, y, 0);
        mask_buf[i] = clamp_u8(v);
    }
}

void lv_draw_sw_dither_buf_area(const lv_dither_dsc_t * dsc, lv_draw_buf_t * draw_buf, const lv_area_t * area,
                                const lv_area_t * origin_area)
{
    if(!lv_dither_dsc_is_enabled(dsc)) return;

    lv_dither_dsc_t normalized = *dsc;
    lv_dither_dsc_normalize(&normalized);

    uint32_t px_size = lv_color_format_get_size(draw_buf->header.cf);
    int32_t stride = draw_buf->header.stride;
    bool swapped = draw_buf->header.cf == LV_COLOR_FORMAT_RGB565_SWAPPED;

    for(int32_t y = area->y1; y <= area->y2; y++) {
        uint8_t * p = lv_draw_buf_goto_xy(draw_buf, y == area->y1 ? area->x1 : area->x1, y);
        for(int32_t x = area->x1; x <= area->x2; x++) {
            int32_t dx = x - origin_area->x1;
            int32_t dy = y - origin_area->y1;
            if(px_size == 1) {
                int32_t v = p[0] + dither_delta(&normalized, dx, dy, 0);
                p[0] = clamp_u8(v);
            }
            else if(px_size == 2) {
                dither_rgb565_px(&normalized, (uint16_t *)p, dx, dy, swapped);
            }
            else if(px_size >= 3) {
                uint8_t r = p[0];
                uint8_t g = p[1];
                uint8_t b = p[2];
                dither_rgb888(&normalized, &r, &g, &b, dx, dy);
                p[0] = r;
                p[1] = g;
                p[2] = b;
            }
            p += px_size;
        }
        LV_UNUSED(stride);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static int32_t dither_delta(const lv_dither_dsc_t * dsc, int32_t x, int32_t y, uint32_t channel)
{
    uint32_t tile = dsc->tile_size ? dsc->tile_size : 64;
    uint32_t tx = (uint32_t)((x % (int32_t)tile + (int32_t)tile) % (int32_t)tile);
    uint32_t ty = (uint32_t)((y % (int32_t)tile + (int32_t)tile) % (int32_t)tile);
    uint32_t h = tx * 374761393u + ty * 668265263u + dsc->seed * 2246822519u + channel * 3266489917u;
    h ^= h >> 13;
    h *= 1274126177u;
    h ^= h >> 16;

    int32_t n = (int32_t)(h & 255) - 128;
    int32_t wave = (int32_t)(((tx * 17u + ty * 29u + dsc->seed + channel * 53u) & 255u)) - 128;
    n = (n * 3 + wave) >> 2;

    return (n * (int32_t)dsc->strength) / (1023 * 8);
}

static inline uint8_t clamp_u8(int32_t v)
{
    if(v < 0) return 0;
    if(v > 255) return 255;
    return (uint8_t)v;
}

static inline uint8_t quantize_5(uint8_t v, int32_t delta)
{
    uint8_t q = clamp_u8((int32_t)v + delta) >> 3;
    return (q << 3) | (q >> 2);
}

static inline uint8_t quantize_6(uint8_t v, int32_t delta)
{
    uint8_t q = clamp_u8((int32_t)v + delta) >> 2;
    return (q << 2) | (q >> 4);
}

static void dither_rgb888(const lv_dither_dsc_t * dsc, uint8_t * r, uint8_t * g, uint8_t * b, int32_t x, int32_t y)
{
    if(dsc->color_mode == LV_DITHER_COLOR_MODE_GRAYSCALE) {
        int32_t delta = dither_delta(dsc, x, y, 0);
        *r = quantize_5(*r, delta);
        *g = quantize_6(*g, delta);
        *b = quantize_5(*b, delta);
    }
    else {
        *r = quantize_5(*r, dither_delta(dsc, x, y, 0));
        *g = quantize_6(*g, dither_delta(dsc, x, y, 1));
        *b = quantize_5(*b, dither_delta(dsc, x, y, 2));
    }
}

static void dither_rgb565_px(const lv_dither_dsc_t * dsc, uint16_t * px, int32_t x, int32_t y, bool swapped)
{
    uint16_t v = *px;
    if(swapped) v = (v >> 8) | (v << 8);

    uint8_t r = ((v >> 11) & 0x1F) << 3;
    uint8_t g = ((v >> 5) & 0x3F) << 2;
    uint8_t b = (v & 0x1F) << 3;
    r |= r >> 5;
    g |= g >> 6;
    b |= b >> 5;
    dither_rgb888(dsc, &r, &g, &b, x, y);

    v = ((uint16_t)(r >> 3) << 11) | ((uint16_t)(g >> 2) << 5) | (b >> 3);
    if(swapped) v = (v >> 8) | (v << 8);
    *px = v;
}

#endif /*LV_USE_DRAW_SW*/
