#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
    
//guarda el contenido del fichero en un array de chars
rewind(ram);
fgets(RAM[1024],1024,r);
//imprime 
 for(i=0;i<=1023;i++){
        printf("RAM[%d]: %c\n",i, RAM[i]);
    }




return 0;
}