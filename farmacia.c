/*
 * Projeto: Controle de Validade - Farmacia
 * Disciplina: Algoritmos e Pensamento Computacional - UDF
 * Profa. Karla R. Sartin
 *
 * Versao inicial: cadastro dos medicamentos e exibicao do estoque.
 */

#include <stdio.h>

#define TAM 12      /* quantidade de medicamentos (minimo exigido: 10) */
#define TAM_NOME 40 /* tamanho maximo do nome de cada medicamento */

int main(void) {
    /* Array com os nomes dos medicamentos em estoque */
    char nomes[TAM][TAM_NOME] = {
        "Dipirona 500mg",      "Amoxicilina 500mg",  "Paracetamol 750mg",
        "Ibuprofeno 400mg",    "Loratadina 10mg",    "Omeprazol 20mg",
        "Losartana 50mg",      "Insulina NPH",       "Vitamina C 1g",
        "Soro Fisiologico",    "Azitromicina 500mg", "Xarope Expectorante"
    };

    /* Array com os dias restantes ate o vencimento de cada medicamento.
       A posicao i deste array corresponde ao medicamento nomes[i]. */
    int dias[TAM] = {120, 15, 210, 45, 7, 300, 90, 3, 60, 180, 30, 21};

    int i;

    printf("=== ESTOQUE DA FARMACIA ===\n");
    for (i = 0; i < TAM; i++) {
        printf("%2d) %-22s %4d dias\n", i + 1, nomes[i], dias[i]);
    }

    return 0;
}
