// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 2-1-4-conta-bancaria.c
// atividade: 2.1.4

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

const int NUMTHREADS = 3;
int contabancaria = 0, vez = 0;

int escolhendo[3] = {0, 0, 0};

int numero[3] = {0, 0, 0};

// void djikstra(int processo){
//     int j;
//     while(true){
//         int val_max = -1;
//         escolhendo[processo] = 1;

//         val_max = max(numero[0], numero[1]);
//         val_max = max(val_max, numero[2]);

//         numero[processo] = 1 + val_max;
//         escolhendo[processo] = 0;

//         for(j = 0; j < 3; j++){
//             while(escolhendo[j] != 0){}
//             while(numero[j] != 0 && ((numero[j] < numero[processo]) || ((numero[j] == numero[processo]) && j < processo))){}
//         }
//         // sessao critica

//         numero[processo] = 0;
//         //sessao nao critica
//     }
// }

void* deposito(void* arg){
    int i = *((int *) arg);
    int j;
    while(true){
        int val_max = -1;
        escolhendo[i] = 1;

        val_max = max(numero[0], numero[1]);
        val_max = max(val_max, numero[2]);

        numero[i] = 1 + val_max;
        escolhendo[i] = 0;

        for(j = 0; j < NUMTHREADS; j++){
            while(escolhendo[j] != 0){}
            while(numero[j] != 0 && ((numero[j] < numero[i]) || ((numero[j] == numero[i]) && j < i))){}
        }
        // sessao critica
        contabancaria += 20;
        printf("Contabancaria: %d i: %d\n", contabancaria, i);
        numero[i] = 0;
        //sessao nao critica
    }
}

void* retirada(void* arg){
    int i = *((int *) arg);
    int j;
    while(true){
        int val_max = -1;
        escolhendo[i] = 1;

        val_max = max(numero[0], numero[1]);
        val_max = max(val_max, numero[2]);

        numero[i] = 1 + val_max;
        escolhendo[i] = 0;

        for(j = 0; j < NUMTHREADS; j++){
            while(escolhendo[j] != 0){}
            while(numero[j] != 0 && numero[j] < numero[i]){}
        }
        // sessao critica
        if(contabancaria - 10 >= 0) contabancaria += -10;
        printf("Contabancaria: %d i: %d\n", contabancaria, i);
        numero[i] = 0;
        //sessao nao critica
    }
}

int main(){
    pthread_t threads[NUMTHREADS];
    int *arg_1 = malloc(sizeof(int));
    int *arg_2 = malloc(sizeof(int));
    int *arg_3 = malloc(sizeof(int));

    *arg_1 = 0;
    *arg_2 = 1;
    *arg_3 = 2;
    
    pthread_create(&threads[0], NULL, deposito, (void *) arg_1);
    pthread_create(&threads[1], NULL, retirada, (void *) arg_2);
    pthread_create(&threads[2], NULL, retirada, (void *) arg_3);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    free(arg_1);
    free(arg_2);
    free(arg_3);

    return 0;
}