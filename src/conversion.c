#include <stdio.h>
#include <jpeglib.h>
#include <stdint.h>
#include "../incl/conversion.h"
#include "../incl/lecturaImagenes.h"

/*
 * Aqui se escriben las funciones para convertir imagenes RGB a escala de grises 
*/

JpegData convertirAEscalaGrises(JpegData img){
    int len = img.height*img.width*img.ch;
    int loc = 0;
    uint8_t Y, R, G, B;
    
    JpegData nuevaImg;
    nuevaImg.width = img.width;
    nuevaImg.height = img.height;
    nuevaImg.ch = 1;
    alloc_jpeg(&nuevaImg);
    
    for (int i = 0; i < len; i+=3)
    {
        R = img.data[i]; 
        G = img.data[i+1];
        B = img.data[i+2];
        Y = R*0.3 + G*0.59 + B*0.11;
        nuevaImg.data[loc] = Y;
        loc++;
    }
    return nuevaImg;
}