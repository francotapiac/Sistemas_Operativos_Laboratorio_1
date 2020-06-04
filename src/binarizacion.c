#include "../incl/binarizacion.h"
#include <stdint.h>
#include <stdio.h>

JpegData binarizarImagen(JpegData img, uint8_t umbral){

    int len = img.width*img.height;

    for (int i = 0; i < len; i++)
    {
        if(img.data[i] > umbral){
            img.data[i] = 255;
        }
        else{
            img.data[i] = 0;
        }
    }

    return img; 
}