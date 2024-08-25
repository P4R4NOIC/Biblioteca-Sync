"Biblioteca Sync"

Una biblioteca que posee las estructuras de sincronización semáforo, barrera read/write lock realizadas con hilos y mutex.

  Autores:
  Dylan Mora Corrales
  Fernando Gross Hernández
  Roberto Vindas Hernández

## tabla de contenidos
- [Semaforo](#semaforo)
- [Barrera](#barrera)
- [Read-write_lock](#read-write_lock)


## Semaforo

Para usar el semaforo realice lo siguiente:

1. Descomente la función semaphoreExample.
2. Ingrese en el primer parametro la cantidad de hilos que se les dara acceso al recurso.
3. Ingrese en el segundo parametro la cantidad de hilos que utilizará.

## Barrera

Para usar la barrera realice lo siguiente:

1. 

## Read-write_lock

Para usar el read-write lock realice lo siguiente:

1. Cree un lock básico en mutex con la variable r
2. Cree un lock básico en mutex con la variable g
3. Cree un hilo en el programa donde llamará a la función de lecturas, con los parametros (&tid[i], NULL, "FuncionDeLectura", NULL)
4. Cree un hilo en el programa donde llamará a la función de escrituras, con los parametros (&tid[i], NULL, "FuncionDeEscritura", NULL)
5. Dentro de su función de lectura, coloque la lectura de su variable compartida dentro de los métodos beginRead() y endRead()
6. Dentro de su función de escritura, coloque la escritura de su variable compartida dentro de los métodos beginWrite() y endWrite()
7. En la misma función donde creó los locks, coloque joins para los hilos "r" y "g"
8. Destruya los mutex de "r" y "g" para liberar la memoria utilizada.