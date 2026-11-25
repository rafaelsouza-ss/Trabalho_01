#include <stdio.h>

#define TOTAL_ALUNOS 10

typedef struct {
    int matricula;
    char nome[51];
    float nota1;
    float nota2;
    float media;
} Aluno;

float calcularMedia(float n1, float n2) {
    return (n1 + n2) / 2.0f;
}

int main(void) {
    Aluno turma[TOTAL_ALUNOS];
    float somaMedias = 0.0f;
    int idxMaior = 0;
    int idxMenor = 0;

    /* 1. Cadastrar os 10 alunos e calcular média individual */
    for (int i = 0; i < TOTAL_ALUNOS; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);
        printf("Matricula: ");
        scanf("%d", &turma[i].matricula);

        printf("Nome: ");
        scanf(" %50[^\n]", turma[i].nome);

        printf("Nota 1: ");
        scanf("%f", &turma[i].nota1);

        printf("Nota 2: ");
        scanf("%f", &turma[i].nota2);

        turma[i].media = calcularMedia(turma[i].nota1, turma[i].nota2);
        somaMedias += turma[i].media;

        if (turma[i].media > turma[idxMaior].media) {
            idxMaior = i;
        }
        if (turma[i].media < turma[idxMenor].media) {
            idxMenor = i;
        }
    }

    /* 3. Exibir situação de cada aluno */
    printf("\n===== SITUACAO DOS ALUNOS =====\n");
    for (int i = 0; i < TOTAL_ALUNOS; i++) {
        const char *situacao = (turma[i].media >= 6.0f) ? "APROVADO" : "REPROVADO";
        printf("Mat.: %d | Nome: %s | N1: %.1f | N2: %.1f | Media: %.2f | %s\n",
               turma[i].matricula, turma[i].nome, turma[i].nota1,
               turma[i].nota2, turma[i].media, situacao);
    }

    /* 5. Média geral da turma */
    float mediaGeral = somaMedias / TOTAL_ALUNOS;

    /* 6. Contar alunos acima da média geral */
    int acimaMediaGeral = 0;
    for (int i = 0; i < TOTAL_ALUNOS; i++) {
        if (turma[i].media > mediaGeral) {
            acimaMediaGeral++;
        }
    }

    /* 4. Maior e menor média */
    printf("\n===== RESUMO DA TURMA =====\n");
    printf("Maior media: %.2f (%s - Mat. %d)\n",
           turma[idxMaior].media, turma[idxMaior].nome, turma[idxMaior].matricula);
    printf("Menor media: %.2f (%s - Mat. %d)\n",
           turma[idxMenor].media, turma[idxMenor].nome, turma[idxMenor].matricula);
    printf("Media geral da turma: %.2f\n", mediaGeral);
    printf("Alunos acima da media geral: %d\n", acimaMediaGeral);

    return 0;
}