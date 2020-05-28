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

    JpegData filtro;
    filtro.width = img.width;
    filtro.height = img.height;
    filtro.ch = img.ch;
    alloc_jpeg(&filtro);

    for (int i = 0; i < h*w; i++)
    {
        filtro.data[i] = img.data[i];
    }
    


    for(i = 1; i < h -1; i++){
        for(j = 1; j < w - 1; j++){
            calcularFiltro(&filtro,mascara,loc,w,h);
            loc++;
        }
        loc+=2;
    }
    
    for (int i = 0; i < w*h; i++)
    {
        img.data[i] = img.data[i] + filtro.data[i];
    }

    liberarJpeg(&filtro);
    


    return img;

}

void  calcularFiltro(JpegData *img,int **mascara,int loc,int w, int h){
    int n1 = img->data[loc - w -1] * mascara[0][0];
    int n2 = img->data[loc - w] * mascara[0][1]; 
    int n3 = img->data[loc - w + 1]*mascara[0][2]; 
    int n4 = img->data[loc - w]*mascara[1][0]; 
    int n5 = img->data[loc]*mascara[1][1]; 
    int n6 = img->data[loc + 1]*mascara[1][2]; 
    int n7 = img->data[loc + w -1]*mascara[2][0]; 
    int n8 = img->data[loc + w]*mascara[2][1]; 
    int n9 = img->data[loc + w +1]*mascara[2][2];

    int resultado = n1 + n2 + n3 + n4 + n5 + n6 +n7 +n8 +n9; 
    img->data[loc] = (resultado + 255)/2;

}