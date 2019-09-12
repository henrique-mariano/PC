// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 1-1-1-hello-threads.c
// atividade: 1.1.1

#include <stdio.h>
#include <pthread.h>

void *rotina(){
    printf("Olá, sou uma thread\n");
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, rotina, NULL);
    pthread_create(&t, NULL, rotina, NULL);
    printf("Olá, sou a main.\n");
    return 0;
}