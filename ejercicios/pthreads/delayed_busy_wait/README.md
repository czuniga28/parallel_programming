# delayed_busy_wait

Espera activa con retraso. ¿Se corrige el problema de la espera activa si en lugar de tener un ciclo vacío, se espera un cierto tiempo? Copie su carpeta ejemplos/pthreads/hello_order_busywait a ejercicios/pthreads/delayed_busy_wait. Permita que el usuario pueda invocar su programa dos argumentos de línea de comandos: la cantidad de hilos a crear, y la cantidad de microsegundos a esperar cuando no es el turno del hilo de ejecución.

Espera activa con retraso constante. Si no es el turno de un hilo, éste espera una cantidad constante de microsegundos, algo como:

```bash
// Constant delayed busy waiting: wait until it is my turn
while (next_thread < my_thread_id) {
  usleep(delay);
}
```

Recuerde probar la calidad de su código (sanitizers, linter). Luego ejecute al menos tres veces su solución (sin sanitizers) con la cantidad máxima de hilos de ejecución que su sistema operativo le permite crear y una espera de 50µs. Escriba en el readme.md del ejercicio la mayor de las duraciones que obtuvo de sus corridas. ¿Hubo una mejora de la espera constante respecto a la espera activa pura?

Espera activa con retraso pseudoaleatorio. Altere su solución al ejercicio para que en lugar de esperar exactamente la cantidad de microsegundos indicada por el usuario, espere por una cantidad pseudoaleatoria de microsegundos cuyo límite es el número indicado por el usuario en el segundo argumento de línea de comandos. Sugerencia: puede usar compilación condicional para implementar esta variación. La espera varía en cada iteración del ciclo de espera activa, algo como:

```bash
// Random delayed busy waiting: wait until it is my turn
while (next_thread < my_thread_id) {
  const unsigned my_delay = rand_r(&my_seed) % max_delay;
  usleep(my_delay);
}
```

Ejecute al menos tres veces su solución pseudoaleatoria con la cantidad máxima de hilos y un máximo de espera de 50µs. Tome la mayor de las duraciones. ¿Hubo una mejora de la espera pseudoaleatoria respecto a la espera constante?

Comparación de las esperas. ¿Mejora el tiempo de ejecución de los dos tipos de esperas (constante y pseudoaleatoria) si disminuye o incrementa la espera máxima de los hilos? Haga al menos un par de ejecuciones con al menos los siguientes tiempos de espera:

```bash
    1µs usleep: 2.029924839s     random: 2.045553887s

    5µs usleep: 2.019666262s     random: 2.002043521s

    25µs usleep: 2.959491728s    random: 2.002774797s

    50µs usleep: 3.910595129s    random: 2.056468830s

    75µs usleep: 3.960725610s    random: 2.954970820s

    100µs usleep: 4.029772881s   random: 2.988011700s
```

Sugerencia: si hay varios compañeros(as) trabajando el mismo ejercicio en el laboratorio, escojan tiempos diferentes y compartan los resultados. Pueden crear una gráfica en un documento compartido. Agreguen más tiempos de ejecución si hay más de 6 integrantes.

Cree una gráfica donde el eje-x son las duraciones dadas por argumento al programa. El eje-y son los tiempos de ejecución de los programas. El gráfico tendrá dos series, una para la espera constante y otra para la espera pseudoaleatoria.

Agregue la gráfica al readme.md del ejercicio y una discusión de a lo sumo dos párrafos. Indique cuál fue el mejor tiempo máximo de espera obtenido y los efectos de disminuir o incrementarlo. Conjeture y trate de explicar por qué ocurre este comportamiento. Finalmente indique si la espera activa con retraso es una solución óptima, y en caso negativo, provea una idea que pueda lograr este ideal.

## Grafica de comparacion

![grafica](grafica_comparación.png)
A partir de las pruebas y la grafica se puede inferir que la espera activa pseudoaleatoria fue mas rapida que su contraparte, esto se debe a que posiblemente ningun caso pseudoaleatoria llego al maximo del delay. No es una solucion optima ya que el hilo sigue aprovechandose de los recursos del nucleo en cual esta realizando la espera, asimismo seria mejor otra opcion donde no se tenga que acceder o modificar valores en paralelo en una misma direccion de memoria para evitar condiciones de carrera.

## Estudiantes

Christopher Zuniga C28730
Andres Diaz C22576