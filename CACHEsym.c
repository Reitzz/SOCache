#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;

char str[5];

void rellenarDatos(T_LINEA_CACHE *);
char* sacarDireccion(FILE *);
int convertirDireccion(FILE *);
void dividirDireccion(int *, int);

int main() 
{ 
      //Inicializacion de variables y arrays

    int i = 0, j, numfallos = 0, datoinicial, ELP[3]; // ELP -> Etiqueta Linea Palabra
    float tiempoglobal = 0;
    unsigned char RAM[1024];
    char texto[100];
    T_LINEA_CACHE Cache[4];
    FILE* ram;
    rellenarDatos(Cache);

    //Si el fichero RAM.bin no se encuentra en el mismo directorio que CACHEsym.c no se ejecutara el programa y se finalizara 

    ram = fopen("RAM.bin", "r+");
    if(!ram){
        printf("No se puede localizar el fichero RAM.bin. Ubiquelo en el directorio correspondiente y vuelva a iniciar el programa");
        exit (-1);
    }

    //Guarda el contenido del fichero en un array de chars

    ram = fopen("RAM.bin", "rb");
    rewind(ram);
    fgets(RAM,1025,ram);
    fclose(ram);
    FILE* accesos_memoria;

    //Si el fichero accesos_memoria.txt no se encuentra en el mismo directorio que CACHEsym.c no se ejecutara el programa y se finalizara 

    if((accesos_memoria = fopen("accesos_memoria.txt", "r+")) == NULL){
        printf("No se puede localizar el fichero accesos_memoria.txt. Ubiquelo en el directorio correspondiente y vuelva a iniciar el programa");
        exit (-1);
    }

    accesos_memoria = fopen("accesos_memoria.txt", "r+");
    rewind(accesos_memoria);

    while(!feof(accesos_memoria)){
        datoinicial = convertirDireccion(accesos_memoria);
        dividirDireccion(ELP, datoinicial);

        //En caso de que haya fallo de cache (no coinciden la etiqueta de la direccion y la ETQ de la linea de la cache) carga el bloque y continua

        if ( Cache[ELP[1]].ETQ != ELP[0]){
            numfallos++;
            printf("T: %f, Fallo de CACHE %d, ADDR %04X ETQ %02X linea %02X palabra %02X bloque %02X\n" , tiempoglobal, numfallos, datoinicial, ELP[0], ELP[1], ELP[2], ELP[1]);
            tiempoglobal += 10;
            printf("Cargando el bloque %02X en la linea %02X\n", ELP[1], ELP[1]);
            for(j=0; j<=7; j++)
                Cache[ELP[1]].Datos[j] = RAM[ELP[0] + ELP[1] + j];
            Cache[ELP[1]].ETQ = ELP[0];
        }

        //Se imprime el acierto de cache y los datos

        printf("T: %f, Acierto de CACHE, ADDR %04X ETQ %02X linea %02X palabra %02X DATO %02X\n", tiempoglobal, datoinicial, ELP[0], ELP[1], ELP[2], RAM[datoinicial]);
        for(j=0; j<4; j++)
          printf("ETQ:%02X  Datos %02X %02X %02X %02X %02X %02X %02X %02X\n", Cache[j].ETQ, Cache[j].Datos[7], Cache[j].Datos[6], Cache[j].Datos[5], Cache[j].Datos[4], Cache[j].Datos[3], Cache[j].Datos[2], Cache[j].Datos[1], Cache[j].Datos[0]);
        texto[i] = RAM[datoinicial];
        i++;

        //Se suma UNO al tiempo global y se hace el sleep de 2 segundos

        tiempoglobal++;
        printf("\n");
        sleep(2);
    }

    //Se imprimen el texto leido, el numero total de accesos, el numero de fallos y el tiempo medio de acceso

    texto[++i] = '\0';
    printf("Número total de accesos: %i\nNúmero de fallos: %i\nTiempo medio de acceso: %f\n", (i-1), numfallos, tiempoglobal / (float)(i-1));
    printf("\nTexto leído desde la cache: %s\n\n", texto);
    fclose(accesos_memoria);
    return 0;
} 

void rellenarDatos(T_LINEA_CACHE* Cache){
    int i;
    for(i = 0; i<=4; i++)
        Cache[i] = (T_LINEA_CACHE){0xFF,{0,0,0,0,0,0,0,0}}; //Rellenamos cada una de las lineas de la cache con los datos del enunciado
}

char* sacarDireccion(FILE *accesos_memoria) {
    int tam=0;                                      //Guarda el tamaño de la cadena.
    char tmp = fgetc(accesos_memoria);              //Guarda temporalmente cada caracter.
    while( (tmp!='\n') && !feof(accesos_memoria)) { //Guarda cada char en str mientras no encuentre un salto de linea o se acabe el fichero.
        str[tam++]=tmp;
        tmp=getc(accesos_memoria);
    }
    str[tam]='\0';
    return str;
}

int convertirDireccion(FILE *f){
    return (int)strtol(sacarDireccion(f), NULL, 16);   //Hacemos un string to int de la direccion sacada en sacarDireccion para manipularlo
}

void dividirDireccion(int *ELP, int datoinicial){
    ELP[0]= (datoinicial>>5);
    ELP[1]= (datoinicial>>3)&0b11;                  //Se sacan la palabra, la etiqueta y la linea de cada direccion de memoria con mascaras de bits
    ELP[2] = datoinicial&0b111;
}