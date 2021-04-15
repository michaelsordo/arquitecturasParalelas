#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    
    
    IplImage* ImgOrigen = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
/*
    IplImage* ImgDestino = cvCreateImage(cvSize(ImgOrigen->width,ImgOrigen->height), IPL_DEPTH_8U, 3);
*/

    
    // Always check if the program can find a file
    if (!ImgOrigen) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }
 
    int fila,columna;
    
    for(int i=0;i<256;i++){
        
        cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
        cvShowImage(argv[1], ImgOrigen);
        cvWaitKey(5);
        
        for(int fila = 0; fila<ImgOrigen->height;fila++){
        
        unsigned char *pImgOrigen = (unsigned char *) ImgOrigen->imageData + fila * ImgOrigen->widthStep;
        

            for(columna=0; columna<ImgOrigen->widthStep;columna++){
                
                if(*pImgOrigen>0){
                    
                    *pImgOrigen=*pImgOrigen-1;
                   
                }
                     pImgOrigen++;
                
            
            }
        
        }
    }

        

       
       cvReleaseImage(&ImgOrigen);
    
    
        
    // a visualization window is created with title 'image'
    //cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    
    // img is shown in 'image' window
    //cvShowImage(argv[1], ImgOrigen);
    
    //cvWaitKey(0);


    // memory release for img before exiting the application
    //cvReleaseImage(&ImgOrigen);
    //cvReleaseImage(&ImgDestino);
    // Self-explanatory
    cvDestroyWindow(argv[1]);
    //cvDestroyWindow("copia");
    
    return EXIT_SUCCESS;

}