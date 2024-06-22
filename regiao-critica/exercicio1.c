/*
Escolha três dos exercícios anteriores e implemente usando as construções
pthread_mutex_lock, pthread_mutex_unlock e as variáveis condição
pthread_cond_wait e pthread_cond_signal
exercicio 0
*/

#include <pthread.h>
#include <stdio.h>

pthread_t tid1, tid2;
pthread_mutex_t lock;
pthread_cond_t cond;

int buffer;
int data_available = 0; // Indica se há um novo dado no buffer

void *produtor()
{
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&lock);
        while (data_available)
        {
            pthread_cond_wait(&cond, &lock);
        }

        buffer = i;
        data_available = 1;
        printf("\tValor produzido: %d\n", i);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);

        // Para permitir que o consumidor tenha tempo para consumir o item produzido antes que o próximo item seja produzido
        struct timespec ts = {0, 10000000L}; // 10ms
        nanosleep(&ts, NULL);
    }
    return NULL;
}
void *consumidor()
{
    int k;
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&lock);
        while (!data_available)
        {
            pthread_cond_wait(&cond, &lock);
        }
        k = buffer;
        data_available = 0;
        printf("Valor consumido: %d\n", k);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    // Inicializando o mutex e a variável de condição
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid1, NULL, produtor, NULL);
    pthread_create(&tid2, NULL, consumidor, NULL);

    // Espera pelas threads terminarem
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Destruindo o mutex e a variável de condição
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}