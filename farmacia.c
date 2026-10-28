/*
 * Projeto: Controle de Validade - Farmacia
 * Disciplina: Algoritmos e Pensamento Computacional - UDF
 * Profa. Karla R. Sartin
 *
 * Ordena os medicamentos pelos dias restantes ate o vencimento
 * usando o algoritmo Bubble Sort.
 */

#include <stdio.h>
#include <string.h>

#define TAM 12      /* quantidade de medicamentos (minimo exigido: 10) */
#define TAM_NOME 40 /* tamanho maximo do nome de cada medicamento */

/* Mostra a lista de medicamentos com os dias para vencer */
void exibirEstoque(char nomes[][TAM_NOME], int dias[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%2d) %-22s %4d dias\n", i + 1, nomes[i], dias[i]);
    }
}

/*
 * Bubble Sort em ordem crescente (menos dias primeiro).
 * Compara elementos vizinhos e troca quando estao fora de ordem.
 */
void bubbleSort(char nomes[][TAM_NOME], int dias[], int n) {
    int i, j, auxDias;
    char auxNome[TAM_NOME];

    /* Laco externo: cada passada leva o maior valor para o final */
    for (i = 0; i < n - 1; i++) {
        /* Laco interno: percorre os pares vizinhos ainda nao ordenados */
        for (j = 0; j < n - 1 - i; j++) {
            /* Comparacao entre elementos adjacentes */
            if (dias[j] > dias[j + 1]) {
                /* Troca dos dias */
                auxDias = dias[j];
                dias[j] = dias[j + 1];
                dias[j + 1] = auxDias;

                /* Troca dos nomes, para manter cada nome com seus dias */
                strcpy(auxNome, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], auxNome);
            }
        }
    }
}

int main(void) {
    char nomes[TAM][TAM_NOME] = {
        "Dipirona 500mg",      "Amoxicilina 500mg",  "Paracetamol 750mg",
        "Ibuprofeno 400mg",    "Loratadina 10mg",    "Omeprazol 20mg",
        "Losartana 50mg",      "Insulina NPH",       "Vitamina C 1g",
        "Soro Fisiologico",    "Azitromicina 500mg", "Xarope Expectorante"
    };
    int dias[TAM] = {120, 15, 210, 45, 7, 300, 90, 3, 60, 180, 30, 21};

    printf("=== ANTES DA ORDENACAO ===\n");
    exibirEstoque(nomes, dias, TAM);

    bubbleSort(nomes, dias, TAM);

    printf("\n=== DEPOIS DA ORDENACAO (crescente) ===\n");
    exibirEstoque(nomes, dias, TAM);

    return 0;
}
