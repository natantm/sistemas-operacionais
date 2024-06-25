/*
Escreva um programa concorrente formado por dois processos, um produtor e um consumidor que compartilham um buffer de um elemento, e que sincronizam suas ações com o uso de semáforos.
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2;

sem_t s0, s1;

int buffer;

void *produtor()
{
    for (int i = 0; i < 100; i++)
    {
        sem_wait(&s0);
        buffer = i;
        sem_post(&s1);
        printf("\tValor produzido: %d\n", i);
    }
}
void *consumidor()
{
    int k;
    for (int i = 0; i < 100; i++)
    {
        sem_wait(&s1);
        k = buffer;
        sem_post(&s0);
        printf("Valor consumido: %d\n", k);
    }
}

int main(int argc, char const *argv[])
{
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);

    pthread_create(&tid1, NULL, produtor, NULL);
    pthread_create(&tid2, NULL, consumidor, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
