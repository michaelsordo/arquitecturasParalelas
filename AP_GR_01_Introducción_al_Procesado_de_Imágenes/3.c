/**
 * 3.- Mostrar una nueva imagen cuya parte superior sea la parte 
 * inferior de fruits, y cuya parte inferior sea la parte superior
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Error: Usage %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

    // Always check if the program can find the image file
    if (!Img) {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    }

    // a visualization window is created with title: image file name
    cvNamedWindow(argv[1],  CV_WINDOW_AUTOSIZE);
    // Img is shown in 'image' window
    cvShowImage(argv[1], Img);
    cvWaitKey(0);

    // Crea la imagen para la componete azul
    IplImage* Img2 = cvCreateImage(cvSize(Img->width, Img->height), IPL_DEPTH_8U, 3);

    int fila, columna;
    

    for (fila = 0; fila < Img->height/2; fila++) {

        unsigned char *pImg = (unsigned char *) Img->imageData + (fila+Img->height/2) * Img->widthStep;
        unsigned char *pImg2 = (unsigned char *) Img2->imageData + fila * Img2->widthStep;
    
        for (columna = 0; columna < Img->width; columna++) {
            //Imagen 2
            *pImg2++ = *pImg++ ;            
            *pImg2++ =*pImg++ ;          
            *pImg2++ = *pImg++;
        }       
    }
     for (fila = Img->height/2+1; fila < Img->height; fila++) {

        unsigned char *pImg = (unsigned char *) Img->imageData + (fila-Img->height/2) * Img->widthStep;
        unsigned char *pImg2 = (unsigned char *) Img2->imageData + fila* Img2->widthStep;
    
        for (columna = 0; columna < Img->width; columna++) {
            //Imagen 2
           *pImg2++ = *pImg++;             
            *pImg2++ = *pImg++; 
            *pImg2++ = *pImg++;
        }       
    }
    

    // crea y muestras las ventanas con las im genes
    cvNamedWindow("Componente 2", CV_WINDOW_AUTOSIZE);
    cvShowImage("Componente 2", Img2);

    cvWaitKey(0);
 
    // memory release for images before exiting the application
    cvReleaseImage(&Img);
    cvReleaseImage(&Img2);
    
 
    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Componente 2");

    return EXIT_SUCCESS;
}