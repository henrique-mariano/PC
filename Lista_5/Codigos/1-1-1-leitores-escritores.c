// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 1-1-1-controle-de-assinatura.c
// atividade: 1.1.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define NUMLEITORES 10
#define NUMESCRITORES 3

char BD[10000];

int count = 1;

pthread_mutex_t mutex;

sem_t semaforo;

void *ler(void *args){
    while(1){
        sem_wait(&semaforo);
        printf("%s\n", BD);
        sem_post(&semaforo);
        sleep(rand() % 4);
    }
}

void *escrever(void *args){
    int *id = (int *) args;

    for(int i = 0; i < 1000; i++){
        pthread_mutex_lock(&mutex);
        BD[count] = (char) (*id + '0');
        count++;
        BD[count] = '\0';
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    free(id);
    pthread_exit(NULL);
}

int main(){

    pthread_t l[NUMLEITORES], e[NUMESCRITORES];
    
    int *id = NULL;

    BD[0] = 'A';
    BD[1] = '\0';

    sem_init(&semaforo, 0, 10);

    srand(time(0));

    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NUMESCRITORES; i++){
        id = (int *) calloc(1, sizeof(int));
        *id = i;
        pthread_create(&e[(*id)], NULL, escrever, (void *) id);
    }

    for(int j = 0; j < NUMLEITORES; j++){
        id = (int *) calloc(1, sizeof(int));
        *id = j;
        pthread_create(&l[(*id)], NULL, ler, (void *) id);
    }

    for(int k = 0; k < NUMESCRITORES; k++)
        pthread_join(e[k], NULL);

    for(int k = 0; k < NUMLEITORES; k++)
        pthread_join(l[k], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaforo);

    return 0;
}