# Tarea01: zippass_serial

## Estructura de los archivos

En la carpeta src/ se encuentran 7 archivos los cuales tienen la siguiente
estructura:

* dynamicArray.c
* dynamicArray.h
* readData.c
* readData.h
* findPassword.c
* findPassword.h
* main.c

### DynamicArray

Los archivos dynamicArray.c y dynamicArray.h se encargan de crear una estructura
de datos para almacenar informacion relevante de las contraseñas dentro de ella.

Es la unica estructura de datos que se implementa dentro del programa y se ve de la siguiente manera:

![memory_diagram](diagramaDatos.svg)

Utilizando una estructura de memoria tal que:

![memory_diagram](diagramaMemoria.svg)

### ReadData

Los archivos readData se encargan principalmente de abrir un archivo *.zip* y
tratar de abrir el mismo; si se consigue, el resultado se almacena en la
estructura de datos *dynamicArray*

### FindPassword

Los archivos findPassword se encargan de implementar la logica necesaria para
recibir como parametro los datos previamente leidos con *readData* y guardados
en la estructura de datos *dynamicArray* para seguidamente utilizar los mismos
como parametros base para el calculo y la generación de contraseñas aleatorias
que son seguidamente utilizadas con fuerza bruta para intentar abrir un archivo
.ZIP.

Sus funciones son:

```c
char* getPass(size_t numToChange, dynamicArray_t* passInfo, char* alfa, 
    size_t passLength);

size_t forceZip(dynamicArray_t* passInfo, char* alfa);

void fileCracker(dynamicArray_t* files);
```
