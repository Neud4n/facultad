#include <iostream>
#include <stdio.h>

struct NodoNumeros{
    int num;
    NodoNumeros * sig;
};

struct NodoOperadores{
    char operador;
    NodoOperadores * sig;
};

typedef NodoNumeros * Nn;
typedef NodoOperadores * No;

void init(Nn &);
void init (No &);
bool isEmpty(Nn);
bool isEmpty(Nn);
int cargarNumeros(Nn &);
void pushNumeros(Nn &, int);
void cargarOperadores(No &, int);
void pushOperadores(No &, char);
int operarNumeros(No, Nn);
void popNumero(Nn &, int &);
void popOperador(No &, char &);
bool salir();

int main()
{
    int cantNumeros;
    Nn headNumeros;
    No headOperadores;
    init(headNumeros);
    init(headOperadores);
    cantNumeros = cargarNumeros(headNumeros);
    cargarOperadores(headOperadores, cantNumeros);
    printf("El resultado es: %i\n", operarNumeros(headOperadores, headNumeros));
    return 0;
}

void init(Nn &head){
    head = NULL;
}

void init(No &head){
    head = NULL;
}

bool isEmpty(Nn head){
    return head == NULL;
}

bool isEmpty(No head){
    return head == NULL;
}

int cargarNumeros(Nn &head){
    int cant = 0;
    printf("=============================\n");
    printf("Carga de numeros para operar.\n");
    printf("=============================\n");
    int num;
    do{
        printf("Ingrese un numero\n");
        scanf("%i", &num);
        pushNumeros(head, num);
        cant++;
    }while(salir());
    return cant;
}

bool salir(){
    int resp;
    do{
        printf("Hay más datos para cargar?\n");
        scanf("%i", &resp);
        if(resp != 0 && resp != 1){
            printf("Respuesta invalida.\n");
        }
    }while(resp != 0 && resp != 1);
    return resp == 1;
}

void pushNumeros(Nn &head, int num){
    Nn newNode = new NodoNumeros;
    newNode->num = num;
    newNode->sig = head;
    head = newNode;
}

void cargarOperadores(No &headOperadores, int cantNumeros){
    printf("===============================\n");
    printf("Carga de operadores aritmeticos\n");
    printf("===============================\n");
    char op;
    for(int i = 0; i < cantNumeros; i++){
        printf("Muestro I en el FOR: %i\n", i);
        do{
            printf("Ingrese un operador + - * /\n");
            scanf(" %c", &op);
            if(op != '+' && op != '-' && op != '*' && op != '/'){
                printf("Ingresante un operador invalido.\n");
            }
        }while(op != '+' && op != '-' && op != '*' && op != '/');
        pushOperadores(headOperadores, op);
    }
}

void pushOperadores(No &head, char op){
    No newNode = new NodoOperadores;
    newNode->operador = op;
    newNode->sig = head;
    head = newNode;
}

void popNumero(Nn &headNumeros, int &num){
    if(!isEmpty(headNumeros)){
        Nn bor = headNumeros;
        headNumeros = headNumeros->sig;
        num = bor->num;
        delete bor;
    }
}

void popOperador(No &headOperador, char &op){
    if(!isEmpty(headOperador)){
        No bor = headOperador;
        headOperador = headOperador->sig;
        op = bor->operador;
        delete bor;
    }
}

// 10 30 50 100
// + - * 
// 0 + 10

int operarNumeros(No headOperadores, Nn headNumeros){
    Nn numeros = headNumeros;
    No operadores = headOperadores;
    int resultado, num;
    char op;
    popNumero(numeros, resultado);
    while(!isEmpty(numeros) && !isEmpty(operadores)){
        popNumero(numeros, num);
        popOperador(operadores, op);
        switch(op){
            case '+':
                resultado += num;
                break;
            case '-':
                resultado -= num;
                break;
            case '*':
                resultado *= num;
                break;
            case '/':
                if(num != 0){
                    resultado /= num;
                }
                break;
        }
    }
    return resultado;
}