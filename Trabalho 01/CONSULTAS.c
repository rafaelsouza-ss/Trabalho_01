#include <stdio.h>

#define MAX_PACIENTES 15
#define MAX_CONSULTAS 30

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int codigo;
    char nome[51];
    int idade;
} Paciente;

typedef struct {
    Paciente paciente;
    Data dataConsulta;
    char descricao[121];
} Consulta;

int buscarPaciente(const Paciente pacientes[], int totalPacientes, int codigo) {
    for (int i = 0; i < totalPacientes; i++) {
        if (pacientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int mesmaData(Data d1, Data d2) {
    return (d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano);
}

int main(void) {
    Paciente pacientes[MAX_PACIENTES];
    Consulta consultas[MAX_CONSULTAS];
    int totalPacientes = 0;
    int totalConsultas = 0;
    int opcao;

    do {
        printf("\n--- CLINICA - PACIENTES E CONSULTAS ---\n");
        printf("1. Cadastrar paciente (ate %d)\n", MAX_PACIENTES);
        printf("2. Registrar consulta (ate %d)\n", MAX_CONSULTAS);
        printf("3. Pesquisar consultas de um paciente pelo codigo\n");
        printf("4. Listar consultas em determinada data\n");
        printf("5. Contabilizar consultas por paciente e ver o que mais atendeu\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (totalPacientes >= MAX_PACIENTES) {
                    printf("Limite de %d pacientes atingido!\n", MAX_PACIENTES);
                    break;
                }
                int cod;
                printf("Codigo do paciente: ");
                scanf("%d", &cod);
                if (buscarPaciente(pacientes, totalPacientes, cod) != -1) {
                    printf("Ja existe paciente com esse codigo!\n");
                    break;
                }
                pacientes[totalPacientes].codigo = cod;
                printf("Nome: ");
                scanf(" %50[^\n]", pacientes[totalPacientes].nome);
                printf("Idade: ");
                scanf("%d", &pacientes[totalPacientes].idade);

                totalPacientes++;
                printf("Paciente cadastrado!\n");
                break;
            }
            case 2: {
                if (totalConsultas >= MAX_CONSULTAS) {
                    printf("Limite de %d consultas atingido!\n", MAX_CONSULTAS);
                    break;
                }
                if (totalPacientes == 0) {
                    printf("Cadastre ao menos um paciente primeiro!\n");
                    break;
                }

                int cod;
                printf("Codigo do paciente: ");
                scanf("%d", &cod);
                int idx = buscarPaciente(pacientes, totalPacientes, cod);
                if (idx == -1) {
                    printf("Paciente nao encontrado!\n");
                    break;
                }

                consultas[totalConsultas].paciente = pacientes[idx];
                printf("Data da consulta (dd mm aaaa): ");
                scanf("%d %d %d",
                      &consultas[totalConsultas].dataConsulta.dia,
                      &consultas[totalConsultas].dataConsulta.mes,
                      &consultas[totalConsultas].dataConsulta.ano);

                printf("Descricao do atendimento: ");
                scanf(" %120[^\n]", consultas[totalConsultas].descricao);

                totalConsultas++;
                printf("Consulta registrada!\n");
                break;
            }
            case 3: {
                int cod, encontrou = 0;
                printf("Codigo do paciente: ");
                scanf("%d", &cod);

                printf("\n--- Consultas do paciente codigo %d ---\n", cod);
                for (int i = 0; i < totalConsultas; i++) {
                    if (consultas[i].paciente.codigo == cod) {
                        printf("Data: %02d/%02d/%04d | Paciente: %s | Descricao: %s\n",
                               consultas[i].dataConsulta.dia,
                               consultas[i].dataConsulta.mes,
                               consultas[i].dataConsulta.ano,
                               consultas[i].paciente.nome,
                               consultas[i].descricao);
                        encontrou = 1;
                    }
                }
                if (!encontrou) {
                    printf("Nenhuma consulta encontrada para este codigo.\n");
                }
                break;
            }
            case 4: {
                Data busca;
                int encontrou = 0;
                printf("Informe a data (dd mm aaaa): ");
                scanf("%d %d %d", &busca.dia, &busca.mes, &busca.ano);

                printf("\n--- Consultas em %02d/%02d/%04d ---\n",
                       busca.dia, busca.mes, busca.ano);
                for (int i = 0; i < totalConsultas; i++) {
                    if (mesmaData(consultas[i].dataConsulta, busca)) {
                        printf("Paciente: %s (Cod. %d) | Descricao: %s\n",
                               consultas[i].paciente.nome,
                               consultas[i].paciente.codigo,
                               consultas[i].descricao);
                        encontrou = 1;
                    }
                }
                if (!encontrou) {
                    printf("Nenhuma consulta realizada nessa data.\n");
                }
                break;
            }
            case 5: {
                if (totalPacientes == 0) {
                    printf("Nenhum paciente cadastrado.\n");
                    break;
                }

                int maiorQtd = -1;
                int idxMaisAtendido = 0;

                printf("\n--- Numero de consultas por paciente ---\n");
                for (int p = 0; p < totalPacientes; p++) {
                    int cont = 0;
                    for (int c = 0; c < totalConsultas; c++) {
                        if (consultas[c].paciente.codigo == pacientes[p].codigo) {
                            cont++;
                        }
                    }
                    printf("Cod. %d | %s: %d consulta(s)\n",
                           pacientes[p].codigo, pacientes[p].nome, cont);

                    if (cont > maiorQtd) {
                        maiorQtd = cont;
                        idxMaisAtendido = p;
                    }
                }

                if (maiorQtd > 0) {
                    printf("\nPaciente com maior numero de atendimentos: %s (Cod. %d) com %d consulta(s).\n",
                           pacientes[idxMaisAtendido].nome,
                           pacientes[idxMaisAtendido].codigo,
                           maiorQtd);
                } else {
                    printf("\nNenhuma consulta registrada ate o momento.\n");
                }
                break;
            }
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}