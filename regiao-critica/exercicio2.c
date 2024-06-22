/*
Escrever um programa formado por três processos (threads), p0, p1, p2, que
executam um loop eterno no qual imprime a sua identificação, na seqüência
p1, p2, p0, p1, p2, p0,...
*/
#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2, tid0;
pthread_mutex_t lock;
pthread_cond_t cond;

int next_thread = 1; // Define qual thread deve executar

void *p0()
{
    pthread_mutex_lock(&lock);
    while (next_thread != 3)
    {
        pthread_cond_wait(&cond, &lock);
    }

    printf("\np0\n");
    next_thread = 1;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

void *p1()
{
    pthread_mutex_lock(&lock);
    while (next_thread != 1)
    {
        pthread_cond_wait(&cond, &lock);
    }

    printf("\np1\n");
    next_thread = 2;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

void *p2()
{
    pthread_mutex_lock(&lock);
    while (next_thread != 2)
    {
        pthread_cond_wait(&cond, &lock);
    }

    printf("\np2\n");

    next_thread = 3;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

int main(int argc, char const *argv[])
{
    // Inicializando o mutex e a variável de condição
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid0, NULL, p0, NULL);
    pthread_create(&tid1, NULL, p1, NULL);
    pthread_create(&tid2, NULL, p2, NULL);

    // Espera pelas threads terminarem
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Destruindo o mutex e a variável de condição
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
