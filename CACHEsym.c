#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* sacarLinea(FILE *f);

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;

int main() 
{ 
    int i = 0, j = 0, tiempoglobal = 0, numfallos = 0, datoinicial;
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
    f = fopen("accesos_memoria.txt", "r");
    rewind(f);
    for(i = 0; i<=11; i++){
        datoinicial = (int)strtol(sacarLinea(f), NULL, 16)%16;
        printf("Dato inicial es %i", datoinicial);
    }
    fclose(f);
    return 0;
} 

char* sacarLinea(FILE *f) {

    //Guarda la cadena que se devolvera.
    char str[5];

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
/*void HexToBin(string hexadecimal){
    long int i = 0;
    while (hexadecimal[i]) {
        switch (hexadecimal[i]) {
        case '0':
            bin = "0000";
            break;
        case '1':
            bin = "0001";
            break;
        case '2':
            bin = "0010";
            break;
        case '3':
            bin = "0011";
            break;
        case '4':
            bin = "0100";
            break;
        case '5':
            bin = "0101";
            break;
        case '6':
            bin = "0110";
            break;
        case '7':
            bin = "0111";
            break;
        case '8':
            bin = "1000";
            break;
        case '9':
            bin = "1001";
            break;
        case 'A':
            bin = "1010";
            break;
        case 'B':
            bin = "1011";
            break;
        case 'C':
            bin = "1100";
            break;
        case 'D':
            bin = "1101";
            break;
        case 'E':
            bin = "1110";
            break;
        case 'F':
            bin = "1111";
            break;
        }
        i++;
    }
}
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