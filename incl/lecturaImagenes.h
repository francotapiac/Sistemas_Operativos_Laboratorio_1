#include "estructuras.h"
#ifndef EXAMPLE_H
#define EXAMPLE_H

Pixel crearPixel(uint8_t r, uint8_t g, uint8_t b);
void alloc_jpeg(JpegData *jpegData);
void liberarJpeg(JpegData *jpegData);
JpegData leerImagenes();
JpegData escribirImagenes(JpegData jpegData1);

int leerJpeg(JpegData *jpegData,
              const char *srcfile,
              struct jpeg_error_mgr *jerr);
int escribirJpeg(const JpegData *jpegData,
                const char *dstfile,
                struct jpeg_error_mgr *jerr);

void printPixeles(JpegData jpegData);
Pixel **guardarData(JpegData jpegData);
JpegData convertirARojo(JpegData jpegData, Pixel **matriz);


#endif