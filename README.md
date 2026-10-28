# 💊 Controle de Validade de Medicamentos — Bubble Sort em C

**Disciplina:** Algoritmos e Pensamento Computacional
**Instituição:** UDF — Centro Universitário do Distrito Federal
**Professora:** Profa. Karla R. Sartin
**Atividade:** Aplicação do Algoritmo Bubble Sort

## 👥 Integrantes

| Nome | Matrícula | GitHub |
|------|-----------|--------|
| Rian Do Nascimento Ribeiro | 47582006 | [@rian-ribeiro-dev](https://github.com/rian-ribeiro-dev) |
| Jean Emanuel Alves de Morais | 47385804 | [@Jeanemanuel](https://github.com/Jeanemanuel) |
| Emilly Lorrany Alves dos Santos | 46894993 | [@emillyy-cell](https://github.com/emillyy-cell) |
| Alair Eloi de Araujo Neto | _a preencher_ | [@otencoding](https://github.com/otencoding) |

---

## 📌 Problema do cotidiano

Uma farmácia tem dezenas de medicamentos no estoque, e cada lote tem uma data de validade diferente. Quando a equipe não sabe quais produtos vencem primeiro, acontece o seguinte:

- medicamentos vencem na prateleira e viram **prejuízo**, porque precisam ser descartados;
- existe o **risco à saúde** de um produto vencido chegar ao cliente;
- a farmácia descumpre o princípio **PVPS** (*Primeiro que Vence, Primeiro que Sai*), muito usado na gestão de estoques de produtos perecíveis.

**Por que ordenar?** Com a lista ordenada pelos **dias que faltam para o vencimento**, o farmacêutico vê na hora quais itens precisam sair primeiro, ganhar promoção ou ser conferidos. Também fica fácil descobrir o menor e o maior prazo do estoque.

## 🎯 Objetivo da aplicação

Desenvolver em C um programa que:

1. guarde em **arrays** o nome de **12 medicamentos** e os dias que faltam para cada um vencer;
2. mostre o estoque **antes** da ordenação;
3. ordene os dados com o **Bubble Sort**, no critério escolhido pelo usuário (**crescente** ou **decrescente**);
4. mostre o estoque **depois** da ordenação, com a situação de cada item (OK / ATENCAO / URGENTE);
5. apresente um resumo com o número de comparações e trocas, a quantidade de itens críticos e os prazos extremos.

## 🫧 Como o Bubble Sort funciona

O Bubble Sort (ordenação por bolha) **compara elementos vizinhos** do array e **troca os dois de lugar** quando estão na ordem errada. A cada passada completa, o maior valor (no critério crescente) "sobe" até o fim do array, como uma bolha subindo na água.

```
Passada 1: [120, 15, 210, 45, ...]
            120 > 15?  sim -> troca -> [15, 120, 210, 45, ...]
            120 > 210? não -> mantém
            210 > 45?  sim -> troca -> [15, 120, 45, 210, ...]
            ... ao fim da passada, o maior valor (300) está na última posição
Passada 2: repete o processo, ignorando a última posição (já ordenada)
...
```

No código ([`farmacia.c`](farmacia.c), função `bubbleSort`):

- **Laço externo** (`for i`): controla as passadas. Depois de cada uma, um elemento fica na posição definitiva.
- **Laço interno** (`for j`): percorre os pares vizinhos `dias[j]` e `dias[j + 1]`, até `n - 1 - i`, porque o final do array já está ordenado.
- **Comparação** (`if`): no critério crescente, verifica `dias[j] > dias[j + 1]`; no decrescente, `dias[j] < dias[j + 1]`.
- **Troca**: usa uma variável auxiliar. Os **dias** e os **nomes** são trocados juntos (com `strcpy`), para que cada medicamento continue ligado ao seu prazo.
- **Otimização**: a variável `houveTroca` registra se aconteceu alguma troca na passada. Se não aconteceu nenhuma, o array já está ordenado e o laço termina com `break`.

**Complexidade:** O(n²) no pior caso e O(n) no melhor caso (array já ordenado, graças à otimização). Para listas pequenas, como a deste projeto, o desempenho é adequado.

> O programa **não** usa funções prontas de ordenação, como `qsort()`. Toda a ordenação é feita pelo Bubble Sort implementado no código.

## ▶️ Como compilar e executar

Pré-requisito: um compilador C (GCC, MinGW no Windows, Code::Blocks ou OnlineGDB).

```bash
gcc -Wall -o farmacia farmacia.c
./farmacia
```

No Windows (prompt de comando):

```bash
gcc -Wall -o farmacia.exe farmacia.c
farmacia.exe
```

**No OnlineGDB:** cole o conteúdo de `farmacia.c`, selecione a linguagem **C** e clique em **Run**.

### Uso do programa

1. Escolha **1** para usar o estoque de exemplo ou **2** para digitar os 12 medicamentos (nome e dias até o vencimento).
2. Escolha o critério: **1 – Crescente** (os que vencem primeiro aparecem no topo) ou **2 – Decrescente**.
3. Veja a lista antes e depois da ordenação e o resumo final.

As entradas são validadas: se o usuário digitar uma opção inválida, o programa pede o valor de novo.

## 💻 Exemplo de entrada e saída

**Entrada:** `1` (estoque de exemplo) e `1` (crescente)

```text
==============================================
   CONTROLE DE VALIDADE - FARMACIA
==============================================
1 - Usar estoque de exemplo (12 medicamentos)
2 - Digitar os 12 medicamentos
Escolha: 
Criterio de ordenacao:
1 - Crescente  (vencem primeiro no topo)
2 - Decrescente (validade mais longa no topo)
Escolha: 
=== ANTES DA ORDENACAO ===
No  Medicamento             Dias  Situacao
--  ----------------------  ----  -------------------
 1  Dipirona 500mg           120  OK
 2  Amoxicilina 500mg         15  ATENCAO - vender primeiro
 3  Paracetamol 750mg        210  OK
 4  Ibuprofeno 400mg          45  OK
 5  Loratadina 10mg            7  URGENTE - prioridade maxima
 6  Omeprazol 20mg           300  OK
 7  Losartana 50mg            90  OK
 8  Insulina NPH               3  URGENTE - prioridade maxima
 9  Vitamina C 1g             60  OK
10  Soro Fisiologico         180  OK
11  Azitromicina 500mg        30  ATENCAO - vender primeiro
12  Xarope Expectorante       21  ATENCAO - vender primeiro

=== DEPOIS DA ORDENACAO (crescente) ===
No  Medicamento             Dias  Situacao
--  ----------------------  ----  -------------------
 1  Insulina NPH               3  URGENTE - prioridade maxima
 2  Loratadina 10mg            7  URGENTE - prioridade maxima
 3  Amoxicilina 500mg         15  ATENCAO - vender primeiro
 4  Xarope Expectorante       21  ATENCAO - vender primeiro
 5  Azitromicina 500mg        30  ATENCAO - vender primeiro
 6  Ibuprofeno 400mg          45  OK
 7  Vitamina C 1g             60  OK
 8  Losartana 50mg            90  OK
 9  Dipirona 500mg           120  OK
10  Soro Fisiologico         180  OK
11  Paracetamol 750mg        210  OK
12  Omeprazol 20mg           300  OK

=== RESUMO ===
Comparacoes realizadas: 63
Trocas realizadas:      38
Medicamentos vencendo em ate 30 dias: 5
Menor prazo: Insulina NPH (3 dias)
Maior prazo: Omeprazol 20mg (300 dias)
```

## 🛠️ Tecnologias e ferramentas

- **Linguagem C** (padrão C99), com as bibliotecas `stdio.h` e `string.h`
- **GCC** para compilar
- **Visual Studio Code** / **OnlineGDB** para editar e testar
- **Git** para controlar as versões
- **GitHub** para hospedar o repositório e colaborar

## 🗂️ Estrutura do repositório

```
.
├── farmacia.c   # código-fonte da aplicação
├── README.md    # documentação do projeto
└── .gitignore   # ignora os executáveis gerados
```

## 📝 Considerações finais

O projeto mostrou como um algoritmo simples, como o Bubble Sort, resolve um problema real de gestão de estoque. Durante o desenvolvimento, aplicamos:

- **arrays** paralelos (nomes e dias) e o cuidado de trocar os dois juntos para não "descasar" os dados;
- **estruturas de repetição** aninhadas e **condicionais**, tanto para ordenar quanto para classificar a urgência;
- **modularização** em funções (`exibirEstoque`, `bubbleSort`, `lerInteiro`, `cadastrarMedicamentos`);
- **validação de entrada**, para o programa não travar com valores inválidos;
- **versionamento com Git/GitHub**, com commits que registram cada etapa da evolução do código.

Também percebemos uma limitação do Bubble Sort: ele é O(n²) e fica lento para estoques muito grandes. Nesses casos, algoritmos como Merge Sort ou Quick Sort seriam mais indicados. Para fins didáticos e listas pequenas, porém, ele é claro, fácil de entender e cumpre bem o objetivo.
