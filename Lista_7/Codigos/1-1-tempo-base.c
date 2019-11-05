// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 1-1-tempo-base.c
// atividade: 1.1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// #include <omp.h>

long long int somavalores(int *valores, int n) {
    long long int soma = 0;
    
    for (int i = 0; i < n; i++) {
        soma = soma + valores[i];
    }

    return soma;
}

int main() {
    long long int i, n, soma;
    time_t inicio, fim;
    int *valores;
    // scanf("%lld", &n);
    n = 100000000;

    valores = (int *) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) { 
        valores[i] = 1;
    }

    inicio = time(NULL);
    soma = somavalores(valores, n);
    fim = time(NULL);
    
    printf("Soma: %lld - %s - wall time: %f\n", soma, soma == n ? "ok" : "falhou", difftime(fim, inicio));

    free(valores);
    valores = NULL;

    return 0;
}