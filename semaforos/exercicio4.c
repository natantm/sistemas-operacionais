/*
Escreva um programa formado por três threads, th0, th1 e th2 que executam
um loop infinito, e que utilizam semáforos para sincronização . A thread th0 faz
a leitura de um valor, realiza um cálculo parcial e deposita esse cálculo em um
buffer, de onde a thread th1 o retira, executa um outro cálculo e deposita o
resultado em um segundo buffer de onde a thread th2o retira e imprime.
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2, tid3;

sem_t s0, s1, s2;

int buffer1, buffer2;

void *p0()
{
    int val;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&s0);

        printf("Valor#:\t");
        scanf("%d", &val);
        buffer1 = val + 3;

        sem_post(&s1);
    }
}

void *p1()
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&s1);
        buffer2 = buffer1 + 5;
        sem_post(&s2);
    }
}

void *p2()
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&s2);
        printf("p2 = %d\n", buffer2);
        sem_post(&s0);
    }
}

int main(int argc, char const *argv[])
{
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    pthread_create(&tid3, NULL, p0, NULL);
    pthread_create(&tid1, NULL, p1, NULL);
    pthread_create(&tid2, NULL, p2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
}