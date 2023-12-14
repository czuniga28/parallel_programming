# Sem_vs_condsafe

Ejecute al menos tres veces los códigos de Ejemplo 7 (imprimir en orden con
semáforos) y Ejemplo 8 (imprimir en orden con seguridad condicional) con tantos hilos como su sistema operativo permite. Reporte en su readme.md las tres duraciones de cada solución. Tome la menor duración de las tres corridas de cada versión. ¿Cuál solución realiza su trabajo en menor tiempo? Discuta en máximo un párrafo cuál podría ser la causa de este comportamiento.

## hello_order_cond_safe

- **Tiempo 1:** 1.457990633s
- **Tiempo 2:** 1.143553827s
- **Tiempo 3:** 0.981449935s

## hello_order_semaphor

- **Tiempo 1:** 3.243057696s
- **Tiempo 2:** 3.709250445s
- **Tiempo 3:** 3.791240901s

## Resultados

El menor tiempo registrado fue el tiempo 3 de **hello_order_cond_safe**, esto se puede explicar ya que al haber "n" interrupciones, se ejecutan todos los threads concurrentemente.
