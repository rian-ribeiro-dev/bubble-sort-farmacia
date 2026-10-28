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

/* Descarta o restante da linha digitada (ate o Enter) */
void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Le um numero inteiro entre min e max, repetindo ate ser valido */
int lerInteiro(const char *mensagem, int min, int max) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1 && valor >= min && valor <= max) {
            limparEntrada();
            return valor;
        }
        limparEntrada();
        printf("Valor invalido! Digite um numero entre %d e %d.\n", min, max);
    }
}

/* Permite ao usuario digitar o nome e os dias de cada medicamento */
void cadastrarMedicamentos(char nomes[][TAM_NOME], int dias[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\nMedicamento %d de %d\n", i + 1, n);
        printf("Nome: ");
        if (fgets(nomes[i], TAM_NOME, stdin) == NULL) {
            nomes[i][0] = '\0';
        }
        nomes[i][strcspn(nomes[i], "\n")] = '\0'; /* remove o Enter */
        dias[i] = lerInteiro("Dias ate o vencimento: ", 0, 9999);
    }
}

/* Mostra a lista de medicamentos com os dias para vencer */
void exibirEstoque(char nomes[][TAM_NOME], int dias[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%2d) %-22s %4d dias\n", i + 1, nomes[i], dias[i]);
    }
}

/*
 * Bubble Sort: compara elementos vizinhos e troca quando estao fora de ordem.
 * crescente = 1 -> menos dias primeiro (prioridade de venda)
 * crescente = 0 -> mais dias primeiro
 */
void bubbleSort(char nomes[][TAM_NOME], int dias[], int n, int crescente) {
    int i, j, auxDias, foraDeOrdem;
    char auxNome[TAM_NOME];

    /* Laco externo: cada passada leva um elemento para sua posicao final */
    for (i = 0; i < n - 1; i++) {
        /* Laco interno: percorre os pares vizinhos ainda nao ordenados */
        for (j = 0; j < n - 1 - i; j++) {
            /* Comparacao entre elementos adjacentes conforme o criterio */
            if (crescente) {
                foraDeOrdem = dias[j] > dias[j + 1];
            } else {
                foraDeOrdem = dias[j] < dias[j + 1];
            }

            if (foraDeOrdem) {
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
    int opcaoDados, crescente;

    printf("==============================================\n");
    printf("   CONTROLE DE VALIDADE - FARMACIA\n");
    printf("==============================================\n");
    printf("1 - Usar estoque de exemplo (%d medicamentos)\n", TAM);
    printf("2 - Digitar os %d medicamentos\n", TAM);
    opcaoDados = lerInteiro("Escolha: ", 1, 2);
    if (opcaoDados == 2) {
        cadastrarMedicamentos(nomes, dias, TAM);
    }

    printf("\nCriterio de ordenacao:\n");
    printf("1 - Crescente  (vencem primeiro no topo)\n");
    printf("2 - Decrescente (validade mais longa no topo)\n");
    crescente = lerInteiro("Escolha: ", 1, 2) == 1;

    printf("\n=== ANTES DA ORDENACAO ===\n");
    exibirEstoque(nomes, dias, TAM);

    bubbleSort(nomes, dias, TAM, crescente);

    printf("\n=== DEPOIS DA ORDENACAO (%s) ===\n",
           crescente ? "crescente" : "decrescente");
    exibirEstoque(nomes, dias, TAM);

    return 0;
}
