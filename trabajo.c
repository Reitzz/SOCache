#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() 
{ 
    FILE* demo; 
    int display; 
    demo = fopen("RAM.bin", "rb");

    while (1) {  
        display = fgetc(demo); 
        if (feof(demo)) 
            break; 
        printf("%c", display); 
    } 
    
    fclose(demo); 
    return 0; 
} 