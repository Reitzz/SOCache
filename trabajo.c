#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() 
{ 
    FILE* ram; 
    int display; 
    ram = fopen("RAM.bin", "rb"); // Hola dani hola raul

    while (1) {  
        display = fgetc(ram); 
        if (feof(ram)) 
            break; 
        printf("%c", display); 
    } 

    fclose(ram); 
    return 0; 
} 