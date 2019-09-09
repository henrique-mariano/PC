// autor: Henrique Mendes de Freitas Mariano
// arquivo: n_processos.c
// atividade: 3.1.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        __pid_t pid = fork();
        wait(NULL);
        if(pid == 0) {
            printf("Sou o processo %d e o PID do meu criador é %d\n", getpid(), getppid());
            exit(0);
        }
    }

    return 0;
}
