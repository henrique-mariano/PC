// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 2-1-1-divisao-de-tarefas.c
// atividade: 2.1.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* solve(void* args){
    double* x = (double*)args;
    double* ans = malloc(sizeof(double));
    *ans = (pow(*x, *(x + 2)) * *(x + 1));
    pthread_exit(ans);
}

int main() {
    pthread_t t1, t2;
    double x;
    void *ans1, *ans2;
    scanf("%lf", &x);
    double* args1 = malloc(sizeof(double) * 3);
    double* args2 = malloc(sizeof(double) * 3);
    *(args1) = x;
    *(args1 + 1) = 10;
    *(args1 + 2) = 2;
    *(args2) = x;
    *(args2 + 1) = 42;
    *(args2 + 2) = 3;
    pthread_create(&t1, NULL, solve, args1);
    pthread_create(&t2, NULL, solve, args2);
    pthread_join(t1, &ans1);
    pthread_join(t2, &ans2);
    printf("A resposta é: %.4lf\n", *(double*)ans1 + *(double*)ans2);
    free(args1);
    free(args2);
    free(ans1);
    free(ans2);
    return 0;
}