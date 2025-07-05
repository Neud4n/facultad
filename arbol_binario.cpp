#include <iostream>

struct NodoArbol{
    int dato;
    NodoArbol * izq;
    NodoArbol * der;
};

typedef NodoArbol * PuntA;

struct NodoPila{
    PuntA dato;
    NodoPila * sig;
};

typedef NodoPila * PuntP;

void push(PuntP &, PuntA);
void pop(PuntP &, PuntA &);
void pop(PuntP &);
void insertarNodo(PuntA &, int);
void insertarRecursivo(PuntA &, int);
void preOrder(PuntA);
void inOrder(PuntA);
void postOrder(PuntA);
void inOrderIterativo(PuntA);
void preOrderIterativo(PuntA);
void postOrderIterativo(PuntA);

int main(){
    PuntA root = NULL;
    insertarNodo(root, 50);
    insertarNodo(root, 20);
    insertarNodo(root, 40);
    insertarNodo(root, 15);
    insertarNodo(root, 45);
    insertarNodo(root, 5);
    insertarNodo(root, 38);
    insertarNodo(root, 18);
    printf("PreOrder Recursivo\n");
    preOrder(root);
    printf("\nInOrder Recursivo\n");
    inOrder(root);
    printf("\nPostOrder Recursivo\n");
    postOrder(root);
    printf("\nPreOrder Iterativo\n");
    preOrderIterativo(root);
    printf("\nInOrder Iterativo\n");
    inOrderIterativo(root);
    printf("\npostOrder Iterativo\n");
    postOrderIterativo(root);
    return 0;
}

void push(PuntP &tope, PuntA nodo){
    PuntP nuevo = new NodoPila;
    nuevo->sig = tope;
    nuevo->dato = nodo;
    tope = nuevo;
}

void pop(PuntP &tope, PuntA &nodo){
    if(tope != NULL){
        PuntP bor = tope;
        tope = tope->sig;
        nodo = bor->dato;
        delete bor;
    }
}

void pop(PuntP &tope){
    if(tope != NULL){
        PuntP bor = tope;
        tope = tope->sig;
        delete bor;
    }
}

PuntA peek(PuntP tope){
    if(tope != NULL){
        return tope->dato;
    }
    return NULL;
}

void insertarNodo(PuntA &raiz, int num){
    PuntA nuevo = new NodoArbol;
    nuevo->dato = num;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    if(!raiz){
        raiz = nuevo;
    }else{
        PuntA ant = NULL;
        PuntA r = raiz;
        while(r){
            if(num < r->dato){
                ant = r;
                r = r->izq;
            }else{
                ant = r;
                r = r->der;
            }
        }
        if(num < ant->dato){
            ant->izq = nuevo;
        }else{
            ant->der = nuevo;
        }
    }
}

void insertarRecursivo(PuntA &raiz, int num){
    if(raiz == NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->dato = num;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato > num){
            insertarRecursivo(raiz->izq, num);
        }else{
            insertarRecursivo(raiz->der, num);
        }
    }
}

void preOrder(PuntA raiz){
    if(raiz == NULL){
        return;
    }else{
        printf("%i ",raiz->dato);
        preOrder(raiz->izq);
        preOrder(raiz->der);
    }
}

void inOrder(PuntA raiz){
    if(raiz == NULL){
        return;
    }else{
        inOrder(raiz->izq);
        printf("%i ",raiz->dato);
        inOrder(raiz->der);
    }
}

void postOrder(PuntA raiz){
    if(raiz == NULL){
        return;
    }else{
        postOrder(raiz->izq);
        postOrder(raiz->der);
        printf("%i ",raiz->dato);
    }
}

void preOrderIterativo(PuntA raiz){ // Raiz, Izq, Der
    PuntP tope = NULL;
    while(raiz != NULL || tope != NULL){
        if(raiz != NULL){
            push(tope, raiz);
            printf("%i ", raiz->dato);
            raiz = raiz->izq;
        }else{
            pop(tope, raiz);
            raiz = raiz->der;
        }
    }
}

void inOrderIterativo(PuntA raiz){ // Izq, Raiz, Der
    PuntP tope = NULL;
    while(raiz != NULL || tope != NULL){
        if(raiz != NULL){
            push(tope, raiz);
            raiz = raiz->izq;
        }else{
            pop(tope, raiz);
            printf("%i ", raiz->dato);
            raiz = raiz->der;
        }
    }
}

void postOrderIterativo(PuntA raiz){ // Izq, Der, Raiz
    PuntP tope = NULL;
    PuntA ultimoVisitado = NULL;
    PuntA temp = NULL;
    while(raiz != NULL || tope != NULL){
        if(raiz != NULL){
            push(tope, raiz);
            raiz = raiz->izq;
        }else{
            temp = tope->dato; 
            if(temp->der == NULL || temp->der == ultimoVisitado){
                printf("%i ", temp->dato);
                ultimoVisitado = temp;
                pop(tope);
            }else{
                raiz = temp->der;
            }
        }
    }
}