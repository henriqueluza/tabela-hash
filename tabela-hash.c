#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // Tamanho da tabela

// Estrutura para armazenar os elementos da tabela hash
typedef struct {
    int key;
    int isOccupied; // 0: vazio, 1: ocupado
} HashEntry;

HashEntry hashTable[TABLE_SIZE];

// Inicializa a tabela hash
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].key = -1;
        hashTable[i].isOccupied = 0;
    }
}

// Função hash primária
int primaryHash(int key) {
    /* 
     * Usando um multiplicador primo (11) para gerar uma melhor distribuição
     * Isso evita que chaves com padrões similares (como 5, 15, 25, 35)
     * sejam mapeadas para o mesmo índice na tabela
     */
    return (key * 11) % TABLE_SIZE;
}

// Função hash secundária
int secondaryHash(int key) {
    return 1 + (key % (TABLE_SIZE - 1));
}

// Função para inserir um elemento na tabela
void insert(int key) {
    int hash1 = primaryHash(key);
    int hash2 = secondaryHash(key);
    int position = hash1;

    printf("Inserindo chave %d...\n", key);
    fflush(stdout);

    // Resolve colisões usando duplo hashing
    int i = 0;
    while (hashTable[position].isOccupied) {
        printf("Colisao na posicao %d!\n", position);
        fflush(stdout);
        i++;
        position = (hash1 + i * hash2) % TABLE_SIZE;
        printf("Novo hash calculado: %d\n", position);
        fflush(stdout);

        if (i >= TABLE_SIZE) {
            printf("Erro: Tabela cheia, nao foi possivel inserir a chave %d.\n", key);
            fflush(stdout);
            return;
        }
    }

    // Insere o elemento na tabela
    hashTable[position].key = key;
    hashTable[position].isOccupied = 1;
    printf("Chave %d inserida na posicao %d.\n\n", key, position);
    fflush(stdout);
}

// Função para procurar um elemento na tabela
void search(int key) {
    int hash1 = primaryHash(key);
    int hash2 = secondaryHash(key);
    int position = hash1;

    printf("Procurando chave %d...\n", key);
    fflush(stdout);

    // Resolve colisões durante a busca
    int i = 0;
    while (hashTable[position].isOccupied && hashTable[position].key != key) {
        printf("Colisao ao buscar na posicao %d!\n", position);
        fflush(stdout);
        i++;
        position = (hash1 + i * hash2) % TABLE_SIZE;

        if (i >= TABLE_SIZE) {
            printf("Chave %d nao encontrada.\n\n", key);
            fflush(stdout);
            return;
        }
    }

    if (hashTable[position].isOccupied && hashTable[position].key == key) {
        printf("Chave %d encontrada na posicao %d.\n\n", key, position);
        fflush(stdout);
    } else {
        printf("Chave %d nao encontrada.\n\n", key);
        fflush(stdout);
    }
}

// Funço principal
int main() {
    initializeTable();

    printf("=== Testando insercao e busca na tabela hash ===\n\n");
    fflush(stdout);
    
    // Inserindo elementos com diferentes valores
    insert(5);
    insert(16);
    insert(27);
    insert(38);
    insert(49);  // Nova chave para testar

    printf("=== Testando buscas ===\n\n");
    fflush(stdout);
    // Procurando elementos
    search(5);
    search(16);
    search(38);
    search(49);  // Busca da nova chave
    search(40);  // Não encontrado

    printf("=== Fim dos testes ===\n");
    fflush(stdout);
    return 0;
}
