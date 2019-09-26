// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 2-1-1-conta-bancaria.c
// atividade: 2.1.1

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

const int NUMTHREADS = 2;
int contabancaria = 0, vez = 0;

bool interessados[2] = {false, false};

void enter_region(int processo){
    int outro;
    outro = 1 - processo;
    interessados[processo] = true;
    vez = processo;
    while(vez == processo && interessados[outro] == true) {}
}

void out_region(int processo){
    interessados[processo] = false;
}

void* deposito(void* arg){
    int i = *((int *) arg);
    while(true){
        enter_region(i);
        contabancaria += 20;
        printf("Contabancaria: %d\n", contabancaria);
        out_region(i);
    }
}

void* retirada(void* arg){
    int i = *((int *) arg + 1);
    while(true){
        enter_region(i);
        if(contabancaria - 10 >= 0) contabancaria += -10;
        printf("Contabancaria: %d\n", contabancaria);
        out_region(i);
    }
}

int main(){
    pthread_t threads[NUMTHREADS];
    int *arg = malloc(sizeof(int) * 2);

    *arg = 0;
    *(arg + 1) = 1;
    
    pthread_create(&threads[0], NULL, deposito, (void *) arg);
    pthread_create(&threads[1], NULL, retirada, (void *) arg);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    free(arg);
    return 0;
}