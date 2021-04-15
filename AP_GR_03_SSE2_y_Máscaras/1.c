/**
 * 1.-Creación de una imagen uniforme con el color Verde Android o Amarillo Minion
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

    
    // Creamos las imágenes verde y amarillo, lo que es el tamaño

  //Primera forma para crearla  
IplImage* ImgV = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 4 );
IplImage* ImgA = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 4 );    
    
 
//Segunda forma
/*
    CvSize tamano = cvSize(640,480);
    IplImage* ImgV = cvCreateImage(tamano, IPL_DEPTH_8U, 4);
    IplImage* ImgA = cvCreateImage(tamano, IPL_DEPTH_8U, 4);
*/
    
    // Always check if the program can find a file
    
    

    
    //Crear imágenes Verde y Amarillo con SS2
    __m128i registroV = _mm_set1_epi32(0x00A4C639);
    __m128i registroA = _mm_set1_epi32(0x00FED55D);
    int fila, cc;
    for (fila = 0; fila < ImgV->height; fila++) {
        __m128i *pImgV = (__m128i *) (ImgV->imageData + fila * ImgV-> widthStep);
        __m128i *pImgA = (__m128i *) (ImgA->imageData + fila * ImgA-> widthStep);
        for (cc = 0; cc < ImgV->widthStep; cc=cc+16) {
            *pImgV++ = registroV;
            *pImgA++ = registroA;
            
        }
    }
    

    
    //Mostramos las imágenes, tanto la verde android como la amarillo minion
    
    cvShowImage("Verde android", ImgV);
    cvWaitKey(0);
    
    cvShowImage("Amarillo Minion", ImgA);
    cvWaitKey(0);


    // memory release for img before exiting the application
/*
    cvReleaseImage(&ImgOrigen);
*/
    cvReleaseImage(&ImgV);
    cvReleaseImage(&ImgA);
/*
    cvReleaseImage(&ImgR);
    cvReleaseImage(&ImgG);
    cvReleaseImage(&ImgB);
    cvReleaseImage(&ImgAlfa);
*/ 

    // Self-explanatory
    //cvDestroyWindow(argv[1]);
    cvDestroyWindow("Verde android");
    cvDestroyWindow("Amarillo Minion");


    return EXIT_SUCCESS;

}