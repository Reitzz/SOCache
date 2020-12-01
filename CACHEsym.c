include "CACHElib.h"

int main() 
{ 
    int i, j, tiempoglobal = 0, numfallos = 0, datoinicial, palabra, linea, etq;
    unsigned char RAM[1024];
    char bin[16], texto[100];
    T_LINEA_CACHE Cache[4];
    for(i = 0; i<=4; i++){
        Cache[i].ETQ = 0xFF;
        for(j = 0; j<=7; j++)
            Cache[i].Datos[j] = 0;
    }
    i = 0;
    FILE* ram; 
    ram = fopen("RAM.bin", "rb");   //guarda el contenido del fichero en un array de chars
    rewind(ram);
    fgets(RAM,1025,ram);
    fclose(ram);
    FILE* accesos_memoria;
    accesos_memoria = fopen("accesos_memoria.txt", "r+");
    rewind(accesos_memoria);
    while(!feof(accesos_memoria)){
        datoinicial = (int)strtol(sacarLinea(accesos_memoria), NULL, 16);
        palabra = datoinicial&0b111;
        linea = (datoinicial>>3)&0b11;
        etq = (datoinicial>>5);
        if ( Cache[linea].ETQ != etq){
            numfallos++;
            printf("T: %d, Fallo de CACHE %d, ADDR %04X ETQ %02X linea %02X palabra %02X bloque %02X\n" , tiempoglobal, numfallos, datoinicial, etq, linea, palabra, linea);
            tiempoglobal += 10;
            printf("Cargando el bloque %02X en la linea %02X\n", linea, linea);
            for(j=0; j<=7; j++)
                Cache[linea].Datos[j] = RAM[etq + linea + j];
            Cache[linea].ETQ = etq;
        }
        printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %02X linea %02X palabra %02X DATO %02X\n", tiempoglobal, datoinicial, etq, linea, palabra, RAM[datoinicial]);
        //array texto?
        for(j=0; j<4; j++)
          printf("ETQ:%02X  Datos %02X %02X %02X %02X %02X %02X %02X %02X\n", Cache[j].ETQ, Cache[j].Datos[7], Cache[j].Datos[6], Cache[j].Datos[5], Cache[j].Datos[4], Cache[j].Datos[3], Cache[j].Datos[2], Cache[j].Datos[1], Cache[j].Datos[0]);
        texto[i] = RAM[datoinicial];
        i++;
        tiempoglobal += 2;
        printf("\n");
        sleep(2);
    }
    texto[++i] = '\0';
    printf("Número total de accesos: %i\nNúmero de fallos: %i\nTiempo medio de acceso: %i\n", (i-1), numfallos, tiempoglobal);
    printf("\nTexto leído desde la cache: %s\n\n", texto);
    fclose(accesos_memoria);
    return 0;
} 