#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;

int main() 
{ 
    int i = 0, tiempoglobal = 0, numfallos = 0;;
    char RAM[1024];

    T_LINEA_CACHE Cache;
    Cache.ETQ = 0xFF;
    for(i; i<=8; i++)
        Cache.Datos[i] = 0;
    FILE* ram; 
    int display; 
    ram = fopen("RAM.bin", "rb");

    while (1) {  
        display = fgetc(ram); 
        if (feof(ram)) 
            break; 
        printf("%c", display); 
    } 

    fclose(ram); 
    return 0; 

    //guarda el contenido del fichero en un array de chars
    rewind(ram);
    fgets(RAM,102,ram);

return 0;
} 