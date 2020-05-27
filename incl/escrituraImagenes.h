#ifndef ESCRITURA_H
#define ESCRITURA_H
#include "estructuras.h"

JpegData escribirImagenes(JpegData jpegData1);
int escribirJpeg(const JpegData *jpegData,
                const char *dstfile,
                struct jpeg_error_mgr *jerr);
void liberarJpeg(JpegData *jpegData);

#endif