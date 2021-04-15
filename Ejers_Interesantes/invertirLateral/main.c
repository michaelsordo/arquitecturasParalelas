#include <stdio.h>
#include <stdlib.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>

int main(int argc, char** argv) {
    IplImage*Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    if(!Img) {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    } 
    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    cvShowImage(argv[1], Img);
    cvWaitKey(0);
   //Crea la nueva imagen
    IplImage*ImgREVES = cvCreateImage(cvSize(Img->width, Img->height), 
            IPL_DEPTH_8U,3);
    
    unsigned char*pImg;
    unsigned char*pImgREVES;
    
    int fila, columna;
    for(fila = 0; fila < Img->height; fila++) {
        
        pImg = Img->imageData + fila*Img->widthStep;
      //Coje donde empieza la imagen y suma la fila por el tamaño de pixel
      //más la  mitad del ancho de la imagen (para que empiece en la mitad)
        pImgREVES = ImgREVES->imageData + fila*ImgREVES->widthStep +
                Img->width/2*(Img->nChannels);
        for(columna = 0; columna < Img->width/2; columna++) {
            *pImgREVES++ = *pImg++;
            *pImgREVES++ = *pImg++;
            *pImgREVES++ = *pImg++;
        }  
    }
    int fila1, columna1;
    for(fila1 = 0; fila1 < Img->height; fila1++) {
        //pImg empieza ahora en la mitad del ancho
        pImg = Img->imageData + (fila1)*Img->widthStep +
                Img->width/2*(Img->nChannels);
        pImgREVES = ImgREVES->imageData + fila1*ImgREVES->widthStep;
        for(columna1 = 0; columna1 < Img->width/2; columna1++) {
            *pImgREVES++ = *pImg++;
            *pImgREVES++ = *pImg++;
            *pImgREVES++ = *pImg++;
        }    
    }
    cvNamedWindow("", CV_WINDOW_AUTOSIZE);
    cvShowImage("", ImgREVES);
    cvWaitKey(0);
    return (EXIT_SUCCESS); 
}