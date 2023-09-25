#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 100

void menu();
void Imprimir();
void ImprimirArq();
void enfileirar();
void desenfileirar();
void guardar_no_arquivo();
void imprimir();

FILE *Arquivo;

typedef struct
{
    char nome[50];
    float notasp[2][3];
    char curso[50];
    int idade;
    float medias1;
    float medias2;
} Aluno;

typedef struct 
{
    Aluno *fila;
    int ini, fim;
    int capacidade;
} Tfila;

Tfila minhafila;

int QuantAlunos;

void inicializarFila(int capacidade) {
    minhafila.fila = (Aluno*)malloc(capacidade * sizeof(Aluno));
    minhafila.capacidade = capacidade;
    minhafila.ini = 0;
    minhafila.fim = 0;
}

void desalocarFila() {
    free(minhafila.fila);
}

void menu()
{
    char casos;
    int continuar = 1;
    while (continuar == 1)
    {
        printf("\n######## Bem-vindo ao cadastro de aluno! ########\nNeste programa você poderá armazenar seus dados e depois consultá-los.\n");
        printf("Opções:\nC - cadastrar um aluno\nM - mostrar alunos cadastrados no último uso\nP - mostrar alunos cadastrados no uso atual\nA - apagar o último cadastro\nF - fechar programa\n");
        scanf(" %c", &casos);
        getchar();
        switch(casos)
        {
            case 'C':
                enfileirar();
                break;
            case 'M':
                ImprimirArq();
                break;
            case  'P':
                Imprimir();
                break;
            case 'A':
                desenfileirar();
                break;
            case 'F':
                guardar_no_arquivo();
                continuar = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
    printf("\nObrigado por utilizar nosso programa! Até logo! :)\n");
}

void enfileirar()
{
    if (minhafila.fim == minhafila.capacidade) {
        printf("Número máximo de alunos cadastrados atingido! Não é possível cadastrar mais.\n");
    } else {
        Aluno aux;
        printf("\nDigite o nome do aluno: ");
        fgets(aux.nome, 50, stdin);
        printf("Digite o curso do aluno: ");
        fgets(aux.curso, 50, stdin);
        printf("Digite a idade do aluno: ");
        scanf("%d", &aux.idade);
        getchar();
        printf("Agora, digite as notas do aluno:\n");

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("Digite a nota %d do %dº período: ", j + 1, i + 1);
                scanf("%f", &aux.notasp[i][j]);
            }
        }

        aux.medias1 = (aux.notasp[0][0] + aux.notasp[0][1] + aux.notasp[0][2]) / 3;
        aux.medias2 = (aux.notasp[1][0] + aux.notasp[1][1] + aux.notasp[1][2]) / 3;

        minhafila.fila[minhafila.fim] = aux;
        minhafila.fim++;
        QuantAlunos++;
        printf("\nAluno cadastrado com sucesso!\n");
    }
}

void desenfileirar()
{
    if (minhafila.ini == minhafila.fim)
    {
        printf("\nNão há alunos cadastrados!\n");
    } else {
        printf("\nÚltimo aluno cadastrado foi apagado!\n");
        minhafila.ini++;
        QuantAlunos--;
    }
}

void guardar_no_arquivo()
{
    Arquivo = fopen("arquivo.txt", "w");
    if (Arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    } else {
        fprintf(Arquivo, "%d\n", QuantAlunos);
        for (int i = minhafila.ini; i < minhafila.fim; i++)
        {
            fprintf(Arquivo, "%s", minhafila.fila[i].nome);
            fprintf(Arquivo, "%s", minhafila.fila[i].curso);
            fprintf(Arquivo, "%d\n", minhafila.fila[i].idade);
            fprintf(Arquivo, "%.2f\n", minhafila.fila[i].notasp[0][0]);
            fprintf(Arquivo, "%.2f\n", minhafila.fila[i].notasp[0][1]);
            fprintf(Arquivo, "%.2f\n", minhafila.fila[i].notasp[0][2]);
            fprintf(Arquivo, "%.2f\n", minhafila.fila[i].notasp[1][0]);
            fprintf(Arquivo, "%.2f\n", minhafila.fila[i].notasp[1][1]);
            fprintf(Arquivo, "%.2f\n", minhafila.fila[i].notasp[1][2]);
        }
        fclose(Arquivo);
        printf("\nDados dos alunos foram salvos no arquivo 'arquivo.txt'.\n");
    }
}

void Imprimir()
{
    if (minhafila.ini == minhafila.fim)
    {
        printf("\nNão há alunos cadastrados!\n");
    } else {
        printf("\n----- Alunos Cadastrados -----\n");
        for (int i = minhafila.ini; i < minhafila.fim; i++)
        {
            printf("\nNome: %s", minhafila.fila[i].nome);
            printf("Curso: %s", minhafila.fila[i].curso);
            printf("Idade: %d\n", minhafila.fila[i].idade);
            printf("Notas:\n");
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    printf("Nota %d do %dº período: %.2f\n", k + 1, j + 1, minhafila.fila[i].notasp[j][k]);
                }
            }
            printf("Média 1º período: %.2f\n", minhafila.fila[i].medias1);
            printf("Média 2º período: %.2f\n", minhafila.fila[i].medias2);
        }
    }
}

void ImprimirArq()
{
    Arquivo = fopen("arquivo.txt", "r");
    if (Arquivo == NULL)
    {
        printf("\nNão há alunos cadastrados no último uso do programa!\n");
    } else {
        int quantidade;
        fscanf(Arquivo, "%d\n", &quantidade);
        printf("\n----- Alunos Cadastrados no último uso -----\n");
        for (int i = 0; i < quantidade; i++)
        {
            Aluno aux;
            fgets(aux.nome, 50, Arquivo);
            fgets(aux.curso, 50, Arquivo);
            fscanf(Arquivo, "%d\n", &aux.idade);
            fscanf(Arquivo, "%f\n", &aux.notasp[0][0]);
            fscanf(Arquivo, "%f\n", &aux.notasp[0][1]);
            fscanf(Arquivo, "%f\n", &aux.notasp[0][2]);
            fscanf(Arquivo, "%f\n", &aux.notasp[1][0]);
            fscanf(Arquivo, "%f\n", &aux.notasp[1][1]);
            fscanf(Arquivo, "%f\n", &aux.notasp[1][2]);
            aux.medias1 = (aux.notasp[0][0] + aux.notasp[0][1] + aux.notasp[0][2]) / 3;
            aux.medias2 = (aux.notasp[1][0] + aux.notasp[1][1] + aux.notasp[1][2]) / 3;

            printf("\nNome: %s", aux.nome);
            printf("Curso: %s", aux.curso);
            printf("Idade: %d\n", aux.idade);
            printf("Notas:\n");
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    printf("Nota %d do %dº período: %.2f\n", k + 1, j + 1, aux.notasp[j][k]);
                }
            }
            printf("Média 1º período: %.2f\n", aux.medias1);
            printf("Média 2º período: %.2f\n", aux.medias2);
        }
        fclose(Arquivo);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    inicializarFila(MAX);
    menu();
    desalocarFila();
    return 0;
}

