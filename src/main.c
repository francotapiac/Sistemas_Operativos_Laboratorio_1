
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <jpeglib.h>
#include <inttypes.h>
#include "../incl/lecturaImagenes.h"
#include "../incl/escrituraImagenes.h"


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


    
    // src/dst file
   

    JpegData jpegData = leerImagenes();
    Pixel **matriz = guardarData(jpegData);
    JpegData jpegData1 = convertirARojo(jpegData, matriz);
    escribirImagenes(jpegData1);

    liberarJpeg(&jpegData);
	return 0;
}







