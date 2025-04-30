// Shit like this should be on the graveyard
#include <iostream>
#include <stdlib.h>
using namespace std;

struct nodo{
    int inf;
    nodo *sig;
};

void crearNodo(int); // LIFO (Last in First Out)
void imprimirLista();
void borrarNodo();
void borrarNodos();
int cantNodos();

struct nodo *raiz = NULL;

int main()
{
    crearNodo(5);
    crearNodo(10);
    crearNodo(15);
    printf("La cantidad de nodos actual es de: %i\n", cantNodos());
    imprimirLista();
    borrarNodo();
    printf("Impresión de la lista POST borrado de un nodo\n");
    imprimirLista();
    printf("Impresión de la lista POST borrado los nodos restantes\n");
    borrarNodos();
    imprimirLista();
    return(0);
}

void crearNodo(int num){
    struct nodo *nuevo;
    nuevo = (nodo*)malloc(sizeof(struct nodo));
    nuevo->inf = num;
    if(raiz == NULL){
        raiz = nuevo;
        nuevo->sig = NULL;
    }else{
        nuevo->sig = raiz;
        raiz = nuevo;
    }
}

void imprimirLista(){
    struct nodo *imp = raiz;
    int nodo = 1;
    while(imp != NULL){
        printf("El nodo %i tiene la información: %i\n", nodo, imp->inf);
        nodo++;
        imp = imp->sig;
    }
    if(raiz == NULL){
        printf("La lista está vacia.\n");
    }
}

void borrarNodo(){
    if(raiz !=NULL){
        struct nodo *del = raiz;
        raiz = del->sig;
        free(del);
    }else{
        printf("La lista está vacia.\n");
    }
}

void borrarNodos(){
    while(raiz != NULL){
        struct nodo *del = raiz;
        raiz = del->sig;
        free(del);
    }
}

int cantNodos(){
    int cant = 0;
    struct nodo *nodo = raiz;
    while(nodo != NULL){
        cant++;
        nodo = nodo->sig;
    }
    return(cant);
}
