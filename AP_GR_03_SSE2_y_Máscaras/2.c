/**
 * 2.-A partir de una imagen de 4 canales (abierta con la opción
 * CV_LOAD_IMAGE_UNCHANGED),mostrar la imagen original y en otras
 * 3 ventanas sus componentes roja,verde,azul.
 * 
 * 
 * 

 */

/* 
 * File:   main.c
 * Author: Michael
 *
 * Created on 20 de febrero de 2019, 9:50
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <emmintrin.h> //Para el SSE2
 
int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    //Cargamos la imagen original y los tres componentes que vamos a mostrar
    //tal y como dice el título con CV_LOAD_IMAGE_UNCHANGED
    

    IplImage* ImgOrigen = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgR = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgG = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgB = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED); 
    
  

    // Always check if the program can find a file
    
      
    //Creamos las componentes rojo, verde y azul
    
    __m128i registroR = _mm_set1_epi32(0x00FF0000); // Rojo
    __m128i registroG = _mm_set1_epi32(0x0000FF00); // Verde
    __m128i registroB = _mm_set1_epi32(0x000000FF); // Azul
    __m128i registro;
    for (int fila = 0; fila < ImgOrigen->height; fila++) {
        __m128i *pImgOrigen = (__m128i *) (ImgR->imageData + fila * ImgR-> widthStep);
        __m128i *pImgR = (__m128i *) (ImgR->imageData + fila * ImgR-> widthStep);
        __m128i *pImgG = (__m128i *) (ImgG->imageData + fila * ImgG-> widthStep);
        __m128i *pImgB = (__m128i *) (ImgB->imageData + fila * ImgB-> widthStep);
        for (int cc = 0; cc < ImgOrigen->widthStep; cc=cc+16) {
            registro=*pImgOrigen; //Para ordenar correctamente la ImgOrigen
            *pImgR++ = _mm_and_si128(registro, registroR);
            *pImgG++ = _mm_and_si128(registro, registroG);
            *pImgB++ = _mm_and_si128(registro, registroB);
            pImgOrigen++;
        }
    }
     

    
    
    // Mostramos las imágenes
    
    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
    // img is shown in 'image' window
    cvShowImage(argv[1], ImgOrigen); 
    cvWaitKey(0);
    cvShowImage("Componente Roja", ImgR);
    cvWaitKey(0);
    cvShowImage("Componente Verde", ImgG);
    cvWaitKey(0);
    cvShowImage("Componente Azul", ImgB);
    cvWaitKey(0);
   
    // memory release for img before exiting the application

    cvReleaseImage(&ImgOrigen);
    cvReleaseImage(&ImgR);
    cvReleaseImage(&ImgG);
    cvReleaseImage(&ImgB);

 

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Componente Roja");
    cvDestroyWindow("Componente Verde");
    cvDestroyWindow("Componente Azul");


    return EXIT_SUCCESS;

}