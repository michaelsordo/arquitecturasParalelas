/**
 * 1.- Compilar y ejecutar el código ejemplo con una imagen TrueColor, es decir,
 * para una profundidad de colorde 24 bits por pixel. En Netbeans será 
 * necesario indicar los directorios donde se encuentran los archivos de cabecera 
 * (ficheros include, *.h) y las librerías (librerías de enlace dinámico, *.dll).
 * Mostrar primero la imagenletrasRGB.png, y posteriormente fruits.jpg, tal como indica la figura 

 */
 
/* 
 * File:   1.c
 * Author: Michael
 *
 * Created on 12 de febrero de 2019, 20:24
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {

    
    if (argc != 3) {  // Ponemos tres argumentos para mostrar 2 imágenes
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }
    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);   
    IplImage* Img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED); 
    // Always check if the program can find a file
    if (!Img1) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
    else if (!Img2) {
        printf("Error: fichero %s no leido\n", argv[2]);
        return EXIT_FAILURE;
    }
        
    
   
    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    cvNamedWindow(argv[2], CV_WINDOW_NORMAL);
    // img is shown in 'image' window
    cvShowImage(argv[1], Img1);
    cvShowImage(argv[2], Img2);
    cvWaitKey(0);
    // memory release for img before exiting the application
    cvReleaseImage(&Img1);
    cvReleaseImage(&Img2);
    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow(argv[2]);
    return EXIT_SUCCESS;

}
