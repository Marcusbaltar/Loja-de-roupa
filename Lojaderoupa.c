#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Incluído para setlocale

#define MAX_VENDAS 500

typedef struct {
    int dia;
    int mes;
    int ano; // Campo para o ano
    char codigo[8]; // 7 caracteres + 1 para o '\0'
    char nome[30];
    char marca[20];
    int quantidade;
    float preco_unitario;
    float total;
} Venda;

Venda vendas[MAX_VENDAS]; // Variável global não mais usada para armazenamento primário
int total_vendas = 0;    // Variável global não mais usada para controle do array global

float calcular_total(int quantidade, float preco_unitario) {
    float total = quantidade * preco_unitario;
    if (quantidade >= 3) {
        total *= 0.9; // Aplica 10% de desconto
    }
    return total;
}

void registrar_venda() {
    Venda v;
    printf("Dia da venda (DD): ");
    scanf("%d", &v.dia);
    printf("M%cs da venda (MM): ", 136); // "Mês"
    scanf("%d", &v.mes);
    printf("Ano da venda (AAAA): ");
    scanf("%d", &v.ano);
    printf("C%cdigo do item (m%cx. 7 caracteres): ", 162, 225); // "Código", "máx."
    scanf(" %7s", v.codigo);
    printf("Nome do item: ");
    scanf(" %29s", v.nome);
    printf("Marca do item: ");
    scanf(" %19s", v.marca);
    printf("Quantidade de itens: ");
    scanf("%d", &v.quantidade);
    printf("Pre%co unit%crio: ", 135, 161); // "Preço", "unitário"
    scanf("%f", &v.preco_unitario);

    v.total = calcular_total(v.quantidade, v.preco_unitario);

    FILE *f = fopen("loja_roupa.txt", "a");
    if (f != NULL) {
        fwrite(&v, sizeof(Venda), 1, f);
        fclose(f);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }

    printf("Total da venda: R$ %.2f", v.total);
    if (v.quantidade >= 3) {
        printf(" (Desconto de 10%% aplicado por comprar 3 ou mais unidades)\n");
    } else {
        printf(" (Sem desconto)\n");
    }
    printf("Quantidade total de itens vendidos nesta venda: %d\n", v.quantidade);
}

// Função de comparação para qsort (ordena por total em ordem decrescente)
int comparar(const void *a, const void *b) {
    Venda *v1 = (Venda *)a;
    Venda *v2 = (Venda *)b;
    return (v2->total > v1->total) - (v2->total < v1->total);
}

// Carrega vendas filtradas por ano, mês e dia
int carregar_vendas_por_data(int ano, int mes, int dia, Venda *filtro, int *qtde) {
    FILE *f = fopen("loja_roupa.txt", "r");
    if (!f) return 0; // Erro ao abrir o arquivo

    Venda temp;
    *qtde = 0;

    while (fread(&temp, sizeof(Venda), 1, f)) {
        if (temp.ano == ano && temp.mes == mes && temp.dia == dia) {
            filtro[(*qtde)++] = temp;
        }
    }
    fclose(f);
    return 1; // Sucesso
}

void listar_vendas_por_data() {
    int dia, mes, ano;
    printf("Informe o dia (DD): ");
    scanf("%d", &dia);
    printf("Informe o m%cs (MM): ", 136); // "mês"
    scanf("%d", &mes);
    printf("Informe o ano (AAAA): ");
    scanf("%d", &ano);

    Venda filtro[MAX_VENDAS];
    int qtde = 0;

    if (!carregar_vendas_por_data(ano, mes, dia, filtro, &qtde)) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (qtde == 0) {
        printf("Nenhuma venda encontrada para %02d/%02d/%04d.\n", dia, mes, ano);
        return;
    }

    qsort(filtro, qtde, sizeof(Venda), comparar);

    printf("\nVendas em %02d/%02d/%04d (ordenadas por valor decrescente):\n", dia, mes, ano);
    for (int i = 0; i < qtde; i++) {
        printf("%s %s %s - Qtde: %d - Total: R$ %.2f\n",
               filtro[i].codigo, filtro[i].nome, filtro[i].marca,
               filtro[i].quantidade, filtro[i].total);
    }
}

