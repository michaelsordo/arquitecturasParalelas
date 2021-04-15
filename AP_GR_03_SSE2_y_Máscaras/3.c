/**
 * 3.- A partir de una imagen de 4 canales(abierta con la opción CV_LOAD_IMAGE_UNCHANGED),
 * mostrar el canal alfa como una imagen en escala de grises
 */

/* 
 * File:   3.c
 * Author: Michael
 *
 * Created on 20 de febrero de 2019, 10:56
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
    IplImage* ImgAlfa = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgRed = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 4 );

    // Always check if the program can find a file
    
      
   //Mostramos el canal alfa en escala de grises
    
    __m128i registroOrig;
    __m128i registroAlfaSolo;
    __m128i registroAlfa;
    __m128i temp1;
    __m128i temp2;
    __m128i temp3;
    __m128i mascaraAlfa = _mm_set1_epi32(0xFF000000);
    for (int fila = 0; fila < ImgOrigen->height; fila++) {
        __m128i *pImgOrigen = (__m128i *) (ImgOrigen->imageData + fila * ImgOrigen-> widthStep);
        __m128i *pImgAlfa = (__m128i *) (ImgAlfa->imageData + fila * ImgAlfa-> widthStep);
        for (int cc = 0; cc < ImgOrigen->widthStep; cc=cc+16) {
            registroOrig=*pImgOrigen;
            registroAlfaSolo = _mm_and_si128(registroOrig, mascaraAlfa); //Dejamos solo el canal Alfa
            temp1 = _mm_srli_epi32(registroAlfaSolo, 8);
            temp2 = _mm_srli_epi32(temp1, 8);
            temp3 = _mm_srli_epi32(temp2, 8);
            temp2 = _mm_or_si128 (temp1, temp2);
            registroAlfa = _mm_or_si128 (temp2, temp3);
            *pImgAlfa++ = registroAlfa;
            pImgOrigen++;
            
        }
    } 
     
     //Mostramos canal alfa valor rojo
__m128i registroOrig;
    __m128i registroAlfaSolo;
    __m128i registroAlfa;
    __m128i temp1;
    __m128i temp2;
    __m128i temp3;
    __m128i mascaraAlfa = _mm_set1_epi32(0xFF000000);
    for (int fila = 0; fila < ImgOrigen->height; fila++) {
        __m128i *pImgOrigen = (__m128i *) (ImgOrigen->imageData + fila * ImgOrigen-> widthStep);
        __m128i *pImgAlfa = (__m128i *) (ImgAlfa->imageData + fila * ImgAlfa-> widthStep);
        for (int cc = 0; cc < ImgOrigen->widthStep; cc=cc+16) {
            registroOrig=*pImgOrigen;
            registroAlfaSolo = _mm_and_si128(registroOrig, mascaraAlfa); //Dejamos solo el canal Alfa
            temp1 = _mm_srli_epi32(registroAlfaSolo, 8);
            temp2 = _mm_srli_epi32(temp1, 8);
            temp3 = _mm_srli_epi32(temp2, 8);
            temp2 = _mm_or_si128 (temp1, temp2);
            registroAlfa = _mm_or_si128 (temp2, temp3);
            *pImgAlfa++ = registroAlfa;
            pImgOrigen++;
            
        }
    } 
    
    
    // Mostramos las imágenes
    
   
    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
    // img is shown in 'image' window
    cvShowImage(argv[1], ImgOrigen);
    cvWaitKey(0);
    cvShowImage("Componente Alfa", ImgAlfa);
    cvWaitKey(0);
    cvShowImage("Canal Rojo",ImgRed);
    cvWaitKey(0);
    
 


    // memory release for img before exiting the application
    cvReleaseImage(&ImgOrigen);
    cvReleaseImage(&ImgAlfa);
    cvReleaseImage (&ImgRed);

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Componente Alfa");
    cvDestroyWindow("Canal Rojo");

    return EXIT_SUCCESS;

}