// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 3-1-2-escalonador.c
// atividade: 3.1.2

#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void *contador(void *id){
    long int tid = (long int )id;
    for(int i = 0; i < 5; i++) {
        printf("Sou a thread TID %ld e estou no número %d\n", tid, i);
        sched_yield();
    }
}

int main(){
    cpu_set_t mascaranucleos;
    CPU_ZERO(&mascaranucleos);
    CPU_SET(0, &mascaranucleos);
    sched_setaffinity(0, sizeof(cpu_set_t), &mascaranucleos);
    const int NUMTHREADS = 10;
    pthread_t threads[NUMTHREADS];
    for (long int i = 0; i < NUMTHREADS; i++)
        pthread_create(&threads[i], NULL, contador, (void *) i);
    for (long int i = 0; i < NUMTHREADS; i++)
        pthread_join(threads[i], NULL);
    return 0;
}