/*
Objetivo: Sincronizar múltiplas threads em um ponto específico.
Descrição: Crie um programa com três threads que devem esperar umas pelas outras em um ponto de barreira antes de continuar a execução. Cada thread deve imprimir uma mensagem antes e depois da barreira.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais para mutex e condição
pthread_mutex_t lock;       // Mutex para proteger a seção crítica
pthread_cond_t cond;        // Variável de condição para sincronização
pthread_t tid1, tid2, tid3; // Identificadores das threads
int count = 0;              // Contador para rastrear o número de threads que chegaram à barreira

// Função de barreira para sincronização das threads
void barreira()
{
    pthread_mutex_lock(&lock); // Bloqueia o mutex

    count++;       // Incrementa o contador ao chegar na barreira
    if (count < 3) // Se menos de 3 threads chegaram na barreira
    {
        pthread_cond_wait(&cond, &lock); // Espera na variável de condição
    }
    else // Se todas as 3 threads chegaram na barreira
    {
        count = 0;                     // Reseta o contador
        pthread_cond_broadcast(&cond); // Acorda todas as threads esperando na barreira
    }

    pthread_mutex_unlock(&lock); // Desbloqueia o mutex
}

// Função que será executada pelas threads
void *thread_function(void *arg)
{
    int thread_id = *(int *)arg;                         // Obtém o ID da thread a partir dos argumentos
    printf("Thread %d chegou na barreira\n", thread_id); // Mensagem antes da barreira

    barreira(); // Chama a função de barreira para sincronização

    printf("Thread %d passou a barreira\n", thread_id); // Mensagem depois da barreira

    return NULL; // Termina a execução da thread
}

int main()
{
    int thread_ids[3] = {1, 2, 3};   // IDs das threads
    pthread_mutex_init(&lock, NULL); // Inicializa o mutex
    pthread_cond_init(&cond, NULL);  // Inicializa a variável de condição

    // Cria as três threads
    pthread_create(&tid1, NULL, thread_function, &thread_ids[0]);
    pthread_create(&tid2, NULL, thread_function, &thread_ids[1]);
    pthread_create(&tid3, NULL, thread_function, &thread_ids[2]);

    // Aguarda a conclusão das threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Destroi o mutex e a variável de condição
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0; // Termina a execução do programa
}
