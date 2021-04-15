/**
 * 1.- A partir de dos imagenes vamos a coger el fondo de una, y uno de los
 * personajes de la otra para crear una animación. Colocaremos el personaje
 * en la esquina izquierda superior de la imagen fondo. 
 * 
 * 
 * 
 */

/* 
 * File:   1.c
 * Author: Michael
 *
 * Created on 20 de febrero de 2019, 10:56
 */


#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {


    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    IplImage* personaje = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* escena = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    
  
    if (!personaje || escena) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    int fila;
    int cc;
    
    for(fila=0; fila<48;fila++){
        unsigned char *pPerso=(unsigned char*)personaje->imageData+(fila+908) *personaje->widthStep  + 780 * personaje->nChannels;
/*
        unsigned char *pImgE5 = (unsigned char *) ImgE5->imageData + (fila+20) * ImgE5->widthStep + 20 * Img->nChannels;
*/
        unsigned char *pEscena=(unsigned char*)(escena->imageData + fila*escena->widthStep);  
        for(cc=0;cc<56;cc++){ //56*NUMCANALES(56*4) en el siguiente ejercicio
            if(*(pPerso+3)==255){
                *pEscena++=*pPerso++; //blue
                *pEscena++=*pPerso++; //green
                *pEscena++=*pPerso++; //red
                *pEscena++=*pPerso++; //alpha
            }else{
                pPerso+=4;
                pEscena+=4;
            }
        }
    }
    

    
    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);

    cvShowImage(argv[1], personaje);
    cvShowImage(argv[1], escena);

    cvWaitKey(0); 

    cvReleaseImage(&personaje);
    cvReleaseImage(&escena);

    cvDestroyWindow(argv[1]);
    return EXIT_SUCCESS;

}
