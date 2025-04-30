// Punto 1 - Guia Colas
#include <iostream>
#include <stdio.h>

struct Nodo{
    int inf;
    Nodo * sig;
};

struct Cola{
    Nodo * head;
    Nodo * tail;
};

void inicializar(Cola &);
bool isEmpty(Cola);
void push(Cola &, int);
void pop(Cola &, int &);
void read(Cola, int &);

int main()
{
    Cola cola;
    return 0;
}

void inicializar(Cola &cola){
    cola.head = NULL;
    cola.tail = NULL;
}

bool isEmpty(const Cola &cola){
    return cola.head == NULL;
}

void push(Cola &cola, int num){
    Nodo * newNode = new Nodo;
    newNode->inf = num;
    newNode->sig = NULL;
    if(isEmpty(cola)){
        cola.head = newNode;
    }else{
        cola.tail->sig = newNode;
    }
    cola.tail = newNode;
}

void pop(Cola &cola, int &num){
    if(!isEmpty(cola)){
        Nodo * bor = cola.head;
        cola.head = cola.head->sig;
        num = bor->inf;
        delete bor;
        if(cola.head == NULL){
            c.tail = NULL;
        }
    }
}

void read(Cola c, int &num){
    if(!isEmpty(c)){
        num = c.head->inf;
    }
}