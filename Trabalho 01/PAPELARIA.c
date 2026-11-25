#include <stdio.h>

#define MAX_PRODUTOS 15

typedef struct {
    int codigo;
    char nome[51];
    float preco;
    int estoque;
} Produto;

int buscarIndicePorCodigo(const Produto produtos[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void reporEstoque(Produto *p, int qtd) {
    if (qtd > 0) {
        p->estoque += qtd;
    }
}

int registrarVendaEstoque(Produto *p, int qtd) {
    if (qtd <= 0 || qtd > p->estoque) {
        return 0; /* falha: quantidade inválida ou insuficiente */
    }
    p->estoque -= qtd;
    return 1; /* sucesso */
}

void exibirRelatorioEstoque(const Produto produtos[], int total) {
    if (total == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    float valorTotalEstoque = 0.0f;
    int idxMaiorValor = 0;
    float maiorValorTotal = -1.0f;

    printf("\n===== PRODUTOS CADASTRADOS =====\n");
    for (int i = 0; i < total; i++) {
        float valorItem = produtos[i].preco * produtos[i].estoque;
        valorTotalEstoque += valorItem;

        if (valorItem > maiorValorTotal) {
            maiorValorTotal = valorItem;
            idxMaiorValor = i;
        }

        printf("Cod: %d | %s | Preco: R$ %.2f | Estoque: %d | Valor em estoque: R$ %.2f\n",
               produtos[i].codigo, produtos[i].nome, produtos[i].preco,
               produtos[i].estoque, valorItem);
    }

    printf("\nValor total dos produtos em estoque: R$ %.2f\n", valorTotalEstoque);
    printf("Maior valor total em estoque: %s (Cod. %d) - R$ %.2f\n",
           produtos[idxMaiorValor].nome, produtos[idxMaiorValor].codigo, maiorValorTotal);
}

int main(void) {
    Produto produtos[MAX_PRODUTOS];
    int total = 0;
    int opcao;

    do {
        printf("\n--- PAPELARIA - MENU ---\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos e resumo de estoque\n");
        printf("3. Repor estoque\n");
        printf("4. Registrar venda\n");
        printf("5. Consultar produto pelo codigo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (total >= MAX_PRODUTOS) {
                    printf("Limite de %d produtos atingido!\n", MAX_PRODUTOS);
                    break;
                }
                int cod;
                printf("Codigo: ");
                scanf("%d", &cod);

                if (buscarIndicePorCodigo(produtos, total, cod) != -1) {
                    printf("Erro: ja existe um produto com o codigo %d!\n", cod);
                    break;
                }

                produtos[total].codigo = cod;
                printf("Nome: ");
                scanf(" %50[^\n]", produtos[total].nome);
                printf("Preco (R$): ");
                scanf("%f", &produtos[total].preco);
                printf("Quantidade em estoque: ");
                scanf("%d", &produtos[total].estoque);

                total++;
                printf("Produto cadastrado com sucesso!\n");
                break;
            }
            case 2:
                exibirRelatorioEstoque(produtos, total);
                break;
            case 3: {
                int cod, qtd;
                printf("Codigo do produto: ");
                scanf("%d", &cod);
                int idx = buscarIndicePorCodigo(produtos, total, cod);
                if (idx == -1) {
                    printf("Produto nao encontrado!\n");
                    break;
                }
                printf("Quantidade a repor: ");
                scanf("%d", &qtd);
                if (qtd <= 0) {
                    printf("Quantidade invalida!\n");
                    break;
                }
                reporEstoque(&produtos[idx], qtd);
                printf("Estoque atualizado! Novo estoque: %d\n", produtos[idx].estoque);
                break;
            }
            case 4: {
                int cod, qtd;
                printf("Codigo do produto: ");
                scanf("%d", &cod);
                int idx = buscarIndicePorCodigo(produtos, total, cod);
                if (idx == -1) {
                    printf("Produto nao encontrado!\n");
                    break;
                }
                printf("Quantidade a vender (disponivel: %d): ", produtos[idx].estoque);
                scanf("%d", &qtd);
                if (registrarVendaEstoque(&produtos[idx], qtd)) {
                    printf("Venda registrada! Total: R$ %.2f | Restante: %d\n",
                           produtos[idx].preco * qtd, produtos[idx].estoque);
                } else {
                    printf("Venda nao realizada! Quantidade invalida ou superior ao estoque.\n");
                }
                break;
            }
            case 5: {
                int cod;
                printf("Codigo para consulta: ");
                scanf("%d", &cod);
                int idx = buscarIndicePorCodigo(produtos, total, cod);
                if (idx == -1) {
                    printf("Produto nao encontrado!\n");
                } else {
                    Produto p = produtos[idx];
                    printf("Cod: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d | Valor total: R$ %.2f\n",
                           p.codigo, p.nome, p.preco, p.estoque, p.preco * p.estoque);
                }
                break;
            }
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}