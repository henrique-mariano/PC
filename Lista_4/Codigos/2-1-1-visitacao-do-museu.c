// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 2-1-1-visitacao-do-museu.c
// atividade: 2.1.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMTURISTAS 90
#define CAPACIDADE_SALA1 10
#define CAPACIDADE_SALA2 6
#define CAPACIDADE_SALA3 18

sem_t sala1;
sem_t sala2;
sem_t sala3;
sem_t guia;

void *turista(void *id){
    int i = *(int *) id;
    int sala1_completa;
    int sala2_completa;
    int sala3_completa;

    sem_wait(&sala1);
    sem_getvalue(&sala1, &sala1_completa);
    sem_wait(&guia);
    if(sala1_completa == 0){
        printf("Sala 1 completa, começando explicação.\n");
        sleep(2);
    }
    sem_post(&guia);
    sem_post(&sala1);

    sem_wait(&sala2);
    sem_getvalue(&sala2, &sala2_completa);
    sem_wait(&guia);
    if(sala2_completa == 0){
        printf("Sala 2 completa, começando explicação.\n");
        sleep(2);
    }
    sem_post(&guia);
    sem_post(&sala2);

    sem_wait(&sala3);
    sem_getvalue(&sala3, &sala3_completa);
    sem_wait(&guia);
    if(sala3_completa == 0){
        printf("Sala 3 completa, começando explicação.\n");
        sleep(2);
    }
    sem_post(&guia);
    sem_post(&sala3);
}

int main(){
    pthread_t t[NUMTURISTAS];
    int *id;
    sem_init(&sala1, 0, CAPACIDADE_SALA1);
    sem_init(&sala2, 0, CAPACIDADE_SALA2);
    sem_init(&sala3, 0, CAPACIDADE_SALA3);
    sem_init(&guia, 0, 1);

    for(int i = 0; i < NUMTURISTAS; i++){
        id = (int *) calloc(1, sizeof(int));
        *id = i;
        pthread_create(&t[(*id)], NULL, turista, (void *) id);
    }

    for(int i = 0; i < NUMTURISTAS; i++){
        pthread_join(t[i], NULL);
    }

    sem_destroy(&sala1);
    sem_destroy(&sala2);
    sem_destroy(&sala3);
    sem_destroy(&guia);
    return 0;
}