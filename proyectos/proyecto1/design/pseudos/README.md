# Design Factorizacion Primos y Goldbach  

## Descripción de los pseudos 

- Pseudo Factorización Primos:

Para el diseño de la factorizacion primos lo que se realiza es tomar el vector de números como entrada y descomponer cada número en factores primos. Para cada número, se inicializa un vector de factores y se verifica si el número es 0, negativo o igual a 1, agregando tuplas especificas para el manejo de la salida en la webApp. 

Se calcula el maximo de los numeros recibidos y se utiliza la Criba de Eratóstenes para calcular los números primos hasta ese numero. Luego, se calculan los factores diviendo el número actual con los primos obtenidos en la criba, se obtienen los factores y los exponentes. Al final se almacenan los vectores de tuplas en un vector de resultados, que contiene las factorizaciones de cada número.


- Pseudo Goldbach: 

Para la ConjeturaGoldbach trabaja con una lista de sumas como entrada. Para cada suma, verifica si es un número par o impar. Utiliza la Criba de Eratóstenes para encontrar números primos hasta el valor de la suma y, mediante un mapa (unordered_map) se realiza un seguimiento de los números primos disponibles y sus posiciones en la lista de números primos generados. Luego, busca combinaciones de números primos que, al sumarse, igualen el número. Los resultados se almacenan en resultados. Si una suma es menor o igual a 5, se agrega [0, 0] a los resultados para indicar que no hay combinaciones posibles en ese caso.