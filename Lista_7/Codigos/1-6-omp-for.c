// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: 1-6-omp-for.c
// atividade: 1.6
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long int somavalores(int *valores, int n) {
    long long int soma = 0;
    long long int soma_parcial = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            #pragma omp atomic
                soma = soma + valores[i];
        }
            
    return soma;
}

int main() {
    long long int i, n, soma;
    double inicio = 0, fim = 0;
    int *valores;
    // scanf("%lld", &n);
    n = 100000000;
    valores = (int *) malloc(n * sizeof(int));
    
    for (i = 0; i < n; i++) {
        valores[i] = 1;
    }
    {
        inicio = omp_get_wtime();
        soma = somavalores(valores, n);
        fim = omp_get_wtime();
    }
    
    printf("Soma: %lld - %s - wall time: %lf\n", soma, soma == n ? "ok" : "falhou", (fim - inicio));

    free(valores);
    valores = NULL;
    
    return 0;
}