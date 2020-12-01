include "CACHElib.h"

char* sacarLinea(FILE *f) {

    //Guarda el tamaÃo de la cadena.
    int tam=0;

    //Guarda temporalmente cada caracter.
    char tmp = fgetc(f);

    //Guarda cada char en str mientras no encuentre un salto de linea o EOF.
    while( (tmp!='\n') && !feof(f)) {
        str[tam++]=tmp;
        tmp=getc(f);
    }
    str[tam]='\0';

    return str;
}