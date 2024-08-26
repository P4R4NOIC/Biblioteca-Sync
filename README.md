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

1. Descomente la función barrierExample.
2. Ingrese en el primer parámetro de la función la cantidad de hilos totales que tendrá el programa a la hora de ser ejecutado
3. Ingrese en el segundo parámetro de la función la cantidad de hilos que va a hacer esperar la barrera

Si quiere hacer su propio ejemplo de barrera es importante realizar lo siguiente:

1. Crear los hilos que vea necesarios para hacer que su programa funcione correctamente con utilizando pthread_t thread_id[totalThreads]
2. Crear una dato de tipo barrera utilizando el tipo de dato "Barrier"
3. Crear la barrera utilizando la función createBarrier
4. Crear los hilos y llamar a la función auxiliar del ejemplo en un ciclo for que empiece en cero y termine cuando se llegue a la cantidad total de hilos de la siguiente manera: pthread_create(&thread_id[i], NULL, barrierExampleFunc, (void*)&barrier);
5. Hacer otro ciclo for para unir los hilos una vez que todos hayan pasado la barrera utilizando la siguiente función:  pthread_join(thread_id[i], NULL);
6. Eliminar la barrera utilizando la función deleteBarrier

## Read-write_lock

Para usar el read-write lock realice lo siguiente:
Descomente la función readWriteExample(NULL) y corra el programa.

O sino realice lo siguiente:

1. Cree un lock básico en mutex con la variable r
2. Cree un lock básico en mutex con la variable g
3. Cree un hilo en el programa donde llamará a la función de lecturas, con los parametros (&tid[i], NULL, "FuncionDeLectura", NULL)
4. Cree un hilo en el programa donde llamará a la función de escrituras, con los parametros (&tid[i], NULL, "FuncionDeEscritura", NULL)
5. Dentro de su función de lectura, coloque la lectura de su variable compartida dentro de los métodos beginRead() y endRead()
6. Dentro de su función de escritura, coloque la escritura de su variable compartida dentro de los métodos beginWrite() y endWrite()
7. En la misma función donde creó los locks, coloque joins para los hilos "r" y "g"
8. Destruya los mutex de "r" y "g" para liberar la memoria utilizada.