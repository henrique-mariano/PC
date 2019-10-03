// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 1-1-1-controle-de-assinatura.c
// atividade: 1.1.1

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int assinaturas = 1;

int *lista_chamada;

pthread_mutex_t possedalista;

void* aluno(void *id){
    int i = *(int *) id;
    pthread_mutex_init(&possedalista, NULL);
    pthread_mutex_lock(&possedalista);
    lista_chamada[assinaturas] = i;
    assinaturas++;
    sleep(1);
    printf("Aluno %d assinou a lista\n", i);
    free(id);
    pthread_mutex_unlock(&possedalista);
    pthread_exit(NULL);
}

int main(){
    int n;
    scanf("%d", &n);
    lista_chamada = (int *) calloc(n + 1, sizeof(int));
    pthread_t threads[n + 1];
    for(int j = 1; j <= n; j++) {
        int *i = calloc(1, sizeof(int));
        *i = j;
        pthread_create(&threads[(*i)], NULL, aluno, (void *) i);
    }

    for(int k = 1; k <= n; k++)
        pthread_join(threads[k], NULL);

    printf("A ordem de assinatura da lista foi:");
    for(int i = 1; i <= n; i++){
        printf(" %d", lista_chamada[i]);
    }
    printf("\n");
    free(lista_chamada);
    pthread_mutex_destroy(&possedalista);
    return 0;
}