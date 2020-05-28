#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include <inttypes.h>
#include "../incl/escrituraImagenes.h"

// write JPEG image
// 1. create JPEG compression object
// 2. specify destination data
// 3. set parameters
// 4. start compression
// 5. scan lines
// 6. finish compression
int escribirJpeg(const JpegData *jpegData,
                const char *dstfile,
                struct jpeg_error_mgr *jerr, 
                char *typeColorSpace)
{
    // 1.
    struct jpeg_compress_struct cinfo;
    jpeg_create_compress(&cinfo);
    cinfo.err = jpeg_std_error(jerr);

    FILE *fp = fopen(dstfile, "wb");
    if (fp == NULL) {
        printf("Error: failed to open %s\n", dstfile);
        return 0;
    }
    // 2.
    jpeg_stdio_dest(&cinfo, fp);

    // 3.
    cinfo.image_width      = jpegData->width;
    cinfo.image_height     = jpegData->height;
    cinfo.input_components = jpegData->ch;
    if(typeColorSpace == "rgb")
        cinfo.in_color_space   = JCS_RGB;
    else
        cinfo.in_color_space   = JCS_GRAYSCALE;
    
    jpeg_set_defaults(&cinfo);

    // 4.
    jpeg_start_compress(&cinfo, 1);

    // 5.
    uint8_t *row = (uint8_t*)jpegData->data;
    const uint32_t stride = jpegData->width * jpegData->ch;
    for (int y = 0; y < jpegData->height; y++) {
        jpeg_write_scanlines(&cinfo, &row, 1);
        row += stride;
    }

    // 6.
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(fp);

    return 1;
}

JpegData escribirImagenes(JpegData jpegData1, char *typeColorSpace, char *nombreSalida){
    struct jpeg_error_mgr jerr;
    char *dst = nombreSalida;
    if (!escribirJpeg(&jpegData1, dst, &jerr, typeColorSpace)){
        liberarJpeg(&jpegData1);
        return jpegData1;
    }
    //printf("Write: %s\n", dst);
    return jpegData1;
}

    