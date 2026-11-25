#include <stdio.h>

#define MAX_PRODUTOS 10
#define MAX_VENDAS 20

typedef struct {
    int codigo;
    char nome[51];
    float preco;
    int estoque;
} Produto;

typedef struct {
    Produto produto;
    int quantidadeVendida;
    float valorTotal;
} Venda;

int buscarProduto(const Produto produtos[], int totalProdutos, int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    Produto produtos[MAX_PRODUTOS];
    Venda vendas[MAX_VENDAS];
    int totalProdutos = 0;
    int totalVendas = 0;
    int opcao;

    do {
        printf("\n--- LOJA - CONTROLE DE VENDAS ---\n");
        printf("1. Cadastrar produto (ate %d)\n", MAX_PRODUTOS);
        printf("2. Registrar venda (ate %d)\n", MAX_VENDAS);
        printf("3. Listar produtos\n");
        printf("4. Listar vendas e relatorio de faturamento\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (totalProdutos >= MAX_PRODUTOS) {
                    printf("Limite de %d produtos atingido!\n", MAX_PRODUTOS);
                    break;
                }
                int cod;
                printf("Codigo do produto: ");
                scanf("%d", &cod);
                if (buscarProduto(produtos, totalProdutos, cod) != -1) {
                    printf("Codigo ja cadastrado!\n");
                    break;
                }
                produtos[totalProdutos].codigo = cod;
                printf("Nome: ");
                scanf(" %50[^\n]", produtos[totalProdutos].nome);
                printf("Preco (R$): ");
                scanf("%f", &produtos[totalProdutos].preco);
                printf("Estoque inicial: ");
                scanf("%d", &produtos[totalProdutos].estoque);

                totalProdutos++;
                printf("Produto cadastrado!\n");
                break;
            }
            case 2: {
                if (totalVendas >= MAX_VENDAS) {
                    printf("Limite de %d vendas atingido!\n", MAX_VENDAS);
                    break;
                }
                if (totalProdutos == 0) {
                    printf("Cadastre ao menos um produto antes de vender!\n");
                    break;
                }

                int cod, qtd;
                printf("Codigo do produto: ");
                scanf("%d", &cod);
                int idx = buscarProduto(produtos, totalProdutos, cod);
                if (idx == -1) {
                    printf("Produto nao encontrado!\n");
                    break;
                }

                printf("Quantidade vendida (disponivel: %d): ", produtos[idx].estoque);
                scanf("%d", &qtd);
                if (qtd <= 0 || qtd > produtos[idx].estoque) {
                    printf("Quantidade invalida ou acima do estoque disponivel!\n");
                    break;
                }

                produtos[idx].estoque -= qtd; /* atualiza estoque */
                vendas[totalVendas].produto = produtos[idx];
                vendas[totalVendas].quantidadeVendida = qtd;
                vendas[totalVendas].valorTotal = produtos[idx].preco * qtd;
                totalVendas++;

                printf("Venda registrada! Valor total: R$ %.2f\n",
                       vendas[totalVendas - 1].valorTotal);
                break;
            }
            case 3:
                printf("\n===== PRODUTOS =====\n");
                for (int i = 0; i < totalProdutos; i++) {
                    printf("Cod: %d | %s | Preco: R$ %.2f | Estoque: %d\n",
                           produtos[i].codigo, produtos[i].nome,
                           produtos[i].preco, produtos[i].estoque);
                }
                break;
            case 4: {
                float faturamentoTotal = 0.0f;
                printf("\n===== VENDAS REGISTRADAS =====\n");
                for (int i = 0; i < totalVendas; i++) {
                    printf("%d) %s (Cod. %d) | Qtd: %d | Total: R$ %.2f\n",
                           i + 1, vendas[i].produto.nome, vendas[i].produto.codigo,
                           vendas[i].quantidadeVendida, vendas[i].valorTotal);
                    faturamentoTotal += vendas[i].valorTotal;
                }

                /* Faturamento por produto cadastrado */
                int idxCampeao = -1;
                float maiorFaturamento = -1.0f;

                for (int p = 0; p < totalProdutos; p++) {
                    float fatProduto = 0.0f;
                    for (int v = 0; v < totalVendas; v++) {
                        if (vendas[v].produto.codigo == produtos[p].codigo) {
                            fatProduto += vendas[v].valorTotal;
                        }
                    }
                    if (fatProduto > maiorFaturamento) {
                        maiorFaturamento = fatProduto;
                        idxCampeao = p;
                    }
                }

                printf("\nFaturamento total da loja: R$ %.2f\n", faturamentoTotal);
                if (idxCampeao != -1 && maiorFaturamento > 0.0f) {
                    printf("Produto com maior faturamento: %s (Cod. %d) - R$ %.2f\n",
                           produtos[idxCampeao].nome, produtos[idxCampeao].codigo,
                           maiorFaturamento);
                } else {
                    printf("Ainda nao ha faturamento para identificar o produto campeao.\n");
                }
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}