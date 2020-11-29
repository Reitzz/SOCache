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
    int i = 0, j = 0, tiempoglobal = 0, numfallos = 0, datoinicial, palabra, linea, etq, comprobante, instante;
    unsigned char RAM[1024];
    char bin[16], texto[100];

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
        palabra = datoinicial&0b111;
        linea = (datoinicial>>3)&0b11;
        etq = (datoinicial>>5);
     

        if ( Cache[linea].ETQ != etq){
            numfallos++;
            printf("T: %d, Fallo de CACHE %d, ADDR %04X ETQ %X linea %02X palabra %02X bloque %02X\n" , instante, numfallos, addr , etq, linea, palabra, linea);
            tiempoglobal = tiempoglobal + 10;
            printf("Cargando el bloque %02X en la linea %02X\n", Cache[linea], linea);
            for(j=0; j<=7; j++)
                Cache[linea].Datos[j] = RAM[etq + linea + j];
            Cache[linea].ETQ = etq;
        }


        printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %Xlinea %02X palabra %02X DATO %02X\n", instante, addr, etq, linea, palabra, dato);
        //array texto?
        for(i=0; i<4; i++)
          printf("ETQ:%02X  Datos %02X %02X %02X %02X %02X %02X %02X %02X\n", Cache[i].ETQ, Cache[i].Datos[7], Cache[i].Datos[6], Cache[i].Datos[5], Cache[i].Datos[4], Cache[i].Datos[3], Cache[i].Datos[2], Cache[i].Datos[1], Cache[i].Datos[0]);
        
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