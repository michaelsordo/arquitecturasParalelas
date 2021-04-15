/**
 * 2.- Fundido a negro con SSE. Transición Fade to Black o Fundido a Negro
 * 
 * 
 * 

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
    
    IplImage* ImgFundido = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    
    
    // Always check if the program can find a file
    if (!ImgOrigen) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    int fila, cc;
    
    cvShowImage("Fruits", ImgOrigen);  // Para abrir la imagen
    cvWaitKey(0);

    // FUNDIDO A NEGRO CON SSE
    int i;
    __m128i B = _mm_set1_epi8 (1); //Llena el registro B con 1s
    for(i = 0; i<256; i++){ 
        for(fila = 0; fila < ImgFundido->height; fila++){
            __m128i *pImgFundido = (__m128i *) (ImgFundido->imageData+fila*ImgFundido->widthStep);
            for(cc = 0; cc<ImgFundido->widthStep; cc=cc+16){
               
                //__m128i A = _mm_load_si128 (__m128i const *P); // P alineado a 16 Bytes
                //__m128i A = _mm_loadu_si128 (__m128i const *P); // P no alineado a 16 Bytes
                __m128i A = *pImgFundido;
                __m128i C = _mm_subs_epu8 (A, B);
                //_mm_store_si128 (__m128i *P, __m128i B); // P alineado a 16 Bytes
                //_mm_storeu_si128 (__m128i *P, __m128i B); // P no alineado a 16 Bytes
                _mm_storeu_si128 (pImgFundido, C);
                //*pImgFundido=C;
                pImgFundido++;
            }
        }
        cvShowImage("Fundido", ImgFundido);
        cvWaitKey(5);
    }
    
    

  
    // memory release for img before exiting the application
    
    
    cvReleaseImage(&ImgFundido);
    

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    
    cvDestroyWindow("Fundido");
    

    return EXIT_SUCCESS;

}