#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();

    printf("Meu pid é: %d\n", getpid());

    if (pid) {
        wait(NULL);
        printf("Processo filho terminou.\n");
    } else {
        printf("Filho saindo...\n");
        exit(0);
    }

    printf("Irei imprimir somente uma vez, pois o filho já terminou.\n");
    execl("/bin/ls","ls",".", NULL);
    printf("Meu processo está morto! Tens o que é necessário para imprimir?");

    return 0;
}