// autor: Henrique Mendes de Freitas Mariano
// arquivo: eventos_processos.c
// atividade: 3.1.2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    __pid_t pid1 = fork();
    
    if(pid1) {
        printf("Sou pai de dois.\n");
        waitpid(pid1, NULL, 0);
        __pid_t pid2 = fork();
        if (pid2)
            printf("Acho que meus filhos terminaram suas execuções.\n");
        else {
            printf("Sou o filho mais novo.\n");
            printf("Sou o filho %d, e estou terminando agora.\n", getpid());
            exit(0);
        }
    } else {
        sleep(2);
        printf("Sou o filho mais velho e dormi um pouco.\n");
        printf("Sou o filho %d, e estou terminando agora.\n", getpid());
        exit(0);
    }

    return 0;
}