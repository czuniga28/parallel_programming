# Ejercicio 30 [signaling_w]

Generalice el patrón de aviso (signaling) para dada una cantidad arbitraria w de
hilos que ejecutan la instrucción a, lo hagan en el orden del número de hilo.
Por ejemplo, si ai es la ejecución de la instrucción statement a por parte del
hilo con número i, entonces se asegure que siempre se ejecute la secuencia
a0 < a1 < a2 < a3 < …​ < aw.
