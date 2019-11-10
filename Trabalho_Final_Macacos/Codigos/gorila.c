// autores: Henrique Mendes de Freitas Mariano e Leonardo Rodrigues de Souza
// arquivo: gorila.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

typedef enum {
    LEFT, RIGHT
} side;

pthread_mutex_t leftMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rightMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t entrada = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t turno = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gorila = PTHREAD_MUTEX_INITIALIZER;

typedef struct t_monkey {
    side side;
    pthread_t thread;
} monkey;

monkey macacos[1001], gorilas[1001];

int countLeftSide = 0, countRightSide = 0, totalLeftSide = 0, totalRightSide = 0;
int gorilaOcupado;
int gorila_passando = 0;

void *runGorila(void* id) {
    int i = *((int*) id);
    while(1){
        monkey g = gorilas[i];
        pthread_mutex_t* sideMutex = ((g.side == LEFT)? &leftMutex : &rightMutex);
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(sideMutex);
        gorilaOcupado = 1;
        if(g.side == LEFT) totalLeftSide--, totalRightSide++, countLeftSide++;
        else totalLeftSide++,totalRightSide--, countRightSide++;

        if ((g.side == LEFT && countLeftSide == 1) || (g.side == RIGHT && countRightSide == 1)) pthread_mutex_lock(&entrada);

        pthread_mutex_unlock(sideMutex);
        pthread_mutex_unlock(&turno);
        pthread_mutex_lock(&print);
        printf ("[%d/%d] ", totalLeftSide, totalRightSide);
        if(g.side == LEFT) printf(RED "Gorila %d passando da esquerda para direita...\n" RESET, i); 
        else printf(RED "Gorila %d passando da direita para esquerda....\n" RESET, i);
        sleep(3);
        printf ("[%d/%d] ", totalLeftSide, totalRightSide);
        if(g.side == LEFT) printf(RED "Gorila %d passou da esquerda para direita!\n" RESET, i); 
        else printf(RED "Gorila %d passando da passou para esquerda!\n" RESET, i);
        pthread_mutex_unlock(&print);
        gorilas[i].side = (g.side == LEFT)? RIGHT : LEFT;
        sleep(1);
        pthread_mutex_lock(sideMutex);
        if(g.side == LEFT) countLeftSide--;
        else countRightSide--;
        if ((g.side == LEFT && countLeftSide == 0) || (g.side == RIGHT && countRightSide == 0)) pthread_mutex_unlock(&entrada);
        gorilaOcupado = 0;
        pthread_mutex_unlock(sideMutex);
        sleep(5);
    }
}

void *runMonkey(void* id) {
    int i = *((int*) id);
    while(1){
        monkey m = macacos[i];
        pthread_mutex_t* sideMutex = ((m.side == LEFT)? &leftMutex : &rightMutex);
        do { } while (gorilaOcupado == 1);
        pthread_mutex_lock(&turno);
        pthread_mutex_lock(sideMutex);
        if(m.side == LEFT) totalLeftSide--, totalRightSide++, countLeftSide++;
        else totalLeftSide++,totalRightSide--, countRightSide++;

        if ((m.side == LEFT && countLeftSide == 1) || (m.side == RIGHT && countRightSide == 1)) pthread_mutex_lock(&entrada);
        pthread_mutex_unlock(sideMutex);
        pthread_mutex_unlock(&turno);
        pthread_mutex_lock(&print);
        printf ("[%d/%d] ", totalLeftSide, totalRightSide);
        if(m.side == LEFT) printf("Macaco %d passando da esquerda para direita\n", i); 
        else printf("Macaco %d passando da direita para esquerda\n", i);
        pthread_mutex_unlock(&print);
        macacos[i].side = (m.side == LEFT)? RIGHT : LEFT;
        sleep(1);
        pthread_mutex_lock(sideMutex);
        if(m.side == LEFT) countLeftSide--;
        else countRightSide--;
        if ((m.side == LEFT && countLeftSide == 0) || (m.side == RIGHT && countRightSide == 0)) pthread_mutex_unlock(&entrada);
        pthread_mutex_unlock(sideMutex);
    }
}

int main(void){
    int n = 0;
    int n_gorilas = 0;
    int *id = NULL;
    int *id_gorila = NULL;
    gorilaOcupado = 0;
    printf("Número de macacos em cada lado (1 a 500): ");
    do {
        scanf("%d", &n);
    } while (n <= 0 || n >= 1000);

    printf("Número de gorilas em cada lado (1 a 500): ");
    do {
        scanf("%d", &n_gorilas);
    } while (n_gorilas <= 0 || n_gorilas >= 1000);

    pthread_mutex_init(&leftMutex, NULL);
    pthread_mutex_init(&rightMutex, NULL);
    pthread_mutex_init(&entrada, NULL);
    pthread_mutex_init(&turno, NULL);
    pthread_mutex_init(&print, NULL);
    totalLeftSide = n + n_gorilas, totalRightSide = n + n_gorilas;

    for(int i = 0; i < 2 * n; i++){
        id = (int *) calloc(1, sizeof(int));
        *id = i;
        macacos[(*id)].side = (i % 2) == 0? LEFT : RIGHT;
        pthread_create(&macacos[(*id)].thread, NULL, runMonkey, (void *) id);
    }

    for (int i = 0; i < 2 * n_gorilas; i++){
        id_gorila = (int *) calloc(1, sizeof(int));
        *id_gorila = i;
        gorilas[(*id_gorila)].side = (i % 2) == 0? LEFT : RIGHT;
        pthread_create(&gorilas[(*id_gorila)].thread, NULL, runGorila, (void *) id_gorila);
    }

    for(int i = 0; i < 2 * n; i++) pthread_join(macacos[i].thread, NULL);
    for(int i = 0; i < 2 * n_gorilas; i++) pthread_join(gorilas[i].thread, NULL);
    
    return 0;
}