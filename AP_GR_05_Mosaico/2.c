// Funcion Mosaico

#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ALTO 16
#define ANCHO 16

void copiarBloque(int i, int j, IplImage *imagenOrigen, int k, int l, IplImage *imagenDestino); // En C tenemos que declararlo aquí.
int compararBloque(int filaBloque1, int colBloque1, IplImage *imagen1, int filaBloque2, int colBloque2, IplImage *imagen2);


int main(int argc, char** argv) {

    if (argc != 3) {
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
    if (!Img2) {
        printf("Error: fichero %s no leido\n", argv[2]);
        return EXIT_FAILURE;
    }

    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1],  CV_WINDOW_AUTOSIZE);
    // img is shown in 'image' window
    cvShowImage(argv[1], Img1);
    cvWaitKey(0);

    // a visualization window is created with title 'image'
    cvNamedWindow(argv[2], CV_WINDOW_AUTOSIZE);
    // img is shown in 'image' window
    cvShowImage(argv[2], Img2);
    cvWaitKey(0);
    
    
    
    
     IplImage *ImgNueva = cvCreateImage(cvSize(Img1->width, Img1->height), IPL_DEPTH_8U, 3);
    
    
    //copiarBloque(4,4, Img1, 700, 900, ImgNueva);
  

    int fila1, columna1;
    for (fila1 = 0; fila1 < Img1->height; fila1 = fila1 + ALTO) {
        for (columna1 = 0; columna1 < Img1->width; columna1 = columna1 + ANCHO) {

            int fila2, columna2;
            int minimo = INT_MAX;
            int valor = 0;
            int filamin, columnamin;
            for (fila2 = 0; fila2 < Img2->height; fila2 = fila2 + ALTO) {
                for (columna2 = 0; columna2 < Img2->width; columna2 = columna2 + ANCHO) {

                    valor = compararBloque(fila1, columna1, Img1, fila2, columna2, Img2);
                    if (valor < minimo) {
                        
                        minimo = valor;
                        filamin = fila2;
                        columnamin = columna2;
                    }
                }
            }
            copiarBloque(filamin, columnamin, Img2, fila1, columna1, ImgNueva);
        }
    }

   
    // a visualization window is created with title 'image'
    cvNamedWindow("Img Nueva", CV_WINDOW_AUTOSIZE);
    // img is shown in 'image' window
    cvShowImage("Img Nueva", ImgNueva);
    cvWaitKey(0);
    
    // memory release for img before exiting the application
    cvReleaseImage(&Img1);
    cvReleaseImage(&Img2);
    cvReleaseImage(&ImgNueva);
    

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow(argv[2]);
    cvDestroyWindow("Img Nueva");

    return EXIT_SUCCESS;

}

void copiarBloque(int i, int j, IplImage *imagenOrigen, int k, int l, IplImage *imagenDestino) {
    
    int fila, columna;

    for (fila = 0; fila < ALTO ; fila++) {
        
        unsigned char *pimagenOrigen = (unsigned char *)( imagenOrigen->imageData + ((i+fila) * imagenOrigen->widthStep) + j*3); //Esos 3 son bytes
        unsigned char *pimagenDestino = (unsigned char *) imagenDestino->imageData + ((k+fila) * imagenDestino->widthStep) + l*3;
       
        for (columna = 0; columna < ANCHO; columna++) {
            *pimagenDestino++ = *pimagenOrigen++;
            *pimagenDestino++ = *pimagenOrigen++;
            *pimagenDestino++ = *pimagenOrigen++;
        }
         
    } 
    
    

}

int compararBloque(int filaBloque1, int colBloque1, IplImage *imagen1, int filaBloque2, int colBloque2, IplImage *imagen2) {
    int fila, columna, valor = 0;
    
    for (fila = filaBloque1; fila < ALTO + filaBloque1; fila++) {
        unsigned char *pimagen1 = (unsigned char *) imagen1->imageData + fila * imagen1->widthStep + colBloque1 * 3;
        unsigned char *pimagen2 = (unsigned char *) imagen2->imageData + filaBloque2 * imagen2->widthStep + colBloque2 * 3;

        for (columna = 0; columna < ANCHO; columna++) {

            valor = valor + abs(*pimagen1++ - *pimagen2++) + abs(*pimagen1++ - *pimagen2++) + abs(*pimagen1++ - *pimagen2++);

        }
        filaBloque2++;
       
    }
    return valor;
}



