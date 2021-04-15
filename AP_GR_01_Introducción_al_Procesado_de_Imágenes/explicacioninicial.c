#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {

    /*
argc es el numero de palabras, serian X.exe fruits.jpg
el argv son punteros a las palabras:
 si pusimos X.exe fruits.jpg seria
      argc=2 
 *    argv[0]= X.exe
 *    argv[1]= fruits.jpg
 *    argv[...] = serian el resto de parametros si pasamos mas
 */
    
    if (argc != 2) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    
    /*
     IplImage* parametro de tipo struct, se le pasa width heigh nchannels deep widthsteep(tiene que ser 
     forzada a ser multiplo de 4) imageData(num de 64 bits que marca una dir de memoria donde empiezan
     los pixels[van de forma BGR en vez de RGB porque se empieza a leer desde el byte menos significativo])
     -vienen siendo los parametros explicados en la clase grande 1*/
         
    // Always check if the program can find a file
    if (!Img1) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    /*GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOON
    el cvNamedWindow crea una ventana vacia cuyo titulo coincide con el nombre del 
    fichero que hayamos abierto*/
    
    // img is shown in 'image' window
    cvShowImage(argv[1], Img1);
    /*
     representa en pantalla la imagen
     */
    cvWaitKey(0);
    /*
     espera mostrando la image, si ponen tiempo son milisegundos, si pones 0 queda infinito
     */

    // memory release for img before exiting the application
    cvReleaseImage(&Img1);
    /*
     borra la imagen de memoria
     */
    // Self-explanatory
    cvDestroyWindow(argv[1]);
    /*
     destruye la ventana 
     */
    return EXIT_SUCCESS;

}
