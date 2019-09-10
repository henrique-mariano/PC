// autor: Henrique Mendes de Freitas Mariano
// arquivo: first_getppid.c
// atividade: 3.1.3
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    printf("%d\n", getppid());
    return 0;
}