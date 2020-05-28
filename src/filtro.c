#include <stdio.h>
#include <jpeglib.h>
#include <stdint.h>
#include <stdlib.h>
#include "../incl/filtro.h"
#include "../incl/lecturaImagenes.h"

int **leerMascara(char *nombreMascara){
    FILE *archivo = fopen(nombreMascara,"r");
    if(archivo == NULL){
        printf("Error: no se ha detectado un archivo de texto \n"); 
    }

    
    int **mascara = crearPunteroMascara();
    
    int i = 0;
    int j = 0;
    int num1,num2,num3;
    for(i = 0;i < 3; i++){
        fscanf(archivo,"%d %d %d", &num1,&num2,&num3);
        mascara[i][0] = num1;
        mascara[i][1] = num2;
        mascara[i][2] = num3;
    }

  
    return mascara;
}

int **crearPunteroMascara(){
    int i= 0;
    int **mascara = (int**)malloc(3*sizeof(int*));
    for(i = 0; i < 3; i++){
        mascara[i] = (int*)malloc(3*sizeof(int));
    }
    return mascara;
}


JpegData aplicarFiltroLaplaciano(JpegData img,int **mascara){
    int w = img.width;
    int h= img.height;
    int loc = w +1;
    int i,j;

    for(i = 0; i < h -2; i++){
        for(j = 0; j < w - 2; j++){
            calcularFiltro(&img,mascara,loc,w,h);
            loc++;
        }
        loc+=2;
    }
    printf("loc = %d, wh = %d, w = %d, h = %d\n",loc,(w*h), w, h);
    return img;

}

void  calcularFiltro(JpegData *img,int **mascara,int loc,int w, int h){
    uint8_t n1 = img->data[loc - w -1]*mascara[0][0];
    uint8_t n2 = img->data[loc - w]*mascara[0][1]; 
    uint8_t n3 = img->data[loc - w + 1]*mascara[0][2]; 
    uint8_t n4 = img->data[loc - 1]*mascara[1][0]; 
    uint8_t n5 = img->data[loc]*mascara[1][1]; 
    uint8_t n6 = img->data[loc + 1]*mascara[1][2]; 
    uint8_t n7 = img->data[loc + w -1]*mascara[2][0]; 
    uint8_t n8 = img->data[loc + w]*mascara[2][1]; 
    uint8_t n9 = img->data[loc + w +1]*mascara[2][2];

    int resultado = n1 + n2 + n3 + n4 + n5 + n6 +n7 +n8 +n9; 
    img->data[loc] = resultado;

}