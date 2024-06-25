/*
Escrever um programa formado por um processo (thread) produtor e por um processo (thread) consumidor, que compartilham um buffer de 132 posições. O processo consumidor somente pode consumir (fazer printf) quando o buffer estiver cheio
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2;

sem_t s0, s1;

int buffer[132];

void *produtor()
{
    sem_wait(&s0);
    for (int i = 0; i < 132; i++)
    {
        buffer[i] = i;
        // printf("\tValor produzido: %d\n", i);
    }
    sem_post(&s1);
}
void *consumidor()
{
    int k;
    sem_wait(&s1);
    for (int i = 0; i < 132; i++)
    {
        k = buffer[i];
        printf("Valor consumido: %d\n", k);
    }
    sem_post(&s0);
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