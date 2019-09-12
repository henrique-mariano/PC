// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 3-1-1-n-threads.c
// atividade: 3.1.1

#include <stdio.h>
#include <pthread.h>

void *contador(void *id){
    long int tid = (long int )id;
    for(int i = 0; i < 5; i++) printf("Sou a thread TID %ld e estou no número %d\n", tid, i);
}
int main(){
    const int NUMTHREADS = 10;
    pthread_t threads[NUMTHREADS];
    for (long int i = 0; i < NUMTHREADS; i++)
        pthread_create(&threads[i], NULL, contador, (void *) i);
    for (long int i = 0; i < NUMTHREADS; i++)
        pthread_join(threads[i], NULL);
    return 0;
}