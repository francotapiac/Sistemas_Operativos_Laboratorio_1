#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include <inttypes.h>
#include "../incl/lecturaImagenes.h"

Pixel crearPixel(uint8_t r, uint8_t g, uint8_t b){
    Pixel new;
    new.R = r;
    new.G = g;
    new.B = b;
    return new;
}

// allocate memory for raw data
void alloc_jpeg(JpegData *jpegData){
    jpegData->data = NULL;
    jpegData->data = (uint8_t*) malloc(sizeof(uint8_t)  *
                                       jpegData->width  *
                                       jpegData->height *
                                       jpegData->ch);
}

// free memory for raw data
void liberarJpeg(JpegData *jpegData){
    if (jpegData->data != NULL) {
        free(jpegData->data);
        jpegData->data = NULL;
    }
}

// read JPEG image
// 1. create JPEG decompression object
// 2. specify source data
// 3. read JPEG header
// 4. set parameters
// 5. start decompression
// 6. scan lines
// 7. finish decompression
int leerJpeg(JpegData *jpegData,
              const char *srcfile,
              struct jpeg_error_mgr *jerr)
{
    // 1.
    struct jpeg_decompress_struct cinfo;
    jpeg_create_decompress(&cinfo);
    cinfo.err = jpeg_std_error(jerr);

    FILE *fp = fopen(srcfile, "rb");
    if (fp == NULL) {
        printf("Error: failed to open %s\n", srcfile);
        return 0;
    }
    // 2.
    jpeg_stdio_src(&cinfo, fp);

    // 3.
    jpeg_read_header(&cinfo, 1);

    // 4. omitted
    // 5.
    jpeg_start_decompress(&cinfo);

    jpegData->width  = cinfo.image_width;
    jpegData->height = cinfo.image_height;
    jpegData->ch     = cinfo.num_components;

    alloc_jpeg(jpegData);

    // 6. read line by line
    uint8_t *row = jpegData->data;
    const uint32_t stride = jpegData->width * jpegData->ch;
    for (int y = 0; y < jpegData->height; y++) {
        jpeg_read_scanlines(&cinfo, &row, 1);
        row += stride;
    }

    // 7.
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);

    return 1;
}



void printPixeles(JpegData jpegData){
        printf("width = %" PRIu32 "\n", jpegData.width);
    printf("height = %" PRIu32 "\n", jpegData.height);
    printf("chanels = %" PRIu32 "\n", jpegData.ch);

    uint8_t num = 0;
    int loc = 0;

    for (int i = 0; i < jpegData.height; i++)
    {
        for (int j = 0; j < jpegData.width*jpegData.ch; j++)
        {
            num = jpegData.data[loc];
            printf("%" PRId8 " ", num);
            loc++;
        }
        printf("\n");
        
    }
}

Pixel **guardarData(JpegData jpegData){
    uint8_t num1 = 0, num2 = 0, num3 = 0;
    int loc = 0;
    
    Pixel **matriz;
    matriz = (Pixel **)malloc (jpegData.height*sizeof(Pixel *));
    for (int i=0;i<jpegData.height;i++)
        matriz[i] = (Pixel *) malloc (jpegData.width*sizeof(Pixel));

    for (int i = 0; i < jpegData.height; i++)
    {
        for (int j = 0; j < jpegData.width; j++)
        {
             num1 = jpegData.data[loc];
             num2 = jpegData.data[loc+1];
             num3 = jpegData.data[loc+2];

             matriz[i][j] = crearPixel(num1,num2,num3);
            
            loc= loc+3;
        }
        
    }
    printf("Los datos se guardaron correctamente\n");
    return matriz;
}

JpegData convertirARojo(JpegData jpegData, Pixel **matriz){
    for (int i = 0; i < jpegData.height*jpegData.width*jpegData.ch; i+=3)
    {
        jpegData.data[i] = 0;
        jpegData.data[i+1] = 0;
        jpegData.data[i+2] = jpegData.data[i+2];  
    }
    printf("aqui\n");
    return jpegData;
}


JpegData leerImagenes(){
    JpegData jpegData;
    struct jpeg_error_mgr jerr;
    char *src = "./16.jpg";
    if (!leerJpeg(&jpegData, src, &jerr)){
        liberarJpeg(&jpegData);
        return jpegData;
    }
    printf("Leer:  %s\n", src);
    return jpegData;
}




