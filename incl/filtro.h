#include "estructuras.h"
#ifndef FILTRO_H
#define FILTRO_H

JpegData aplicarFiltroLaplaciano(JpegData img,int **mascara);
int **leerMascara(char *nombreMascara);
int **crearPunteroMascara();
<<<<<<< HEAD
void calcularFiltro(JpegData *img,JpegData *nueva,int **mascara,int loc,int w, int h);
uint8_t corregirResultado(int resultado);
=======
void calcularFiltro(JpegData *img,JpegData *nuevo,int **mascara,int loc,int w, int h);
>>>>>>> f1franco
#endif