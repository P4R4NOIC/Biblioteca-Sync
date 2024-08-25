#include <pthread.h>
#include <stdio.h>

int bCounter = 0;  
pthread_mutex_t r; 
pthread_mutex_t g; 

// Semaforo
typedef struct {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  int counter;
} semaphore;

void wait(semaphore *sem) {
  pthread_mutex_lock(&(sem->mutex));
  while (sem->counter <= 0) {
    printf("Hilo: %lu en cola\n", (unsigned long)pthread_self());
    pthread_cond_wait(&(sem->cond), &(sem->mutex));
  }
  sem->counter--;
  pthread_mutex_unlock(&(sem->mutex));
}

void signal(semaphore *sem) {
  pthread_mutex_lock(&(sem->mutex));
  sem->counter++;
  pthread_cond_signal(&(sem->cond));
  pthread_mutex_unlock(&(sem->mutex));
}

// Barrera
//Estructura general de la barrera
typedef struct Barrier {
  int threadAmmount;     // cantidad de hilos que espera la barrera
  pthread_mutex_t barrierLock;  //bloqueador de hilos de mutex
  int maxThreads;   // cantidad total de hilos del programa
  pthread_cond_t conditional; //condicional que bloquea todo el programa hasta que lleguen los hilos necesarios 

} Barrier;


//Funcion que crea la barrera
void createBarrier(Barrier *barrier, int threadAmmount) {
  pthread_mutex_init(&(barrier->barrierLock), NULL);
  barrier->threadAmmount = threadAmmount;
  barrier->maxThreads = 0;
}

//Funcion que bloquea los hilos hasta que todos hayan llegado a la barrera
void barrierAwait(Barrier *barrier) {

  pthread_mutex_lock(&(barrier->barrierLock));

  barrier->maxThreads++;

  if (barrier->maxThreads < barrier->threadAmmount) {
    pthread_cond_wait(&(barrier->conditional), &(barrier->barrierLock));
  } else {

    barrier->maxThreads--;
    pthread_cond_broadcast(&(barrier->conditional));
  }
  pthread_mutex_unlock(&(barrier->barrierLock));
}


//Funcion que elimina la barrera
void deleteBarrier(Barrier *barrier) {
  pthread_mutex_destroy(&(barrier->barrierLock));
}


// Read/Write Lock

void beginRead(void) {
  pthread_mutex_lock(&r);
  bCounter++;
  if (bCounter == 1)
    pthread_mutex_lock(&g);
  pthread_mutex_unlock(&r);
}

void endRead(void) {
  pthread_mutex_lock(&r);
  bCounter--;
  if (bCounter == 0)
    pthread_mutex_unlock(&g);
  pthread_mutex_unlock(&r);
}

void beginWrite(void) { pthread_mutex_lock(&g); }

void endWrite(void) { pthread_mutex_unlock(&g); }