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
{   //inicializacion de variables y arrays
    int i, j, numfallos = 0, datoinicial, palabra, linea, etq;
    float tiempoglobal = 0;
    unsigned char RAM[1024];
    char texto[100];
    T_LINEA_CACHE Cache[4];
    // inicializa a FF (hexadecimal) los campos ETQ y a 0 todos los campos de datos de la caché
    for(i = 0; i<=4; i++){
        Cache[i].ETQ = 0xFF;
        for(j = 0; j<=7; j++)
            Cache[i].Datos[j] = 0;}
    i = 0;
    FILE* ram; 
    //si el fichero RAM.bin no se encuentra en el mismo directorio que CACHEsym.c no se ejecutara el programa y se finalizara 
     if(ram = fopen("RAM.bin", "r+") == NULL){
        printf("No se puede localizar el fichero RAM.bin. Ubiquelo en el directorio correspondiente y vuelva a iniciar el programa");
        exit (-1);}
    //guarda el contenido del fichero en un array de chars
    ram = fopen("RAM.bin", "rb");
    rewind(ram);
    fgets(RAM,1025,ram);
    fclose(ram);
    FILE* accesos_memoria;
    //si el fichero accesos_memoria.txt no se encuentra en el mismo directorio que CACHEsym.c no se ejecutara el programa y se finalizara 
    if(accesos_memoria = fopen("accesos_memoria.txt", "r+") == NULL){
        printf("No se puede localizar el fichero accesos_memoria.txt. Ubiquelo en el directorio correspondiente y vuelva a iniciar el programa");
        exit (-1);}
    //se sacan la palabra, la etiqueta y la linea de cada direccion de memoria
    accesos_memoria = fopen("accesos_memoria.txt", "r+");
    rewind(accesos_memoria);
    while(!feof(accesos_memoria)){
        datoinicial = (int)strtol(sacarLinea(accesos_memoria), NULL, 16);
        palabra = datoinicial&0b111;
        linea = (datoinicial>>3)&0b11;
        etq = (datoinicial>>5);
        //en caso de que haya fallo de cache (no coinciden la etiqueta de la direccion y la ETQ de la linea de la cache) se hace que coincidan para que en el siguiente intento haya acierto de cache
        if ( Cache[linea].ETQ != etq){
            numfallos++;
            printf("T: %f, Fallo de CACHE %d, ADDR %04X ETQ %02X linea %02X palabra %02X bloque %02X\n" , tiempoglobal, numfallos, datoinicial, etq, linea, palabra, linea);
            tiempoglobal += 10;
            printf("Cargando el bloque %02X en la linea %02X\n", linea, linea);
            for(j=0; j<=7; j++)
                Cache[linea].Datos[j] = RAM[etq + linea + j];
            Cache[linea].ETQ = etq;
        }
        //Se imprime el acierto de cache y los datos
        printf("T: %f, Acierto de CACHE, ADDR %04X ETQ %02X linea %02X palabra %02X DATO %02X\n", tiempoglobal, datoinicial, etq, linea, palabra, RAM[datoinicial]);
        for(j=0; j<4; j++)
          printf("ETQ:%02X  Datos %02X %02X %02X %02X %02X %02X %02X %02X\n", Cache[j].ETQ, Cache[j].Datos[7], Cache[j].Datos[6], Cache[j].Datos[5], Cache[j].Datos[4], Cache[j].Datos[3], Cache[j].Datos[2], Cache[j].Datos[1], Cache[j].Datos[0]);
        texto[i] = RAM[datoinicial];
        i++;
        // se suma dos al tiempo global y se hace el sleep de 2 segundos
        tiempoglobal += 2;
        printf("\n");
        sleep(2);
    }
    //se imprimen el texto leido, el numero total de accesos, el numero de fallos y el tiempo medio de acceso
    texto[++i] = '\0';
    printf("Número total de accesos: %i\nNúmero de fallos: %i\nTiempo medio de acceso: %f\n", (i-1), numfallos, tiempoglobal / (float)(i-1));
    printf("\nTexto leído desde la cache: %s\n\n", texto);
    fclose(accesos_memoria);
    return 0;
} 
char* sacarLinea(FILE *accesos_memoria) {

    //Guarda el tamanio de la cadena.
    int tam=0;

    //Guarda temporalmente cada caracter.
    char tmp = fgetc(accesos_memoria);

    //Guarda cada char en str mientras no encuentre un salto de linea o se acabe el fichero.
    while( (tmp!='\n') && !feof(accesos_memoria)) {
        str[tam++]=tmp;
        tmp=getc(accesos_memoria);
    }
    str[tam]='\0';

    return str;
}