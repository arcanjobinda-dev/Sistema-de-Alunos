#include <stdio.h> // Biblioteca principal
#include <string.h> // Biblioteca para usar "strcmp"
#include <stdlib.h> // Biblioteca para usar "malloc"

struct Aluno {

    char nome[50];
    int idade;
    float notas[3];

};
float calcularMedia(struct Aluno *p);

void lerAluno(struct Aluno *p) {

    printf("Nome: ");
    fgets(p->nome, sizeof(p->nome), stdin);

    printf("Idade: ");
    scanf("%d", &p->idade);

    for(int i = 0; i < 3; i++) {
        printf("%d° Nota: ", i+1);
        scanf("%f", &p->notas[i]);
    }

    getchar();

}
void mostrarAlunos(struct Aluno *p, int tamanho) {

    for(int i = 0; i < tamanho; i++) {
        printf("\n=== %d° ALUNO ===\n\n", i+1);
        printf("Nome: %s", (p + i)->nome);
        printf("Idade: %d\n", (p + i)->idade);
        
        for(int j = 0; j < 3; j++) {
            printf("%d° Nota: %.1f\n", j+1, (p + i)->notas[j]);
        }

        float media = calcularMedia(p + i);
        printf("Media: %.2f\n", media);

        if(media >= 10) {
            printf("Aprovado\n");
        } else if (media >=7) {
            printf("Recurso\n");
        } else {
            printf("Reprovado\n");
        }
    }

}
float calcularMedia(struct Aluno *p) {

    float soma = 0;
    for(int i = 0; i < 3; i++) {
        soma += p->notas[i];
    }
    return soma / 3;

}
int procurarMelhorAluno(struct Aluno *p, int tamanho) {

    int melhor = 0;
    float maiorMedia = calcularMedia(p);

    for(int i = 1; i < tamanho; i++) {
        float media = calcularMedia(p + 1);

        if(media > maiorMedia) {
            maiorMedia = media;
            melhor = i;
        }
    }
    return melhor;

}
int procurarAluno(struct Aluno *p, int tamanho, char nome[]) {

    for(int i = 0; i < tamanho; i++) {

        if(strcmp((p + i)->nome, nome) == 0) {
            return i;
        }
    }
    return -1;

}
int main(void) {

    int quantidadeAlunos;
    int capacidade;
    int cadastrados = 0;
    int opcao;

    printf("\nCapacidade de Alunos: ");
    scanf("%d", &capacidade);
    getchar();

    struct Aluno *alunos = malloc(capacidade * sizeof(struct Aluno));

    if(alunos == NULL) {
        printf("ERRO ao alocar memoria.\n");
        return 1;
    }

    do {
        printf("\n=== SISTEMA DE ALUNOS ===\n\n");
        printf("1. Cadastrar Alunos\n");
        printf("2. Mostrar Alunos\n");
        printf("3. Procurar Aluno\n");
        printf("4. Mostrar Melhor Aluno\n");
        printf("5. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1:
                printf("\n=== Cadastro de Alunos ===\n");
                printf("\nQuantos alunos deseja cadastrar agora?: ");
                scanf("%d", &quantidadeAlunos);
                getchar();

                if(cadastrados + quantidadeAlunos > capacidade) {
                    
                    capacidade += quantidadeAlunos;

                    struct Aluno *temp = realloc(alunos, capacidade * sizeof(struct Aluno));

                    if(temp == NULL) {
                        printf("ERRO ao aumentar memoria.\n");
                        break;
                    }
                    alunos = temp;

                    printf("Capacidade aumentada para %d alunos.\n", capacidade);

                }
                for(int i = 0; i < quantidadeAlunos; i++) {
                    printf("\n=== %d° ALUNO ===\n\n", cadastrados + 1);
                    lerAluno(&alunos[cadastrados]);
                    cadastrados++;
                }
                printf("\nCadastro Concluido.\n");
                printf("%d de %d alunos cadastrados.\n", cadastrados, capacidade);
                break;

            case 2:
                if(cadastrados > 0) {
                    printf("\n=== Alunos Cadastrados ===\n");
                    mostrarAlunos(alunos, cadastrados);
                } else {
                    printf("\nNenhum aluno cadastrado.\n");
                }
                break;

            case 3:
                if(cadastrados > 0) {
                    char resposta;
                    printf("\nDeseja procurar um aluno? (s/n): ");
                    scanf(" %c", &resposta);
                    getchar();

                    while(resposta == 's' || resposta == 'S') {
                        char nomeBusca[50];
                        printf("Digite o nome do Aluno que deseja procurar: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\n';

                        int posicao = procurarAluno(alunos, cadastrados, nomeBusca);

                        if(posicao != -1) {
                            printf("\n=== Aluno encontrado ===\n");
                            printf("Nome: %s", alunos[posicao].nome);
                            printf("Idade: %d\n", alunos[posicao].idade);
                            for(int i = 0; i < 3; i++) {
                                printf("%d° Nota: %.1f\n", i+1, alunos[posicao].notas[i]);
                            }
                            printf("Media: %.2f\n", calcularMedia(&alunos[posicao]));

                        } else {
                            printf("Aluno nao encontrado\n");
                        }
                        printf("\nDeseja procurar outro aluno? (s/n): ");
                        scanf(" %c", &resposta);
                        getchar();
                    }
                } else {
                    printf("\nNenhum aluno cadastrado.\n");
                }
                break;

            case 4:
                if(cadastrados > 0) {
                    int melhor = procurarMelhorAluno(alunos, cadastrados);
                    printf("\n=== Melhor Aluno ===\n");

                    printf("Nome: %s", alunos[melhor].nome);
                    printf("Idade: %d\n", alunos[melhor].idade);
                    for(int i = 0; i < 3; i++) {
                        printf("%d° Nota: %.1f\n", i+1, alunos[melhor].notas[i]);
                    }
                    printf("Media: %.2f\n", calcularMedia(&alunos[melhor]));

                } else {
                    printf("\nNenhum aluno cadastrado.\n");
                }
                break;

            case 5:
                printf("Sair...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 5);

    return 0;
}