/*
Objetivo: Dividir o trabalho entre múltiplas threads para processar dados.
Descrição: Crie um programa que conte o número de palavras em um grande
texto. Divida o texto em partes e crie uma thread para contar as palavras em cada parte. Combine os resultados das threads para obter a contagem total de palavras.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Definindo o tamanho máximo do buffer (modifique conforme necessário)
#define MAX_BUFFER_SIZE 1024

// Variável global para armazenar o conteúdo do arquivo
char fileContent[MAX_BUFFER_SIZE];

// Função para ler o conteúdo de um arquivo e armazená-lo na variável global
void readFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(fileContent, sizeof(char), MAX_BUFFER_SIZE - 1, file);
    if (ferror(file))
    {
        perror("Erro ao ler o arquivo");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fileContent[bytesRead] = '\0'; // Certifique-se de que a string é terminada com NULL
    fclose(file);
}

pthread_t tid1, tid2;

void ler_

    int
    main()
{
    readFile("arquivo.txt");

    pthread_create(&tid1, NULL, produtor, NULL);
    pthread_create(&tid2, NULL, consumidor, NULL);

    return 0;
}
