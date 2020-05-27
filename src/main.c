/*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//Funcion Main
int main (int argc, char **argv)
{
	//Inicialización de Variables
	int cantImagenes = 0;
	int umbralBin = 0;
	int umbralNeg = 0;
	int flagConclusion = 0;
	char *nombreArchivoMasc = NULL;
	int index;
	int c;

	opterr = 0;

	//el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
	while ((c = getopt (argc, argv, "c:u:m:n:b")) != -1)
		switch (c)
			{
			case 'c':
				sscanf(optarg, "%d", &cantImagenes);
				break;
			case 'u':
				sscanf(optarg, "%d", &umbralBin);
				break;
			case 'n':
				sscanf(optarg, "%d", &umbralNeg);
				break;
			case 'm':
				nombreArchivoMasc = optarg;
				break;
			case 'b':
				flagConclusion = 1;
				break;
			case '?':
				if (optopt == 'c')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
				fprintf (stderr,
						"Unknown option character `\\x%x'.\n",
						optopt);
				return 1;
			default:
				abort ();
			}





	return 0;
	}
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <jpeglib.h>
#include <inttypes.h>

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

Pixel crearPixel(uint8_t r, uint8_t g, uint8_t b){
    Pixel new;
    new.R = r;
    new.G = g;
    new.B = b;
    return new;
}

// allocate memory for raw data
void alloc_jpeg(JpegData *jpegData)
{
    jpegData->data = NULL;
    jpegData->data = (uint8_t*) malloc(sizeof(uint8_t)  *
                                       jpegData->width  *
                                       jpegData->height *
                                       jpegData->ch);
}

// free memory for raw data
void free_jpeg(JpegData *jpegData)
{
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
bool read_jpeg(JpegData *jpegData,
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
        return false;
    }
    // 2.
    jpeg_stdio_src(&cinfo, fp);

    // 3.
    jpeg_read_header(&cinfo, TRUE);

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

    return true;
}

// write JPEG image
// 1. create JPEG compression object
// 2. specify destination data
// 3. set parameters
// 4. start compression
// 5. scan lines
// 6. finish compression
bool write_jpeg(const JpegData *jpegData,
                const char *dstfile,
                struct jpeg_error_mgr *jerr)
{
    // 1.
    struct jpeg_compress_struct cinfo;
    jpeg_create_compress(&cinfo);
    cinfo.err = jpeg_std_error(jerr);

    FILE *fp = fopen(dstfile, "wb");
    if (fp == NULL) {
        printf("Error: failed to open %s\n", dstfile);
        return false;
    }
    // 2.
    jpeg_stdio_dest(&cinfo, fp);

    // 3.
    cinfo.image_width      = jpegData->width;
    cinfo.image_height     = jpegData->height;
    cinfo.input_components = jpegData->ch;
    cinfo.in_color_space   = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    // 4.
    jpeg_start_compress(&cinfo, TRUE);

    // 5.
    uint8_t *row = jpegData->data;
    const uint32_t stride = jpegData->width * jpegData->ch;
    for (int y = 0; y < jpegData->height; y++) {
        jpeg_write_scanlines(&cinfo, &row, 1);
        row += stride;
    }

    // 6.
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(fp);

    return true;
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

int main(void)
{
    JpegData jpegData;
    struct jpeg_error_mgr jerr;

    // src/dst file
    char *src = "./16.jpg";
    char *dst = "./out.jpg";

    if (!read_jpeg(&jpegData, src, &jerr)){
        free_jpeg(&jpegData);
        return -1;
    }
    printf("Read:  %s\n", src);
    
    //printPixeles(jpegData);
    Pixel **matriz = guardarData(jpegData);
    JpegData jpegData1 = convertirARojo(jpegData, matriz);

    // reverse all bits
    //int size = jpegData.width * jpegData.height * jpegData.ch;
    //for (int i = 0; i < size; i++) {
    //    jpegData.data[i] = ~jpegData.data[i];
    //}

    if (!write_jpeg(&jpegData1, dst, &jerr)){
        free_jpeg(&jpegData1);
        return -1;
    }
    printf("Write: %s\n", dst);

    free_jpeg(&jpegData);

    return 0;
}
