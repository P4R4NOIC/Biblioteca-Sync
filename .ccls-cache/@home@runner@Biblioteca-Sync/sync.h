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
typedef struct Barrier {
  int threadAmmount;
  pthread_mutex_t barrierLock;
  int maxThreads;
  pthread_cond_t conditional;

} Barrier;

void createBarrier(Barrier *barrier, int threadAmmount) {
  pthread_mutex_init(&(barrier->barrierLock), NULL);
  barrier->threadAmmount = threadAmmount;
  barrier->maxThreads = 0;
}

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

void deleteBarrier(Barrier *barrier) {
  pthread_mutex_destroy(&(barrier->barrierLock));
}

void *thread_func(void *arg) {
  Barrier *barrier = (Barrier *)arg;
  printf("thread %ld is waiting at the barrier\n", pthread_self());
  barrierAwait(barrier);
  printf("The barrier is lifted, the thread %ld is running now\n",
         pthread_self());
  return NULL;
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