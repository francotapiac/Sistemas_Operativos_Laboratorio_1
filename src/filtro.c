#include <stdio.h>
#include <jpeglib.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
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
    int h = img.height;
    int loc = w +1;
    int i,j;
    /*
    int loc_aux = 0;
    for(i = 0; i< h; i++){
        for(j = 0; j < w; j++){
            printf("%d ",img.data[loc_aux]);
            loc_aux++;
        }
       printf("\n");
    }
    */
   JpegData nueva;
    nueva.height = h;
    nueva.width = w;
    nueva.ch = 1;
    alloc_jpeg(&nueva);

    for (int i = 0; i < w*h; i++){
        nueva.data[i] = img.data[i];
    }

    //printf("\n");
    for(i = 1; i < h -1; i++){
        for(j = 1; j < w - 1; j++){
            calcularFiltro(&img,&nueva,mascara,loc,w,h);
            loc++;
        }
        loc+=2;
    }

    /*liberarJpeg(&img);
     loc_aux = 0;
    for(i = 0; i< h; i++){
        for(j = 0; j < w; j++){
            printf("%d ",img.data[loc_aux]);
            loc_aux++;
        }
       printf("\n");
    }
 */ liberarJpeg(&img);
    return nueva;

}

void  calcularFiltro(JpegData *img,JpegData *nueva,int **mascara,int loc,int w, int h){
    int n1 = img->data[loc - w -1];
    n1 = n1* mascara[0][0];
    int n2 = img->data[loc - w] ; 
    n2= n2 * mascara[0][1];
    int n3 = img->data[loc - w + 1] ; 
    n3 = n3 * mascara[0][2];
    int n4 = img->data[loc - 1] ; 
   // printf("data(w+1): %d --- ",img->data[2*w + 1]);
    n4 = n4 * mascara[1][0];
    int n5 = img->data[loc]; 
    n5 = n5 * mascara[1][1];
    int n6 = img->data[loc + 1] ;
    n6 = n6 * mascara[1][2]; 
    int n7 = img->data[loc + w -1] ;
    n7 = n7 * mascara[2][0]; 
    int n8 = img->data[loc + w] ; 
    n8 = n8 * mascara[2][1];
    int n9 = img->data[loc + w +1] ;
    n9 = n9* mascara[2][2];

    int resultado = n1 + n2 + n3 + n4 + n5 + n6 +n7 +n8 +n9; 
   // printf("pixel: %d --- ",img->data[loc] );
   //printf("pixel: %" PRIu8 " ", img->data[loc]);
    nueva->data[loc] = resultado;
    //printf("resultado: %d --- ",resultado);
    //printf("n1:%d n2:%d n3:%d n4:%d n5:%d n6:%d n7:%d n8:%d n9:%d \n",n1,n2,n3,n4,n5,n6,n7,n8,n9);
 
    
}