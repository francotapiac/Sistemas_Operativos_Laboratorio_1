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
#include "../incl/conversion.h"
#include "../incl/filtro.h"
#include "../incl/escrituraImagenes.h"
#include "../incl/binarizacion.h"
#include "../incl/clasificacion.h"


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
    
    // Para cada imagen
	for (int i = 0; i < cantImagenes; i++)
	{
		//formar string "imagen_"+i
		char *snum;
		char *imagename = "imagen_";
		char *filename;
		sprintf(snum, "%d", i);
		strcat(imagename,snum);
		strcat(filename, ".jpg");
		
		//1. Leer la imagen
		JpegData jpegData = leerImagenes();
		
		//2. Convertir a escala de grises
		jpegData = convertirAEscalaGrises(jpegData);
		
		//3. aplicar filtro laplaciano
		
		//4. binarizar imagen
		jpegData = binarizarImagen(jpegData, umbralBin);

		//5. Clasificar imagen
		char *nearlyBlack = analisisDePropiedad(jpegData, umbralNeg);

		//6. Escribir imagen
		escribirImagenes(jpegData, "escalagrises");

		//7. liberar memoria
		liberarJpeg(&jpegData);

		if(flagResultados){
			printf("|          %s          |             %s          |\n", imagename, nearlyBlack);
		}
	}

	int **mascara = leerMascara(nombreArchivoMasc);
	jpegData = aplicarFiltroLaplaciano(jpegData,mascara);
	escribirImagenes(jpegData, "escalagrises","./out2.jpg");
	return 0;
}







