// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 2-1-1-lock-recursivo.c
// atividade: 2.1.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_mutexattr_t attr;

void bar() {
    printf("Tentando pegar o lock de novo.\n");
    pthread_mutex_lock(&mutex);
    printf("Estou com duplo acesso?\n");
    pthread_mutex_unlock(&mutex);
}
void *foo(void *empty){
    pthread_mutex_lock(&mutex);
    printf("Acesso a região crı́tica.\n");
    bar();
    pthread_mutex_unlock(&mutex);
}
int main() {
    pthread_t t;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&mutex, &attr);
    pthread_create(&t, NULL, foo, NULL);
    pthread_join(t, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_attr_destroy(&attr);

    return 0;
}