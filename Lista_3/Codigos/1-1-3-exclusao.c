// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 1-1-3       -exclusao.c
// atividade: 1.1.3

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

const int NUMTHREADS = 10;
int contador = 0, vez = 0;
int interessados[10];

void enter_region(int processo){
    int outro = -1;
    int i = 0;
    interessados[processo] = 0;
    while (!~outro && i < NUMTHREADS)
        outro = interessados[i] == 1? i : -1, i++;
    
    interessados[processo] = 1;
    vez = processo;
    while (vez == processo && interessados[outro] == 1) {}    
}

void out_region(int processo){
    interessados[processo] = 0;
}

void* incrementos(void* u){
    int i = *((int*)u);
    enter_region(i);
    for(int i = 0; i < 100; i++)
        contador++;
    out_region(i);
}

int main(){
    memset(interessados, 0, sizeof(interessados));
    pthread_t threads[NUMTHREADS];

    for (int i = 0; i < NUMTHREADS; i++)
        pthread_create(&threads[i], NULL, incrementos, (void*)&i);
    
    for(int i = 0; i < NUMTHREADS; i++)
        pthread_join(threads[i], NULL);

    
    printf("Contador = %d\n", contador);

    return 0;
}