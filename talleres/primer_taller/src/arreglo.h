#ifndef ARREGLO_H
#define ARREGLO_H

#include <stdint.h>
#include <stdlib.h>

typedef struct element {
    char* path;
} element_t;

typedef struct arreglo {
    int64_t capacidad;
    int64_t cantidad;
    element_t* elementos;
} arreglo_t;

int initArreglo(arreglo_t* arreglo);
int agregar(arreglo_t* arreglo, char* path);
int destruir(arreglo_t* arreglo);


#endif  // ARREGLO_H