#include <stdio.h>
#include <pthread.h>
#include "sync.h"

int sharedValue = 0;

//Función ejemplo para hilos de lecturas
void *reader_thread(void *arg) {
  int i;
  for (i = 0; i < 5; i++) {
    beginRead();  // Llamada a la función de inicio de lectura
    printf("Reader: Value = %d\n", sharedValue);
    endRead();   // Llamada a la función de fin de lectura
    sleep(1); // Sleep para simular tiempo de lectura
  }
  return NULL;
}

//Función ejemplo para hilos de escrituras
void *writer_thread(void *arg) {
  int i;
  for (i = 0; i < 5; i++) {
    beginWrite(); // Llamada a la función de inicio de escritura
    sharedValue += 10;
    printf("Writer: Value updated to %d\n", sharedValue);
    endWrite();  //Llamada a la función de finalización de escritura
    sleep(1);  // Sleep para simular tiempo de escritura
  }
  return NULL;
}

void readWriteExample(void *arg){
  pthread_t tid[3];
  
  pthread_mutex_init(&r, NULL);  
  pthread_mutex_init(&g, NULL); 

  pthread_create(&tid[0], NULL, reader_thread, NULL); 
  pthread_create(&tid[1], NULL, writer_thread, NULL);
  pthread_create(&tid[2], NULL, writer_thread, NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);

  pthread_mutex_destroy(&r);  
  pthread_mutex_destroy(&g);
}
//Función auxiliar que indica los hilos que han llegado a la barrera y luego indica cuando han pasado, despues de correr barrierAwait()
void *barrierExampleFunc(void *arg) { 
  Barrier *barrier = (Barrier *)arg;
  printf("thread %ld is waiting at the barrier\n", pthread_self());
  barrierAwait(barrier);
  printf("The barrier is lifted, the thread %ld is running now\n",
         pthread_self());
  return NULL;
}

//Ejemplo de uso de barrera de hilos.
void barrierExample(int totalThreads, int barrierThreads) {
  
  pthread_t thread_id[totalThreads];
  Barrier barrier;

  createBarrier(&barrier, barrierThreads);
  for (int i = 0; i < totalThreads; i++){

      pthread_create(&thread_id[i], NULL, barrierExampleFunc, (void*)&barrier);
  }
  
  for (int i = 0; i < totalThreads; i++){

      pthread_join(thread_id[i], NULL);
  }

  deleteBarrier(&barrier);
  printf("Thread barrier is lifted\n"); 
  
}

void* payPhone(void* arg) {
    semaphore* sem = (semaphore*)arg;

    wait(sem);
    printf("Wcounter: %d\n", sem->counter);
    for(int r = 0; r < 20; r++) {
      if(r==5){
        printf("%lu - usando la cabina...\n", 
          (unsigned long)pthread_self());
      }
    }
    signal(sem);
    printf("Scounter: %d\n", sem->counter);
    return NULL;
}

void semaphoreExample(int n, int hilos){
  semaphore sem;
  pthread_mutex_init(&(sem.mutex), NULL);
  pthread_cond_init(&(sem.cond), NULL);
  sem.counter = n;

  pthread_t tid[hilos];

  for (int t = 0; t < hilos; t++){
     pthread_create(&tid[t], NULL, (void *)payPhone,
                    (void *)&sem);
  }

  for (int t = 0; t < hilos; t++){
     pthread_join(tid[t], NULL);
  }
}

int main(void){
  //readWriteExample(NULL);
  //barrierExample(2,3);//La primera entrada son el total de threads que va a tener el programa, la segunda entrada son la cantidad de threads que va a esperar la barrera, si la cantidad de threads de la barrera es mayor que la cantidad de threads total el programa se va a bloquear y no va a dejar pasar ningun thread
  //semaphoreExample(3, 25);//la primera entrada es el numero de hilos que el semaforo permitira usar un recurso, el segundo parametro es la cantidad de hilos que se van a crear.

  return 0;
}

