/**
 * 1.-Copia de una imagen
 */

/* 
 * File:   main.c
 * Author: Michael
 *
 * Created on 13 de febrero de 2019, 9:16
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h> 
#include <emmintrin.h> //Para el SSE2
/*
 * 
 */
int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    } 

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    
    IplImage* ImgOrigen = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgDestino = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    

    
    // Always check if the program can find a file
    if (!ImgOrigen) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    
         
    int fila, cc;
    for (fila = 0; fila < ImgOrigen->height; fila++) {
        __m128i *pImgOrigen = (__m128i *) (ImgOrigen->imageData + fila * ImgOrigen->
        widthStep);
        __m128i *pImgDestino = (__m128i *) (ImgDestino->imageData + fila* ImgDestino
        ->widthStep);
        __m128i registro;
        for (cc = 0; cc < ImgOrigen->widthStep; cc=cc+16) {
            //Opcion 1
            registro = *pImgOrigen++;
            *pImgDestino++ = registro;
            /*Opcion 2
            registro = _mm_load_si128(pImgOrigen++);
            _mm_store_si128(pImgDestino++,registro);
            Opcion 3, para datos no alineados en memoria
            registro = _mm_loadu_si128(pImgOrigen++);
            _mm_storeu_si128(pImgDestino++,registro);*/
        }
    }
    


    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    
    
    
    
    // img is shown in 'image' window
    cvShowImage(argv[1], ImgOrigen);
    cvWaitKey(0);
    cvShowImage("Copia", ImgDestino);
    cvWaitKey(0);
      


    // memory release for img before exiting the application
    cvReleaseImage(&ImgOrigen);
    cvReleaseImage(&ImgDestino);
    

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Copia");
    

    return EXIT_SUCCESS;

}