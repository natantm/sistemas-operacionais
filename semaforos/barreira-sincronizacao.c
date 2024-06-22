/*
Objetivo: Sincronizar múltiplas threads em um ponto específico. 
Descrição: Crie um programa com três threads que devem esperar umas pelas 
outras em um ponto de barreira antes de continuar a execução. Cada thread 
deve imprimir uma mensagem antes e depois da barreira. 
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;
pthread_cond_t cond;
pthread_t tid1,tid2,tid3;
int count = 0;

void barreira() {
    pthread_mutex_lock(&lock);

    count++;
    if (count < 3) {
        pthread_cond_wait(&cond, &lock);
    } else {
        count = 0; 
        pthread_cond_broadcast(&cond);
    }

    pthread_mutex_unlock(&lock);
}

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d chegou na barreira\n", thread_id);

    barreira();

    printf("Thread %d passou a barreira\n", thread_id);

    return NULL;
}

int main() {
    int thread_ids[3] = {1, 2, 3};
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid1, NULL, thread_function, &thread_ids[0]);
    pthread_create(&tid2, NULL, thread_function, &thread_ids[1]);
    pthread_create(&tid3, NULL, thread_function, &thread_ids[2]);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
