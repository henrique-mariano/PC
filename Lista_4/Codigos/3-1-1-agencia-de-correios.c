// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 3-1-1-agencia-de-correios.c
// atividade: 3.1.1

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_cond_t packets;
pthread_mutex_t mutex;
int countPackets;
pthread_t client, deliveryman;

typedef struct s_client {
    int num, i;
    struct s_client* next;
} Client;
Client* queue;

void *clientRoutine() {
    pthread_mutex_lock(&mutex);
    countPackets++;
    if (queue->num)
        printf("Cliente %d solicitou entrega de um pacote\n", queue->i), queue->num--;
    Client* last = queue;
    while(last->next != NULL)
        last = last->next;
    
    last->next = queue, queue = queue->next, last->next->next = NULL;
    if (countPackets >= 10) pthread_cond_signal(&packets);
    pthread_mutex_unlock(&mutex);
}

void *deliverymanRoutine() {
    pthread_mutex_lock(&mutex);
    do {
        pthread_cond_wait(&packets, &mutex);
        printf("Saindo para entregar 10 pacotes\n");
        sleep(2), countPackets = 0;
    } while (queue->num > 0);
    pthread_mutex_unlock(&mutex);
}

int main(){
    int n;
    countPackets = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&packets, NULL);

    do {
        printf("Número de clientes (1 a 30): ");
        scanf("%d", &n);
    } while (n < 1 || n > 30);
    pthread_create(&deliveryman, NULL, deliverymanRoutine, NULL);

    queue = (Client*) malloc(sizeof(Client)), queue->num = 30, queue->i = 0;
    Client* last = queue;
    for (int i = 0; i < n - 1; i++)
        last->next = (Client*) malloc(sizeof(Client)), last->next->i = last->i + 1, last->next->num = 30, last->next->next = NULL, last = last->next;
    
    while (queue->num > 0)
        pthread_create(&client, NULL, clientRoutine, NULL), pthread_join(client, NULL);

    pthread_join(deliveryman, NULL);
    last = queue;
    while (last != NULL) {
        Client* next = last->next;
        free(last), last = next;
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&packets);
    return 0;
}
