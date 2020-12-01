include "CACHElib.h"

char* sacarLinea(FILE *accesos_memoria) {

    //Guarda el tamaÃo de la cadena.
    int tam=0;

    //Guarda temporalmente cada caracter.
    char tmp = fgetc(accesos_memoria);

    //Guarda cada char en str mientras no encuentre un salto de linea o EOF.
    while( (tmp!='\n') && !feof(accesos_memoria)) {
        str[tam++]=tmp;
        tmp=getc(accesos_memoria);
    }
    str[tam]='\0';

    return str;
}