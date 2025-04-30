#include <iostream>
#include <stdlib.h>
using namespace std;

struct node{
    int inf;
    struct node* next;
};

struct node* head = nullptr;
struct node* tail = nullptr;

void crearNodo(int); // Crea un nodo (First in First Out)
bool empty(); // Verifica si la lista esta vacia
void extract(); // Extrae el primer nodo y muestra por consola inf.
void imprimir(); // Imprime la inf. del primer nodo.
void liberar(); // Borra todos los nodos.

int main(){
    crearNodo(10);
    imprimir();
    crearNodo(20);
    crearNodo(30);
    liberar();
    extract();
    return(0);
}

bool empty(){
    return head == nullptr && tail == nullptr;
}

void crearNodo(int x){
    struct node* newNode = (node*)malloc(sizeof(struct node));
    if(newNode == nullptr){
        printf("Error al asignar el espacio de memoria.\n");
        exit(1);
    }
    newNode->inf = x;
    if(empty()){
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }else{
        tail->next = newNode;
        tail = newNode;
        newNode->next = NULL;
    }
}

void extract(){
    if(!empty()){
        struct node* ext = head;
        printf("Inf: %i \n", ext->inf);
        head = head->next;
        if(head == nullptr){
            tail = nullptr;
        }
        free(ext);
    }else{
        printf("No hay nodos para extraer.\n");
    }

}

void imprimir(){
    if(!empty()){
        printf("Informacion del HEAD: %i\n", head->inf);
    }else{
        printf("La lista esta vacia.\n");
    }
}

void liberar(){
    struct node* del;
    while(!empty()){
        del = head;
        head = head->next;
        free(del);
    }
    tail = nullptr;
}
