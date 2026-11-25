#include <stdio.h>

#define MAX_FUNCIONARIOS 8
#define HORAS_MENSAIS 160.0f

typedef struct {
    int codigo;
    char nome[51];
    char cargo[41];
    float salarioBase;
    float horasExtras;
    float salarioBruto;
    float salarioLiquido;
} Funcionario;

void calcularSalarios(Funcionario *f) {
    float valorHora = f->salarioBase / HORAS_MENSAIS;
    float valorHoraExtra = valorHora * 1.5f; /* acréscimo de 50% */
    f->salarioBruto = f->salarioBase + (f->horasExtras * valorHoraExtra);
    f->salarioLiquido = f->salarioBruto * 0.90f; /* desconto de 10% */
}

int main(void) {
    Funcionario funcs[MAX_FUNCIONARIOS];
    int qtd;

    do {
        printf("Quantos funcionarios deseja cadastrar (1 a %d)? ", MAX_FUNCIONARIOS);
        scanf("%d", &qtd);
    } while (qtd < 1 || qtd > MAX_FUNCIONARIOS);

    float custoTotalFolha = 0.0f;
    int idxMaiorLiquido = 0;

    for (int i = 0; i < qtd; i++) {
        printf("\n--- Funcionario %d ---\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &funcs[i].codigo);

        printf("Nome: ");
        scanf(" %50[^\n]", funcs[i].nome);

        printf("Cargo: ");
        scanf(" %40[^\n]", funcs[i].cargo);

        printf("Salario-base (R$): ");
        scanf("%f", &funcs[i].salarioBase);

        printf("Quantidade de horas extras: ");
        scanf("%f", &funcs[i].horasExtras);

        calcularSalarios(&funcs[i]);
        custoTotalFolha += funcs[i].salarioLiquido;

        if (funcs[i].salarioLiquido > funcs[idxMaiorLiquido].salarioLiquido) {
            idxMaiorLiquido = i;
        }
    }

    printf("\n===== FOLHA DE PAGAMENTO =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("Cod: %d | %s (%s) | Bruto: R$ %.2f | Liquido: R$ %.2f\n",
               funcs[i].codigo, funcs[i].nome, funcs[i].cargo,
               funcs[i].salarioBruto, funcs[i].salarioLiquido);
    }

    printf("\n===== RESUMO =====\n");
    printf("Maior salario liquido: R$ %.2f (%s - Cod. %d)\n",
           funcs[idxMaiorLiquido].salarioLiquido,
           funcs[idxMaiorLiquido].nome,
           funcs[idxMaiorLiquido].codigo);
    printf("Custo total da folha (liquido): R$ %.2f\n", custoTotalFolha);

    return 0;
}