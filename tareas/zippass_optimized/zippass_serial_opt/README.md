# Tarea01: zippass_serial

## Descripción del problema a resolver

Un usuario ha olvidado la contraseña de un archivo ZIP que contiene archivos
importantes. El usuario necesita acceder a los archivos lo antes posible.

Una solución posible es usar fuerza bruta para probar todas las posibles
contraseñas. Esta solución es efectiva, pero puede ser muy lenta, especialmente
si la contraseña es larga.

## Objetivo de la tarea

El objetivo de este proyecto es desarrollar un programa en C que encuentre
mediante fuerza bruta la contraseña para desencriptar los archivos comprimidos
dentro de un archivo ZIP.
El programa debe cumplir con los siguientes requisitos:

* Debe leer de la entrada estándar un lote de trabajo,
como el presentado en el enunciado.
* Debe encontrar e imprimir la contraseña para
cada archivo ZIP en la salida estándar.
* Debe ser lo más eficiente posible.

## Requisitos funcionales

Los requisitos funcionales del proyecto son los siguientes:

* Se debe leer de la entrada estándar un lote de trabajo que consiste en:
  * La primera línea corresponde al alfabeto con que
  se escribió las contraseñas.
  * La segunda línea corresponde a la cantidad máxima
  de caracteres la contraseña.
  * La tercera línea es una línea en blanco de separación.
  * Las cuarta y siguientes líneas corresponden a una lista de archivos ZIP
  a los que se les debe encontrar la contraseña.
  Cada línea contiene un nombre de archivo y una
  ruta relativa a la carpeta donde se encuentra el proyecto.
* El programa debe encontrar e imprimir la contraseña para cada archivo ZIP
en la salida estándar. La contraseña debe estar separada del nombre del
archivo por un espacio en blanco.
* Si el programa no puede encontrar la contraseña para un archivo ZIP,
debe imprimir el nombre del archivo en la salida estándar.

Para procesar los archivos ZIP, el programa usará la biblioteca libzip.
La función `zip_open()` abre el archivo ZIP en modo de lectura.
La función `zip_set_password()` establece la contraseña para el archivo ZIP.
La función `zip_close()` cierra el archivo ZIP.

## Manual de usuario

El programa se puede ejecutar utilizando Makefile; mientras se está situado
en la misma carpeta que se encuentra el makefile, en la terminal de ejecuta
el comando ```make``` el cual se encargará de ejecutar los comandos
de compilación.

Seguidamente, una vez haya compilado el programa, se ejecutará el comando
```./bin/zippass_serial < ./tests/ejemplo.txt```
Cambiando "ejemplo.txt" por el archivo que se desee usar como entrada para el programa como por ejemplo lo podría ser ```input001.txt```
quedando de la siguiente manera: ```./bin/zippass_serial < ./tests/input001.txt```.

## Referencias

* Libzip: <https://libzip.org/>
