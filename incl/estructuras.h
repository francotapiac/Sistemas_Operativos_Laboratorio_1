#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


// JPEG image struct
typedef struct {
    uint8_t *data;   // raw data
    uint32_t width;
    uint32_t height;
    uint32_t ch;     // color channels
} JpegData;

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} Pixel;

#endif