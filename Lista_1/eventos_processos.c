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
    
    if(pid1)
        printf("Pai cria processo 1: %d\n", pid1);
    else{
        sleep(2);
        printf("Sou o filho mais velho e dormi um pouco.\n");
        printf("Sou o filho %d e meu pai %d, e estou terminando agora.\n", getpid(), getppid());
        exit(0);
    }
    // sleep(1);
    __pid_t pid2 = fork();
    if(pid2){
        printf("Pai cria processo 2: %d\n", pid2);
        waitpid(pid1, NULL, 0);
    } else {
        printf("Sou o filho mais novo.\n");
        printf("Sou o filho %d e meu pai %d, e estou terminando agora.\n", getpid(), getppid());
        exit(0);
    }
    
    if(pid1 && pid2){
        printf("Sou pai de dois.\n");
        waitpid(pid1, NULL, 0);
        printf("Acho que meus filhos terminaram suas execuções.\n");
    }
    // if(pid1){
    //     pid2 = fork();
    //     if(!pid2){
    //         waitpid(pid1, NULL, 0);
    //         printf("Sou o filho mais novo.\n");
    //         printf("Sou o filho %d, e estou terminando agora.\n", getpid());
    //         exit(0);
    //     }
    // }

    // if(pid1 && pid2){
    //     printf("Sou pai de dois.\n");
    //     waitpid(pid1, NULL, 0);
    //     printf("Acho que meus filhos terminaram suas execuções.\n");
    // } else if(!pid1) {
    //     sleep(2);
    //     printf("Sou o filho mais velho e dormi um pouco.\n");
    //     printf("Sou o filho %d, e estou terminando agora.\n", getpid());
    //     exit(0);
    // } else if(!pid2 && pid1) {
    //     // waitpid(pid1, NULL, 0);
    //     printf("Sou o filho mais novo.\n");
    //     printf("Sou o filho %d, e estou terminando agora.\n", getpid());
    //     exit(0);
    // } else {
    //     exit(0);
    // }

    // if(pid1 == 0){
    //     sleep(2);
    //     printf("Sou o filho mais velho e dormi um pouco.\n");
    //     printf("Sou o filho %d, e estou terminando agora.\n", getpid());
    //     exit(0);
    // }

    // if((pid2 == 0) && pid1){
    //     printf("Sou o filho mais novo.\n");
    //     printf("Sou o filho %d, e estou terminando agora.\n", getpid());
    //     exit(0);
    // }
    // wait(NULL);
    // wait(NULL);



    return 0;
}