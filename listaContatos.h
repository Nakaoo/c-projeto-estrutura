typedef struct cliente{
    int id;
    char nome[40];
    char empresa[30];
    char departamento[30];
    char telefone[10];
    char email[30];
}cliente;

typedef struct elementos* Lista;

//funcao pra criar lista
Lista* criaLista();

//funcao para liberar lista
void liberarLista();

//funcao para verificar o tamanho da lista
int tamanhoLista(Lista *lis);

//funcao para verificar se a lista é vazia
int listaVazia(Lista *lis);

//funcao para coleta de dados
cliente coletaDados(cliente *cli);

//funcao para impressao de relatorio
void imprimeRelatorio(cliente *cli);

//funcao para inserir de forma ordenada
int insercaoOrdenada(Lista *lis, struct cliente cliente);

//funcao para remover um contato da lista
int remocaoLista(Lista *lis, int id);

//funcao para consultar um id na lista
int consultaId(Lista *lis, int id, cliente *cli);

//funcao para consultar um nome na lista
int consultaNome(Lista *lis, char *nome, cliente *cli);

//funcao para fazer a consulta total
int consultaTotal(Lista *lis, cliente *cli);

//funcao para edicao de contato
int edicaoContato(Lista *lis, int id, cliente *cli);

