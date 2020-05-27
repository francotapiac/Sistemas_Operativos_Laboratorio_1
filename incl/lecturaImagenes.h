#ifndef EXAMPLE_H
#define EXAMPLE_H
#include "estructuras.h"

Pixel crearPixel(uint8_t r, uint8_t g, uint8_t b);
void alloc_jpeg(JpegData *jpegData);
void liberarJpeg(JpegData *jpegData);
JpegData leerImagenes();
int leerJpeg(JpegData *jpegData,
              const char *srcfile,
              struct jpeg_error_mgr *jerr);

void printPixeles(JpegData jpegData);
Pixel **guardarData(JpegData jpegData);
JpegData convertirARojo(JpegData jpegData, Pixel **matriz);


#endif