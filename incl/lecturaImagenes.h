#ifndef EXAMPLE_H
#define EXAMPLE_H
#include "estructuras.h"

void alloc_jpeg(JpegData *jpegData);
void liberarJpeg(JpegData *jpegData);
JpegData leerImagenes();
int leerJpeg(JpegData *jpegData,
              const char *srcfile,
              struct jpeg_error_mgr *jerr);

#endif