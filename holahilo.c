//Compilación: gcc -o holahilo holahilo.c -lpthread

#include <stdio.h>
#include <pthread.h>
#define NUM_THREAD 10000   // variable cte en todo el codigo

int saldo;
pthread_mutex_t saldoLock = PTHREAD_MUTEX_INITIALIZER;

void * suma100(void *arg) {
    pthread_mutex_lock(&saldoLock);
    int localsaldo = saldo;
    localsaldo += 100;
    saldo = localsaldo;
    pthread_mutex_unlock(&saldoLock);
    pthread_exit(NULL);
}

void * suma100RC(void *arg) {
    // CONDICION DE CARRERA (RACE CONDITION): el resultado final depende del
    // orden en que se ejecuten los hilos.
    // REGION CRITICA: codigo que debe ejecutarse secuencialmente.
    // En este caso puede ser que dos hilos copien 'saldo' al mismo tiempo y
    // por lo tanto entre las dos incrementen 100 en lugar de 200.
    int localsaldo = saldo;
    localsaldo += 100;
    saldo = localsaldo;
    pthread_exit(NULL);
}

void * printHola(void *arg) {
    printf("Hola desde el hilo\n");
    pthread_exit(NULL);
    // notifica fin de ejecucion y retorna NULL
}

int main() {
    pthread_t threads[NUM_THREAD];
    saldo = 0;
    for (int i=0; i<NUM_THREAD; i++) {
        pthread_create(&threads[i], NULL, suma100, NULL);
        // ARGUMENTOS:
        // - variable con localilzacion del hilo
        // - objeto con prioridad o propiedades del hilo
        // - funcion a correr en hilo
        // - argumentos a pasar a funcion

    }
    for (int i=0; i<NUM_THREAD; i++) {
        pthread_join(threads[i], NULL);
        // ARGUMENTOS:
        // - espera a que el hilo de argumento haya concluido
        // - direccion de variable donde guarda valor que retorna
    }
    printf("Saldo final: %d\n", saldo);
    pthread_exit(NULL);
    // espera hasta que todos los hilos hayan concluido y termina el programa
}