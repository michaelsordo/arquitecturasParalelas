/**
 * 4.-Crear una imagen de 1 único canal de tamaño 256x256. El nivel de gris de 
 * cada fila será igual al índice de la propia fila
 * 
 */

/* 
 * File:   4.c
 * Author: Michael
 *
 * Created on 13 de febrero de 2019, 10:20
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char **argv) {
//3 canales
    IplImage* Img = cvCreateImage(cvSize(256,256), IPL_DEPTH_8U, 3 );   
    int fila, columna;    
    for(fila = 0; fila < Img->height ; fila++){
        unsigned char *pImg = (unsigned char *) Img->imageData + fila * Img->widthStep;           
        for (columna = 0; columna < Img->width; columna++) {
            //Imagen GREEN
            *pImg++ = fila; 
            *pImg++ = fila;
            *pImg++ = fila;
      
        }
    }
    /*
    //1 canales
    IplImage* Img = cvCreateImage(cvSize(256,256), IPL_DEPTH_8U, 1 );   
    int fila, columna;    
    for(fila = 0; fila < Img->height ; fila++){
        unsigned char *pImg = (unsigned char *) Img->imageData + fila * Img->widthStep;           
        for (columna = 0; columna < Img->width; columna++) {
            //Imagen GREEN
            *pImg++ = fila; 
           
      
        }
    }*/
    
// crea y muestras las ventanas con las im genes
    cvNamedWindow("Componente 2", CV_WINDOW_AUTOSIZE);
    cvShowImage("Componente 2", Img);
    cvWaitKey(0); 
    // memory release for images before exiting the application
    cvReleaseImage(&Img);
    // Self-explanatory
    cvDestroyWindow(argv[1]);
return EXIT_SUCCESS;
}


