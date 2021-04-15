#include <stdio.h>
#include <stdlib.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>

int main(int argc, char** argv) {
    //imagen Frutas
    IplImage*ImgFrutas = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    //imagen aves
    IplImage*ImgAves = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);
    if(!ImgAves || !ImgFrutas) {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    }
    cvNamedWindow("", CV_WINDOW_AUTOSIZE);
    cvShowImage("", ImgAves);
    cvWaitKey(0);
    
    unsigned char*pImgFrutas;
    unsigned char*pImgAves;
    
    int fila, columna;
    for(fila = 0; fila < ImgFrutas->height; fila++) {
        
        pImgFrutas = (unsigned char*) ImgFrutas->imageData +
                fila*ImgFrutas->widthStep;
        pImgAves = (unsigned char*) ImgAves->imageData +
                fila*ImgAves->widthStep;
       
        for(columna = 0; columna < ImgFrutas->width; columna++) {
           
            *pImgAves++ = *pImgFrutas++;
            *pImgAves++ = *pImgFrutas++;
            *pImgAves++ = *pImgFrutas++;
        }  
        cvNamedWindow("" , CV_WINDOW_AUTOSIZE);
        cvShowImage("" , ImgAves);
        cvWaitKey(1);
    }
    cvWaitKey(0);

     return (EXIT_SUCCESS); 
}