void faturamento_bruto() {
    int dia, mes, ano;
    printf("Informe o dia (DD): ");
    scanf("%d", &dia);
    printf("Informe o m%cs (MM): ", 136); // "mês"
    scanf("%d", &mes);
    printf("Informe o ano (AAAA): ");
    scanf("%d", &ano);

    Venda filtro[MAX_VENDAS];
    int qtde = 0;
    float soma = 0.0;

    if (!carregar_vendas_por_data(ano, mes, dia, filtro, &qtde)) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (qtde == 0) {
        printf("Nenhuma venda encontrada para %02d/%02d/%04d.\n", dia, mes, ano);
        return;
    }

    for (int i = 0; i < qtde; i++) {
        soma += filtro[i].total;
    }
    printf("Faturamento bruto em %02d/%02d/%04d: R$ %.2f\n", dia, mes, ano, soma);
}

void contar_clientes() {
    int dia, mes, ano;
    printf("Informe o dia (DD): ");
    scanf("%d", &dia);
    printf("Informe o m%cs (MM): ", 136); // "mês"
    scanf("%d", &mes);
    printf("Informe o ano (AAAA): ");
    scanf("%d", &ano);

    Venda filtro[MAX_VENDAS];
    int qtde = 0;

    if (!carregar_vendas_por_data(ano, mes, dia, filtro, &qtde)) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Vendas realizadas em %02d/%02d/%04d: %d\n", dia, mes, ano, qtde);
    printf("Observa%c%co: Este valor representa o n%cmero de transa%c%ces, n%co necessariamente clientes %cnicos.\n",
            135, 198, 163, 135, 198, 198, 163); // "Observação", "número", "transações", "não", "únicos"
}

void item_mais_menos_vendido(int mais) { // 'mais' = 1 para mais vendido, 0 para menos vendido
    int dia, mes, ano;
    printf("Informe o dia (DD): ");
    scanf("%d", &dia);
    printf("Informe o m%cs (MM): ", 136); // "mês"
    scanf("%d", &mes);
    printf("Informe o ano (AAAA): ");
    scanf("%d", &ano);

    Venda filtro[MAX_VENDAS];
    int qtde = 0;

    if (!carregar_vendas_por_data(ano, mes, dia, filtro, &qtde)) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (qtde == 0) {
        printf("Nenhuma venda nesta data (%02d/%02d/%04d).\n", dia, mes, ano);
        return;
    }

    int idx = 0; // Índice do item mais/menos vendido
    for (int i = 1; i < qtde; i++) {
        if ((mais && filtro[i].quantidade > filtro[idx].quantidade) ||
            (!mais && filtro[i].quantidade < filtro[idx].quantidade)) {
            idx = i;
        }
    }

    printf("%s vendido em %02d/%02d/%04d: %s (%d unidades)\n",
           mais ? "Item mais" : "Item menos", dia, mes, ano,
           filtro[idx].nome, filtro[idx].quantidade);
}

void menu() {
    int opc;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Registrar nova venda\n");
        printf("2. Listar vendas por data (DD/MM/AAAA - ordem decrescente de valor)\n");
        printf("3. Faturamento bruto di%crio/mensal\n", 161); // "diário"
        printf("4. Quantidade de vendas por data (DD/MM/AAAA)\n");
        printf("5. Item mais vendido por data (DD/MM/AAAA)\n");
        printf("6. Item menos vendido por data (DD/MM/AAAA)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: registrar_venda(); break;
            case 2: listar_vendas_por_data(); break;
            case 3: faturamento_bruto(); break;
            case 4: contar_clientes(); break;
            case 5: item_mais_menos_vendido(1); break;
            case 6: item_mais_menos_vendido(0); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Op%c%co inv%clida!\n", 135, 198, 160); // "Opção inválida"
        }
    } while (opc != 0);
}

int main() {
    // Manter o setlocale é boa prática, mas a exibição real dependerá do terminal.
    // Ele tenta configurar o ambiente C para pt-BR e UTF-8.
    setlocale(LC_ALL, "pt_BR.UTF-8"); // ou apenas ""

    // Se o problema de acentuação persistir, é porque seu terminal não está em UTF-8.
    // Nesses casos, execute 'chcp 65001' no seu terminal ANTES de iniciar o programa.
    // system("chcp 65001 > nul"); // Descomente só se souber o que está fazendo

    menu();
    return 0;
}