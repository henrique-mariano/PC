// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 3-1-1-incremento-atomico.c
// atividade: 3.1.1

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile int contador = 0;

void* incrementos(){
    for(int i = 0; i < 100; i++)
        __sync_fetch_and_add(&contador, 1);
}

int main(){
    const int NUMTHREADS = 10;
    pthread_t threads[NUMTHREADS];

    for (int i = 0; i < NUMTHREADS; i++)
        pthread_create(&threads[i], NULL, incrementos, NULL);
    
    for(int i = 0; i < NUMTHREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Contador = %d\n", contador);

    return 0;
}