// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 4-1-2-corrida.c
// atividade: 4.1.2

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int largada = 3;

void* corrida(void* i) {
    int ID = *((int*)i);
    while (largada != 0)
        continue;
    printf("Sou carro ID %d e terminei a corrida\n", ID);
    pthread_exit(NULL);
}

void* juizdelargada(){
    while(largada) {
        largada--;
        if (!largada) break;
        sleep(rand() % 10);
    }

    printf("GO!\n");
    pthread_exit(NULL);
}

int main(){
    const int NUMTHREADS = 10;
    pthread_t threads[NUMTHREADS + 1];

    for (int i = 0; i < NUMTHREADS; i++)
        pthread_create(&threads[i], NULL, corrida, (void*)&i);

    pthread_create(&threads[NUMTHREADS], NULL, juizdelargada, NULL);
    
    for(int i = 0; i <= NUMTHREADS; i++)
        pthread_join(threads[i], NULL);
    return 0;
}