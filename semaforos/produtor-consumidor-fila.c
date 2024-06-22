/*
Objetivo: Implementar o padrão produtor-consumidor. 
Descrição: Crie um programa com duas threads: uma thread produtora que 
adiciona itens a uma fila e uma thread consumidora que remove itens da fila. A 
fila deve ter uma capacidade limitada e a sincronização deve ser usada para 
garantir que a thread consumidora não tente remover itens de uma fila vazia e 
que a thread produtora não tente adicionar itens a uma fila cheia
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int indexFila = 0;

pthread_t tid1,tid2;
sem_t s0, s1;

struct Node {
    int data;
    struct Node* next;
};

struct Fila {
    struct Node* inicio;
    struct Node* fin;
};


struct Node* createNode(int data);

struct Fila* createFila();

void addFila(int data);
int removeFila();

struct Fila* fila;

void * produtor(){
    int i ;
    for(i=0; i<100; i++)
    {   
        sem_wait(&s0) ;
        addFila(i);
        sem_post(&s1) ;
    }
}

void * consumidor(){
    int i;
    for(i=0; i<100; i++)
    {
        sem_wait(&s1);
        printf("\nValor consumido: %d\n", removeFila());
        sem_post(&s0);
    }
}


///////--------------------------------------------------------------------------------
int main(){
    fila = createFila();
    sem_init(&s0, 0, 1) ;
    sem_init(&s1, 0, 0) ;

    pthread_create(&tid1, NULL, produtor, NULL);
    pthread_create(&tid2, NULL, consumidor, NULL);

    pthread_join(tid1,NULL);
    pthread_join (tid2,NULL);
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Fila* createFila() {
    struct Fila* fila = (struct Fila*)malloc(sizeof(struct Fila));
    fila->inicio = fila->fin = NULL;
    return fila;
}


void addFila(int data) {
    printf("\n\tValor adicionado: %d", data);
    struct Node* newNode = createNode(data);

    if (fila->fin == NULL) {
        fila->inicio = fila->fin = newNode;
        return;
    }

    // Adicionar o novo nó no final da fila e atualizar o fin
    fila->fin->next = newNode;
    fila->fin = newNode;
}

int removeFila() {
    if (fila->inicio == NULL) {
        printf("Fila vazia\n");
        return -1;
    }

    struct Node* temp = fila->inicio;
    fila->inicio = fila->inicio->next;

    // Se o inicio se tornar NULL, então a fila está vazia
    if (fila->inicio == NULL) {
        fila->fin = NULL;
    }

    int data = temp->data;
    free(temp);
    return data;
}