#include <stdio.h>
#include <stdlib.h>

//estrutura da BST
typedef struct Celula * Apontador;
typedef struct Celula{
    Apontador Esq;
    Apontador Dir;
    int Chave;
}Celula;


typedef struct Item{
    int valor;
    int pos;
}Item;

void inicializaItem(Item *i, int valor, int pos){
    i->pos = pos;
    i->valor = valor;
}

void inicializaCelula(Apontador *Celula){
    *Celula = NULL;
}

//insere elemento na árvore
int insereValor(Apontador *C, Item *item){
    
    if(*C == NULL){
        *C = (Celula*)malloc(sizeof(Celula));
        (*C)->Chave = item->valor;
        inicializaCelula(&(*C)->Esq);
        inicializaCelula(&(*C)->Dir);
        return 1;
    }else{
        if(item->valor <= (*C)->Chave){
            return insereValor(&(*C)->Esq, item);
        }else{
            return insereValor(&(*C)->Dir, item);
        }

    }
}

//verifica se um dado valor inteiro está na árvore
int verificaArvore(int valor, Apontador c){
    if(c == NULL){
        return 0;
    }
    if(valor == c->Chave){
        return 1;
    }else{
        if(valor > c->Chave){
            return verificaArvore(valor, c->Dir);
        }else{
            return verificaArvore(valor, c->Esq);
        }
    }
}

//conta quantos nós não-nulos da árvore
int contaNos(Apontador c){
    if(c != NULL){
        return 1 + contaNos(c->Dir) + contaNos(c->Esq);
    }
    return 0;
}

//exibe o maior elemento da árvore
void exibeMaior(Apontador C){
    if(C == NULL){
        return;
    }
    if(C->Dir == NULL){
        printf("%d", C->Chave);
    }else{
        exibeMaior(C->Dir);
    }
    
}

//printa os elementos em pré-ordem (raiz, esquerda e direita)
void printPre(Apontador c){
    if(c == NULL){
        return;
    }
    printf("%d ", c->Chave);
    printPre(c->Esq);
    printPre(c->Dir);

}

//printa os elementos em ordem (esquerda, direita, raiz)
void printOrdem(Apontador c){
    if(c == NULL){
        return;
    }

    printOrdem(c->Esq);
    printf("%d ", c->Chave);
    printOrdem(c->Dir);
}

//printa em pós-ordem, (esquerda, direita, raiz)
void printPos(Apontador c){
    if(c == NULL){
        return;
    }
    printPos(c->Esq);
    printPos(c->Dir);
    printf("%d ", c->Chave);
}


void antecessor(Apontador q, Apontador *r){
    if((*r)->Dir != NULL){
        antecessor(q, &(*r)->Dir);
        return;
    }
    q->Chave = (*r)->Chave;
    q = *r;
    *r = (*r)->Esq;
    free(q);
}

//remove elemento da árvore
void remover(Apontador *c, int chave){

    if(*c == NULL){
        return;
    }

    if((*c)->Chave > chave){
        remover(&(*c)->Esq, chave);
        return;
    }else if((*c)->Chave < chave){
        remover(&(*c)->Dir, chave);
        return;
    }

    Apontador aux = *c;
    if((*c)->Dir == NULL){
        *c = (*c)->Esq;
        free(aux);
        return;

    }
    if((*c)->Esq == NULL){
        *c = (*c)->Dir;
        free(aux);
        return;
    }else{
        antecessor(*c, &(*c)->Esq);
    }
    
}

//cada elemento é removido em ordem logo após ser printado
void printRemoveOrdem(Apontador *c){

    if(*c == NULL){
        return;
    }
    printRemoveOrdem(&(*c)->Esq);

    printf("%d ", (*c)->Chave);

    remover(c, (*c)->Chave);

    printRemoveOrdem(c);
      
}

//retorna a altura da árvore
int altura(Apontador raiz){

    if(raiz == NULL){
        return -1;
    }

    int he = altura(raiz->Esq);
    int hd = altura(raiz->Dir);

    if(he > hd){
        return he+1;
    }else{
        return hd+1;
    }
}


int main(){

    Apontador raiz;
    inicializaCelula(&raiz);
    int op = -1;
    do{
        printf("Selecione a funcionalidade:\n");

        printf("1 - Inserir elementos na arvore;\n2 - Remover elementos da arvore;\n3 - Exibir os elementos em pre-ordem, ordem ou pos-ordem;\n4 - Encontrar o maior elemento na arvore;\n5 - Exibir a quantidade de nos (elementos) na arvore;\n6 - Exibir a altura da arvore;\n7 - Verificar se um valor esta na arvore\n0 - Sair.\n");
        scanf("%d", &op);

        int nElem;

        switch(op){
            case 1:
            
                //int nElem;
                printf("Inserindo elementos. Digite quantos elementos deseja inserir:\n");
                scanf("%d", &nElem);

                for(int i = 0; i < nElem; i++){
                    Item *item = (Item*)malloc(sizeof(Item));
                    int valor = 0;
                    printf("Digite o valor:\n");
                    scanf("%d", &valor);

                    //inicializaItem(&item, valor, i);
                    item->pos = i;
                    item->valor = valor;

                    insereValor(&raiz, item);
                }
                break;

            case 2:
                printf("Removendo elementos. Digite o elemento a ser removido:\n");
                
                int elemento = 0;

                scanf("%d", &elemento);

                remover(&raiz, elemento);
                break;

            case 3:
                printf("Exibindo elementos. Qual forma desejas?\n1 - Ordem\n2 - Pre-ordem\n3 - Pos-ordem\n");
                int opOrdem = 0;
                scanf("%d", &opOrdem);
                switch(opOrdem){
                    case 1:
                        printf("Percurso em ordem:\n");
                        printOrdem(raiz);
                        printf("\n");
                        break;
                    case 2:
                        printf("Percurso em pre-ordem:\n");
                        printPre(raiz);
                        printf("\n");
                        break;
                    case 3:
                        printf("Percurso em pos-ordem:\n");
                        printPos(raiz);
                        printf("\n");
                        break;
                    default:
                        printf("Entrada invalida.\n");
                        break;
                }
                break;

            case 4:
                printf("Maior elemento: ");
                exibeMaior(raiz);
                printf("\n");
                break;

            case 5:
                printf("Numero de elementos na arvore: %d\n", contaNos(raiz));
                break;

            case 6:
                printf("Altura da arvore: %d\n", altura(raiz));
                break;

            case 7:
                printf("Consultando valor na arvore. Digite o valor:\n");
                int val = 0;
                scanf("%d", &val);
                if(val){
                    printf("O valor esta sim na arvore.\n");
                }else{
                    printf("O valor nao esta na arvore.\n");
                }
                break;

            case 0:
                printf("Saindo...");
                return 0;
                break;
            default:
                printf("Entrava invalida.\n");
                break;
        }

    }while(op != 0);

    return 0;
}