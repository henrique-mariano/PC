#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define COMENDO 0

#define PENSANDO 1

#define COMFOME 2

#define NUMFILOSOFOS 5

int estado[NUMFILOSOFOS] = {PENSANDO, PENSANDO, PENSANDO, PENSANDO, PENSANDO};

pthread_mutex_t verifica;

pthread_mutex_t garfos[5];


void *filosofo(void* args) {

  int id = *(int *) args;

  int direita = (id + 1) % NUMFILOSOFOS;

  int esquerda = id > 0 ? id - 1 : id + 4;

  while(true){

    // Pensa

    pthread_mutex_lock(&verifica);

    estado[id] = PENSANDO;

    printf("Filosofo %d está pensando\n", id);

    pthread_mutex_unlock(&verifica);

    // sleep(1);

    // Com fome

    pthread_mutex_lock(&verifica);

    estado[id] = COMFOME;

    printf("Filosofo %d está com fome\n", id);

    pthread_mutex_unlock(&verifica);
    pthread_mutex_lock(&verifica);

    if (estado[direita] != COMENDO && estado[esquerda] != COMENDO){

      pthread_mutex_unlock(&verifica);

      // Come

      pthread_mutex_lock(&verifica);
      pthread_mutex_lock(&garfos[direita]);
      pthread_mutex_lock(&garfos[id]);

      estado[id] = COMENDO;

      printf("Filosofo %d está comendo\n", id);

      pthread_mutex_unlock(&verifica);

      // sleep(2);

      pthread_mutex_unlock(&garfos[id]);
      pthread_mutex_unlock(&garfos[direita]);



    } else {
      pthread_mutex_unlock(&verifica);

      while (true){

        // pegar o garfo esquerdo

        pthread_mutex_lock(&garfos[id]);

        // tentar pegar o direito

        if (pthread_mutex_trylock(&garfos[direita]) == 0){

          // muda o estado e "come"

          pthread_mutex_lock(&verifica);

          estado[id] = COMENDO;

          printf("Filosofo %d está comendo\n", id);

          pthread_mutex_unlock(&verifica);

          // sleep(2);

          // libera os garfos

          pthread_mutex_unlock(&garfos[id]);
          pthread_mutex_unlock(&garfos[direita]);

          // vai pensar
          break;

        }
        // libera o garfo esquerdo e tenta de novo

        pthread_mutex_unlock(&garfos[id]);
      }

    }

  }

}

int main() {

  pthread_t filosofos[NUMFILOSOFOS];

  int *id = NULL;

  for (int i = 0; i < NUMFILOSOFOS; i++){

    id = (int *) calloc(1, sizeof(int));

    *id = i;

    pthread_create(&filosofos[(*id)], NULL, filosofo, (void*) id);
  }

  for (int i = 0; i < NUMFILOSOFOS; i++)
    pthread_join(filosofos[i], NULL);

  return 0;

}

