// autor: Henrique Mendes de Freitas Mariano
// arquivo: hello-fork.c
// atividade: 1.1.1

#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("Hello, fork!\n");
    return 0;
}