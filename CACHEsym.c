#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* sacarLinea(FILE *f);

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;
char str[5];

int main() 
{ 
    int i = 0, j = 0, tiempoglobal = 0, numfallos = 0, datoinicial, palabra, linea, etq;
    unsigned char RAM[1024];
    char bin[16];

    T_LINEA_CACHE Cache[4];
    for(i; i<=4; i++){
        Cache[i].ETQ = 0xFF;
        for(j; j<=8; j++)
            Cache[i].Datos[j] = 0;
    }

    FILE* ram; 
    ram = fopen("RAM.bin", "rb");   //guarda el contenido del fichero en un array de chars
    rewind(ram);
    fgets(RAM,1025,ram);
    fclose(ram);
    FILE* f;
    f = fopen("accesos_memoria.txt", "r+");
    rewind(f);
    for(i = 0; i<=11; i++){
        datoinicial = (int)strtol(sacarLinea(f), NULL, 16);
        printf("Dato inicial es %04x\n", datoinicial);
        palabra = datoinicial&0b111;
        linea = (datoinicial>>3)&0b11;
        etq = (datoinicial>>5);
        printf("La palabra es %02x, la linea es %02x y la etiqueta es %02x\n", palabra, linea, etq);
    }
    fclose(f);
    return 0;
} 

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
/*
int binadec(long binario) {
    int i = 0, numerofinal = 0, placeholder;
    while (binario != 0) {
        placeholder = binario % 10;
        binario = binario/10;
        placeholder += placeholder * pow(2, i);
        ++i;
    }
    return numerofinal;
}*/