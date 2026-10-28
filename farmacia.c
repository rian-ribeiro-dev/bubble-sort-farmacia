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
#define LIMITE_ALERTA 30 /* ate quantos dias o medicamento e considerado critico */

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

/* Mostra a lista de medicamentos com os dias para vencer e a situacao */
void exibirEstoque(char nomes[][TAM_NOME], int dias[], int n) {
    int i;
    printf("No  Medicamento             Dias  Situacao\n");
    printf("--  ----------------------  ----  -------------------\n");
    for (i = 0; i < n; i++) {
        printf("%2d  %-22s  %4d  ", i + 1, nomes[i], dias[i]);
        /* Condicional que classifica a urgencia de cada item */
        if (dias[i] <= 7) {
            printf("URGENTE - prioridade maxima\n");
        } else if (dias[i] <= LIMITE_ALERTA) {
            printf("ATENCAO - vender primeiro\n");
        } else {
            printf("OK\n");
        }
    }
}

/*
 * Bubble Sort: compara elementos vizinhos e troca quando estao fora de ordem.
 * crescente = 1 -> menos dias primeiro (prioridade de venda)
 * crescente = 0 -> mais dias primeiro
 * Os ponteiros comparacoes e trocas recebem as contagens de operacoes.
 */
void bubbleSort(char nomes[][TAM_NOME], int dias[], int n, int crescente,
                int *comparacoes, int *trocas) {
    int i, j, auxDias, foraDeOrdem, houveTroca;
    char auxNome[TAM_NOME];

    *comparacoes = 0;
    *trocas = 0;

    /* Laco externo: cada passada leva um elemento para sua posicao final */
    for (i = 0; i < n - 1; i++) {
        houveTroca = 0;

        /* Laco interno: percorre os pares vizinhos ainda nao ordenados.
           A cada passada, os ultimos i elementos ja estao no lugar certo. */
        for (j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;

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

                (*trocas)++;
                houveTroca = 1;
            }
        }

        /* Otimizacao: se nenhuma troca ocorreu, o array ja esta ordenado */
        if (!houveTroca) {
            break;
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
    int opcaoDados, crescente, comparacoes, trocas, i, criticos = 0;

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

    bubbleSort(nomes, dias, TAM, crescente, &comparacoes, &trocas);

    printf("\n=== DEPOIS DA ORDENACAO (%s) ===\n",
           crescente ? "crescente" : "decrescente");
    exibirEstoque(nomes, dias, TAM);

    /* Conta quantos medicamentos estao proximos do vencimento */
    for (i = 0; i < TAM; i++) {
        if (dias[i] <= LIMITE_ALERTA) {
            criticos++;
        }
    }

    printf("\n=== RESUMO ===\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Trocas realizadas:      %d\n", trocas);
    printf("Medicamentos vencendo em ate %d dias: %d\n", LIMITE_ALERTA, criticos);
    if (crescente) {
        printf("Menor prazo: %s (%d dias)\n", nomes[0], dias[0]);
        printf("Maior prazo: %s (%d dias)\n", nomes[TAM - 1], dias[TAM - 1]);
    } else {
        printf("Maior prazo: %s (%d dias)\n", nomes[0], dias[0]);
        printf("Menor prazo: %s (%d dias)\n", nomes[TAM - 1], dias[TAM - 1]);
    }

    return 0;
}
