#include "../incl/clasificacion.h"

int analisisDePropiedad(JpegData img, int umbral){

    int len = img.width*img.height;
    int cont = 0;

    for (int i = 0; i < len; i++)
    {
        //Si es pixel negro
        if(img.data[i] == 0){
            //se suma 1 al contador
            cont++;
        }
    }

    double porcentajeNegrura = (cont*100)/len;

    if (porcentajeNegrura >= umbral){
        return 1;
    }
    else{
        return 0;
    }
    
}