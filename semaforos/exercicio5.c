/*
Escreva um programa formado por quatro threads: monitor, relator1 relator2 e impressor. A thread monitor faz a leitura de 100 valores inteiros. Os valores menores que 500 devem ser armazenados no vetor vet0 e os maiores que 500 no vetor vet1. O processo relator0 deve somar os elementos do vetor vet0 e o processo relator1 deve somar os elementos do vetor vet1. O processo impressor deve imprimir cada soma (somente quando o vetor estiver cheio), juntamente com a identificação do processo relator que a efetuou. Considere que as somas possuem um valor superior a 0.
*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2, tid3, tid4;

sem_t s0, s1, s2, s3;

int vet0[5], vet1[5], index0 = 0, index1 = 0, som0, som1, pid0, pid1;
int relator = 3;

void *monitor()
{
    int val = 0;
    relator = 3;
    sem_wait(&s0);
    while (index0 < 5 && index1 < 5)
    {
        printf("\n\nValor:");
        scanf("%d", &val);

        if (val < 500)
        {
            vet0[index0] = val;
            index0++;
        }
        if (val >= 500)
        {
            vet1[index1] = val;
            index1++;
        }
    }
    sem_post(&s1);
    sem_post(&s2);
}

void *relator0()
{
    sem_wait(&s1);
    relator = 0;
    // printf("\nrel0\n");
    for (int i = 0; i < index0; i++)
    {
        som0 += vet0[i];
    }
    pid0 = pthread_self();
    sem_post(&s3);
}

void *relator1()
{
    sem_wait(&s2);
    relator = 1;
    // printf("\nrel1\n");
    for (int i = 0; i < index1; i++)
    {
        som1 += vet1[i];
    }
    pid1 = pthread_self();
    sem_post(&s3);
}

void *impressor()
{
    sem_wait(&s3);
    if (relator == 0)
        printf("\nvetor 0 (%d): %d", pid0, som0);
    else if (relator == 1)
        printf("\nvetor 1 (%d): %d", pid1, som1);
    else
        printf("\nNão houve soma!\n");
    sem_post(&s0);
}

int main(int argc, char const *argv[])
{
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);

    pthread_create(&tid1, NULL, monitor, NULL);
    pthread_create(&tid2, NULL, relator0, NULL);
    pthread_create(&tid3, NULL, relator1, NULL);
    pthread_create(&tid3, NULL, impressor, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
}