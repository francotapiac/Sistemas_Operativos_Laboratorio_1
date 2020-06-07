#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <jpeglib.h>
#include <inttypes.h>
#include <string.h>
#include "../incl/lecturaImagenes.h"
#include "../incl/escrituraImagenes.h"
#include "../incl/binarizacion.h"
#include "../incl/clasificacion.h"
#include "../incl/conversion.h"
#include "../incl/filtro.h"


void printearValores(JpegData img, int w, int h){
	int loc = 0;
	printf("Valores uint8_t:\n\n");
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			printf("%" PRIu8 " ", img.data[loc]);
			loc++;
		}
		printf("\n");
	}
	loc = 0;
	printf("Valores int:\n\n");
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			printf("%d ",img.data[loc]);
			loc++;
		}
		printf("\n");	
	}
	
}

//Funcion Main
int main (int argc, char **argv)
{
	//Inicialización de Variables
	int cantImagenes = 0;
	int umbralBin = 0;
	int umbralNeg = 0;
	int flagResultados = 0;
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
				flagResultados = 1;
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

	if(flagResultados){
		printf("|          image          |       nearly black       |\n");
		printf("|-------------------------|--------------------------|\n");
	}

	int **mascara = leerMascara(nombreArchivoMasc);

	uint8_t num = 10;
	num = num*(-1);
	int entero = (int)num;
	printf("%" PRIu8 "\n", num);
	printf("%d\n",num-100);



    // Para cada imagen
	for (int i = 1; i <= cantImagenes; i++)
	{

		char filename[30];
		char imagename[30];
		sprintf(filename,"./imagen_%i.jpg",i);
		sprintf(imagename, "imagen_%i",i);
		
		//1. Leer la imagen
		JpegData jpegData = leerImagenes(filename);
		//if(i==1)printearValores(jpegData,jpegData.width,jpegData.height); 

		//2. Convertir a escala de grises
		jpegData = convertirAEscalaGrises(jpegData);
		//if(i==1)printearValores(jpegData,jpegData.width,jpegData.height); 
		
		//3. aplicar filtro laplaciano
		jpegData = aplicarFiltroLaplaciano(jpegData,mascara);
		//if(i==1)printearValores(jpegData,jpegData.width,jpegData.height); 
		
		//4. binarizar imagen
		jpegData = binarizarImagen(jpegData, umbralBin);
	    //if(i==8)printearValores(jpegData,jpegData.width,jpegData.height); 
		
		//5. Clasificar imagen
		char *nearlyBlack = analisisDePropiedad(jpegData, umbralNeg);

		//6. Escribir imagen
		char fileout[30];
		sprintf(fileout,"./out_%i.jpg",i);
		escribirImagenes(jpegData, "escalagrises",fileout);

		//7. liberar memoria
		liberarJpeg(&jpegData);

		if(flagResultados){
			printf("|          %s       |             %s           |\n", imagename, nearlyBlack);
		}
	}

   
    
	return 0;
}







