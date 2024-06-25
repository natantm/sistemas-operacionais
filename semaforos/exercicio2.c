/*
Escrever um programa formado por três processos (threads), p0, p1, p2, que executam um loop eterno no qual imprime a sua identificação, na seqüência p1, p2, p0, p1, p2, p0,...
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2, tid3;

sem_t s0, s1, s2;

int buffer;

void *p0()
{
    sem_wait(&s2);
    printf("p0 = %d\n", pthread_self());
    sem_post(&s0);
}

void *p1()
{
    sem_wait(&s0);
    printf("p1 = %d\n", pthread_self());
    sem_post(&s1);
}

void *p2()
{
    sem_wait(&s1);
    printf("p2 = %d\n", pthread_self());
    sem_post(&s2);
}

int main(int argc, char const *argv[])
{
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&tid3, NULL, p0, NULL);
        pthread_create(&tid1, NULL, p1, NULL);
        pthread_create(&tid2, NULL, p2, NULL);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
}
