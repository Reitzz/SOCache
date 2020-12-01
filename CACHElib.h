#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* sacarLinea(FILE *f);

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;
char str[5];