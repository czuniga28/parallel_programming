# concurrente23b-christopher_zuniga

## Glossary

### Programacion serial

Programacion vista en progra I y progra II. Si se tienen varias tareas que
ejecutar, estas mismas lo van a hacer una despues de la otra.

Si se tienen 2 tareas (por ejemplo), se tiene la garantia de que la **2**
no se va a ejecutar hasta que termine la tarea **1**. O sea que las
instruccuiones son secuenciales.

### Programacion concurrente

Lo que no es serial. Todo lo que no es serial, es concurrente(se puede tomar
como un metaparadigma). Se podría decir que se dividen las tareas en muchos
pedazos y estos mismos se intercalan entre sí.

Por ejemplo, los cursos que se llevan durante el semestre **no** son seriales,
pues se llevan todos al mismo tiempo y no uno después del otro

### Programacion paralela

En la programacion paralela las tareas se están ejecutando al mismo tiempo
de forma simultanea.

Por ejemplo, mientras vemos una pelicula podemos estar comiendo al mismo tiempo
a la vez que respiramos. Son tareas que no se necesita cambiar el contexto para
alternar entre una y la otra ni mucho menos serializarlas.

El paralelismo es una forma de concurrencia.

### Concurrencia de tareas

Los problemas en el mundo concurrente se pueden resolver con cambios de
contexto y eventos. La idea principal es realizar una tarea, pero no enfocarse
simplemente en esta, sino estar atento a otros inputs externos que puedan
modificar el proceso de como esta misma es llevada a cabo.

Si se tienen varias tareas que iban a ser planteadas de forma lineal,
refiriendo esto a que cuando terminara una se iniciaba la otra, con la
concurrencia de tareas lo que se propone es dividirlas en pedazos de menor
tamaño e irlos trabajando "interrumpidamente" de forma que en medio de cada
pedazo se pueden atender eventos que vayan surgiendo en el camino.
(Randall concurrente)

### Paralelismo de datos

Cuando dos hilos ejecutan instrucciones idealmente al mismo tiempo.

Tiene forma de un for creando una cantidad definida de datos que hacen la misma
tarea.

### Hilo de ejecucion

Si los hilos de ejecucion son como personas, necesitamos una estacion de trabajo
(stack frame). Se puede definir como un arreglo  de valores que el sistema
operativo carga en los registros de una CPU y eprmiten ejecutar codigo en ella.

### Indeterminismo

La concurrencia genera indeterminismo. El indeterminismo es que uno
no puede predecir en que orden que se ejecutan las instrucciones concurrentes.
Siempre que uno tiene concurrencia, implicitamente, existe el indeterminismo.
Uno no puede predecir el orden de las instrucciones.

### Memoria privada y compartida

#### Memoria privada

Es memoria que un hilo tiene y el otro no, se puede modificar sin alterar a
a otros con los cambios que le haga. Todos los hilos obligatoriamente tienen
memoria privada.

#### Memoria compartida

Se basa en compartir los datos entre todos los hilos en vez de duplicarlo o
copiarlo. Todos en el equipo tienen el mismo dato

### Espera activa

Es un ciclo de ejecucion que espera repetitivamente hasta que una condicion
se haga falsa. La espera activa puede garantizar que nadie mas esta ejecutando
cierta tarea.

Probablemente el codigo mas malicioso y nocivo que se haya visto en lo que se
lleva de carrera.

### Condición de carrera

Es cuando 2 hilos quieren accesar y modificar la misma direccion de memoria al
mismo tiempo. Es una modificacion concurrente de memoria compartida.

Tienen que existir 3 condiciones  fundamentales para que exista una condicion de
carrera: Tiene que haber modificacion (operador de asignacion), tiene que ser
concurrente y por ultimo la modificacion tiene que ser en memoria compartida.

### Control de concurrencia

Se refiere a distintos mecanismo que se utilizan para evitar condiciones de
carrera. Ej: el uso de semaforos, mutex, barreras, etc...

### Seguridad condicional

Cuando se distribuyen los datos entre los hilos de forma que se asegura
que estos no sean accesibles unos entre otros. Esto hace que no exista una
condicion de carrera y no se necesite control de concurrencia.

### Exclusión mutua

Solo un hilo va a ejecutar la/las instrucciones que esten protegidas por un
mutex. Excluye a la region critica, e implementa una espera inactiva

### Semáforo

Un semaforo es un entero con signo que cumple 3 caracteristicas:

- Cuando se crea se inicializa con un entero cualquiera; despues de eso solo
hay 2 operaciones permitidas: Incrementar en 1 **(signal)** y decrementar en 1
**(wait)**.

- Cuando un hilo decrementa un semaforo, si el resultado es negativo, el hilos
es bloqueado y no puede continuar hasta que otro hilo incremente el semaforo.

- Cuando un hilo incrementa un semafoto, si hay otros hilos esperando, uno
de ellos sera desbloqueado. Los 2 seguiran ejecutandose concurrentemente.

### Barrera

La barrera se puede ver como una aguja de paso. La barrera tiene 2 enteros
asociados, uno que es el limite, y el otro, cuantos hilos estan esperando,
para que se levante la barrera se tiene que cumplir la condicion de que el
numero de hilos esperando sea el mismo que el limite. El orden de ejecucion es
indeterministico.

### Variable de condición

Es un mecanismo de control de concurrencia parecido a una barrera que deja pasar
a todos los procesos o hilos de ejecuccion cuando se le indica. La diferencia es
que en este caso, los hilos de ejecucion no se quedan esperando a que todos
lleguen, sino que se quedan esperando a que se les indique que pueden continuar.
luego de eso tienen un momento para pasa y la "barrera" se cierra de nuevo hasta
que se vuelva a

### Candado de lectura y escritura

### Descomposición

Division de un problema en subproblemas mas pequeños que pueden ser resueltos de
forma independiente.

### Mapeo

Asignar las tareas previamente descompuestas a los ejecutantes que tengo. El
mapeo permite tener lo que se conoce como un equipo de trabajo que es de tam.
finito y eso nos permite ajustarlo al paralelismo que dispone la maquina.

### Incremento de velocidad

### Comunicacion punto a punto entre procesos

### Comunicacion colectiva entre procesos

### Reduccion
