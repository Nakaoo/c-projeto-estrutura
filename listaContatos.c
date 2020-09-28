#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaContatos.h"

struct elementos{
    struct cliente info;
    struct elementos *prox;
};
typedef struct elementos elementos;

//funcao pra criacao da lista
Lista* criaLista(){
    Lista *lis;
    lis = (Lista*) malloc(sizeof(Lista));
    if(lis != NULL) // se a lis for diferente de null, passará a apontar para um ponteiro
        *lis = NULL;
    return lis;
}


//funcao pra exibir o tamanho da lista
int tamanhoLista(Lista* lis){
    if(lis == NULL)
        return 0;
    int count = 0;
    elementos* no = *lis;
    while(no != NULL){ // enquanto no for diferente de nulo rodara
        count++; // cada vez que rodar o contador recebera mais um
        no = no->prox;
    }
    return count;
}

//funcao para verificar se a lista esta vazia
int listaVazia(Lista *lis){
    if(lis == NULL) // caso a lista seja nula será returnado 1 (vazia)
        return 1;
    if(*lis == NULL)
        return 1;
    return 0; // caso nao retorne null entao a lista nao esta vazia
}

//funcao para coleta de dados que recebe o endereço de cli
cliente coletaDados(cliente *cli){
    //dados serao coletados diretamente para o ponteiro cli
    printf("\nInsira o id do cliente: ");
    scanf("%d", &cli->id);
    printf("\nInsira o nome do cliente: ");
    fflush(stdin);
    gets(cli->nome);
    printf("\nInsira a empresa onde o cliente trabalha: ");
    fflush(stdin);
    gets(cli->empresa);
    printf("\nInsira o departamento do cliente: ");
    fflush(stdin);
    gets(cli->departamento);
    printf("\nInsira o telefone do cliente: ");
    fflush(stdin);
    gets(cli->telefone);
    printf("\nInsira o email do cliente: ");
    fflush(stdin);
    gets(cli->email);
    return *cli;
}


//funcao para imprimir o relatorio dos dados
void imprimeRelatorio(cliente *cli){
    //ponteiro cli apontando para id
    printf("\nID: %d", cli->id);
    printf("\nNome: %s", cli->nome);
    printf("\nEmpresa: %s", cli->empresa);
    printf("\nDepartamento: %s", cli->departamento);
    printf("\nEmail: %s", cli->email);
    printf("\nTelefone: %s\n", cli->telefone);
}

//funcao para o cliente ser inserido no inicio.
int insercaoOrdenada(Lista *lis, struct cliente cliente){
    if(lis == NULL) // verifica se a lista existe
        return 0;
    elementos *no = (elementos*) malloc(sizeof(elementos)); // aloca espaço
    if(no == NULL) // verifica se o no é nulo
        return 0;
    no->info = cliente; // copia os dados que quer inserir para o cliente
    //verifica se a lista é vazia para inserir no inicio
    if(listaVazia(lis)){
        no->prox = (*lis);
        *lis = no;
        return 1;
    }
    //caso contrario vai procurar onde inserir
    else{
        elementos *anterior, *atual = *lis; // dois ponteiros auxiliares
        while(atual != NULL && atual->info.id < cliente.id){ // laço rodara ate o elemento da lista for menor do que da insercao
            anterior = atual; // anterior vale atual
            atual = atual->prox; // atual vai valer o proximo
        }
        if(atual == *lis){ // insercao inicio
            no->prox = (*lis);
            *lis = no;
        }else{ // insercao fora do inicio
            no->prox = anterior->prox;
            anterior->prox = no;
        }
        return 1;
    }
}

//funcao para remocao da lista por ID
int remocaoLista(Lista* lis, int id){
    if(lis == NULL)
        return 0;
    elementos *anterior, *no = *lis; // ponteiro auxiliar
    while(no != NULL && no->info.id != id){ // enquanto os dados onde o no aponta forem diferente do id, o laço rodará
        anterior = no; // anterior recebe o no atual
        no = no->prox; // apontara para o prox
    }
    if(no == NULL) // nao encontrado
        return 0;
    if(no == *lis) // remocao do primeiro
        *lis = no->prox;
    else // remocao do ultimo
        anterior->prox = no->prox;
    free(no); // apaga o no
    return 1;
}

//funcao para realizar a consulta na lista
int consultaId(Lista *lis, int id, cliente *cli){
    if(lis == NULL)
        return 0;
    elementos *no = *lis;
    while(no != NULL && no->info.id != id){ // laço rodara ate o no atual ser diferente do id
        no = no->prox; // vai sempre para o proximo
    }
    if(no == NULL){ // nao encontrado
        return 0;
    }else{ //encontrado
        *cli = no->info; // retorna os dados da onde o no aponta para o endereço do cli
        return 1;
    }
}

//funcao para consulta de nome
int consultaNome(Lista *lis, char *nome, cliente *cli){
    if(lis == NULL)
        return 0;
    elementos *no = *lis;
    while(no != NULL){ // roda um laço ate no ser diferente de nulo
        if(strcmp(nome, no->info.nome) == 0){ // strcmp vai comparar as duas strings para descobrir que for verdadeiro
            *cli = no->info; // retorna os dados de onde o no aponta para o endereço de cli
            return 1;
        }
        no = no->prox;
    }
    if(no == NULL)
        return 0;
}

//funcao para consultar tudo
int consultaTotal(Lista *lis, cliente *cli){
    if(lis == NULL)
        return 0;
    elementos *no = *lis;
    while(no != NULL){ // enquanto o no for diferente de nulo exibira as informacoe
        printf("\nID: %d", no->info.id);
        printf("\nEmpresa: %s", no->info.empresa);
        printf("\nDepartamento: %s", no->info.departamento);
        printf("\nEmail: %s", no->info.email);
        printf("\nNome: %s", no->info.nome);
        printf("\nTelefone: %s\n", no->info.telefone);
        no = no->prox; // no sempre va apontar para o proximo, pegando assim as informacoes posteriores
    }
}

//funcao para editar contato
int edicaoContato(Lista *lis, int id, cliente *cli){
    if(lis == NULL)
        return 0;
    elementos *no = *lis;
    while(no != NULL && no->info.id != id){ // enquanto o id for diferente do apontado o no rodara
        no = no->prox; // aponta para o prox
    }
    if(no == NULL){
        return 0;
    }else{ //achou e substitui os dados
        *cli = no->info; // o no ta apontando para as informacoes atuais
        //dados atuais serao substituidos
        printf("\nInsira o id do cliente: ");
        scanf("%d", &no->info.id);
        printf("\nInsira o nome do cliente: ");
        fflush(stdin);
        gets(no->info.nome);
        printf("\nInsira a empresa onde o cliente trabalha: ");
        fflush(stdin);
        gets(no->info.empresa);
        printf("\nInsira o departamento do cliente: ");
        fflush(stdin);
        gets(no->info.departamento);
        printf("\nInsira o telefone do cliente: ");
        fflush(stdin);
        gets(no->info.telefone);
        printf("\nInsira o email do cliente: ");
        fflush(stdin);
        gets(no->info.email);
        return 1;
    }
}

//funcao para liberacao da lista apos o uso da mesma
void liberarLista(Lista* lis){
    if(lis != NULL){
        elementos* no;
        while((*lis) != NULL){ // rodara o while ate a lis for diferente de null, e em cada execucao sera liberado o no
            no = *lis;
            *lis = (*lis)->prox;
            free(no);
        }
        free(lis);
    }
}
