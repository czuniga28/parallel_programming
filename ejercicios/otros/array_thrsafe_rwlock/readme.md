# array_thrsafe_rwlock

Provea una segunda implementación thread-safe de su arreglo dinámico en C.
Provea un candado de lectura y escritura (pthread_rwlock_t) para cada instancia
del arreglo dinámico. Proteja el código de cada subrutina que no modifica el
arreglo bloqueando el candado para lectura. De la misma forma proteja el código
de cada subrutina que modifica bloqueando el candado para escritura.

Su implementación debe permitir al código de prueba del ejercicio anterior
correr correctamente sin generar fugas de memoria, accesos inválidos ni
condiciones de carrera:
