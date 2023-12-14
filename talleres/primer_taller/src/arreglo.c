#include "arreglo.h"

int initArreglo(arreglo_t* arreglo) {
    int error = EXIT_SUCCESS;
    arreglo->cantidad = 0;
    arreglo->capacidad = 0;
    arreglo->elementos = NULL;
}