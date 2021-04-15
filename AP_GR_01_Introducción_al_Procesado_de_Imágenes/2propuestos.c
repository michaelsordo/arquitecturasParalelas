/**
 * 2.Propuestos.- Mostrar una nueva imagen más grande que la original, en la que se encuentre 
 * la imagen original entrada a lo ancho y a lo alto. 
 * Los puntos donde no haya imagen serán negros. 
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

    // Crea la imagen que se modificara posteriormente
    
    IplImage* ImgE5 = cvCreateImage(cvSize(Img->width+40, Img->height+40), IPL_DEPTH_8U, 3);

    int fila, columna;
    

   
       

    for(fila = 0; fila < Img->height; fila++) {
        unsigned char *pImg  = (unsigned char *) Img->imageData + fila * Img->widthStep;
        unsigned char *pImgE5 = (unsigned char *) ImgE5->imageData + (fila+20) * ImgE5->widthStep + 20 * Img->nChannels;
        
        for(columna = 0; columna < Img->width; columna++) {
            *pImgE5++ = *pImg++;
            *pImgE5++ = *pImg++;
            *pImgE5++ = *pImg++;
        }
    }
   
    

    // crea y muestras las ventanas con las im genes
    cvNamedWindow("MARCO", CV_WINDOW_AUTOSIZE);
    cvShowImage("MARCO", ImgE5);

    cvWaitKey(0);
 
    // memory release for images before exiting the application
    cvReleaseImage(&Img);
    cvReleaseImage(&ImgE5);
    
 
    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("MARCO");

    return EXIT_SUCCESS;
}