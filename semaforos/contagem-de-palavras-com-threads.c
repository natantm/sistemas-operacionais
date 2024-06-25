#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo o tamanho máximo do buffer (modifique conforme necessário)
#define MAX_BUFFER_SIZE 1024

// Estrutura para passar argumentos para as threads
typedef struct
{
    char *text;
    int start;
    int end;
    int wordCount;
} ThreadArgs;

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

    fileContent[bytesRead] = '\0'; // Para garantir que a string é terminada com NULL
    fclose(file);
}

// Função para contar palavras em uma parte do texto
void *countWords(void *args)
{
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    char *text = threadArgs->text;
    int start = threadArgs->start;
    int end = threadArgs->end;
    int inWord = 0;
    threadArgs->wordCount = 0;

    for (int i = start; i < end; i++)
    {
        if (isspace(text[i]))
        {
            if (inWord)
            {
                inWord = 0;
                threadArgs->wordCount++;
            }
        }
        else
        {
            inWord = 1;
        }
    }
    if (inWord)
    {
        threadArgs->wordCount++;
    }

    return NULL;
}

int main()
{
    readFile("arquivo.txt");

    int numThreads = 4;
    pthread_t threads[numThreads];
    ThreadArgs threadArgs[numThreads];

    int len = strlen(fileContent);
    int partSize = len / numThreads;

    // Criar e iniciar threads
    for (int i = 0; i < numThreads; i++)
    {
        threadArgs[i].text = fileContent;
        threadArgs[i].start = i * partSize;
        threadArgs[i].end = (i == numThreads - 1) ? len : (i + 1) * partSize;
        threadArgs[i].wordCount = 0;
        pthread_create(&threads[i], NULL, countWords, &threadArgs[i]);
    }

    // Aguardar o término das threads
    int totalWords = 0;
    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
        totalWords += threadArgs[i].wordCount;
    }

    printf("Total de palavras: %d\n", totalWords);

    return 0;
}
