// autor: Henrique Mendes de Freitas Mariano
// arquivo: pid.c
// atividade: 2.1

#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork() && (fork() || fork());
    fork();
    putchar('.');
    
    return 0;
}