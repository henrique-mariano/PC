#include <pthread.h>

int var = 0;

void* contador ( void* arg ) {
    var++;
}
int main ( void ) {
    pthread_t t[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&t[i], NULL, contador, NULL);
    }

    var++; // A main também irá incrementar
    
    for (int i = 0; i < 10; i++) {
        pthread_join(t[i], NULL);
    }
    
    return 0;
}