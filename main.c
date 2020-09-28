#include <stdio.h>
#include <stdlib.h>
#include "listaContatos.h"
#include <string.h>

int main()
{
    Lista *lis;
    lis = criaLista();
    FILE* listaContatosR = fopen("listaContatos.bin", "a+");
    int opt, verificar, id, i, resposta;
    char nome[30];
    struct cliente cli;
    if(listaContatosR != NULL)
        while(!feof(listaContatosR)){
            fread(&cli, sizeof(cliente), 1, listaContatosR);
            insercaoOrdenada(lis, cli);
        }
    do{
        printf("---------------------------MENU---------------------------\n");
        printf("1- Insercao de novo contato\n");
        printf("2- Geracao de relatorio total\n");
        printf("3- Geracao de relatorio por ID\n");
        printf("4- Geracao de relatorio por nome\n");
        printf("5- Remocao de contato - por identificador\n");
        printf("6- Edicao de contato por ID\n");
        printf("7- Tamanho da lista\n");
        printf("8- Encerrar o programa e salvar\n");
        printf("Opcao: ");
        scanf("%d", &opt);
        switch(opt){
            case 1:
                cli = coletaDados(&cli);
                verificar = insercaoOrdenada(lis, cli);
                fwrite(&cli, sizeof(cliente), 1, listaContatosR);
                    if(verificar)
                        printf("Cliente inserido com sucesso!\n");
                    else
                        printf("Erro ao inserir!\n");
                break;
            case 2:
                if(listaVazia(lis)){
                    printf("Sua lista de contatos nao tem contatos para se consultar\n");
                    break;
                }
                consultaTotal(lis, &cli);
                break;
            case 3:
                if(listaVazia(lis)){
                    printf("Sua lista de contatos nao tem contatos para se consultar\n");
                    break;
                }
                printf("Insira o id que deseja verificar: ");
                scanf("%d", &id);
                verificar = consultaId(lis, id, &cli);
                if(verificar)
                    imprimeRelatorio(&cli);
                else
                    printf("\nCliente nao encontrado\n");
                break;
            case 4:
                if(listaVazia(lis)){
                    printf("Sua lista de contatos nao tem contatos para se consultar\n");
                }
                printf("Insira o nome que deseja verificar: ");
                fflush(stdin);
                gets(nome);
                verificar = consultaNome(lis, nome, &cli);
                if(verificar)
                    imprimeRelatorio(&cli);
                else
                    printf("Cliente nao encontrado");
                break;
            case 5:
                if(listaVazia(lis)){
                    printf("Sua lista de contatos nao tem contatos para se consultar\n");
                    break;
                }
                printf("Informe um ID para ser removido: ");
                scanf("%d", &id);
                verificar = remocaoLista(lis, id);
                printf("Deseja realmente editar? (1/2): ");
                scanf("%d", &resposta);
                if(resposta == 1){
                    if(verificar)
                        printf("Removido!\n");
                    else
                        printf("Nao existe\n");
                }
                break;
            case 6:
                if(listaVazia(lis)){
                    printf("Sua lista de contatos nao tem contatos para se consultar\n");
                    break;
                }
                printf("Insira o ID que deseja editar: ");
                scanf("%d", &id);
                imprimeRelatorio(&cli);
                printf("Deseja realmente editar? (1/2): ");
                scanf("%d", &resposta);
                if(resposta == 1){
                    verificar = edicaoContato(lis, id, &cli);
                    if(verificar)
                    printf("Cliente editado com sucesso\n");
                    else
                        printf("Cliente nao encontrado");
                }
                break;
            case 7:
                if(listaVazia(lis)){
                    printf("Sua lista de contatos nao tem contatos para se consultar\n");
                    break;
                }
                printf("Tamanho da lista de contatos: %d\n", tamanhoLista(lis));
                break;
            default:
                if(opt > 0 && opt != 8)
                    printf("Opcao inexistente\n");
        }
    }while(opt != 8);
    fclose(listaContatosR);
    liberarLista(lis);
}
