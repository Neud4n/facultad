// Guía de ejercicio Pilas
#include <iostream>
#include <stdio.h>

struct Legajo{
    int num;
    char sexo;
};

struct Nodo{
    Legajo inf;
    Nodo * sig;
};

typedef Nodo * PuntP;

void init(PuntP &); // Punto 1
bool isEmpty(PuntP); // Punto 1
void crearPilaLegajos(PuntP &); // Punto 2a
void cargarDatosLegajo(Legajo &); // Punto 2a
void pushLegajo(PuntP &, Legajo); // Punto 1 // Punto 2a
void popLegajo(PuntP &, Legajo &); // Punto 1
bool salir();
int getCantVarones(PuntP); // Punto 2b
int getPrimerLegMujer(PuntP); // Punto 2c
void separarLegajosPorGenero(PuntP, PuntP &, PuntP &); // Punto 2d
void intercalarPorGenero(PuntP, PuntP &); // Punto 2e
void ordenarPorNumeroLegajo(PuntP &); // Punto 2f
void invertirPila(PuntP &); // Punto 2f
void menu(); // Punto 2g
void mostrarMenu(); // Punto 2g
void verLegajo(PuntP); 
void verLegajo(PuntP, Legajo &); // Punto 1

int main()
{ 
    menu();
    return(0);
}

void init(PuntP &head){
    head = NULL;
}

bool isEmpty(PuntP head){
    return head == NULL;
}

void crearPilaLegajos(PuntP &head){
    Legajo aux;
    do{
        cargarDatosLegajo(aux);
        pushLegajo(head, aux);
    }while(salir());
}

bool salir(){
    int resp;
    do{
        printf("Hay mas datos para cargar? Si [1] | No [0]\n");
        scanf("%i", &resp);
        if(resp != 1 && resp != 0){
            printf("ERROR: No se ingreso un dato valido.\n");
        }
    }while(resp != 1 && resp != 0);
    return resp == 1;
}

void cargarDatosLegajo(Legajo &leg){
    printf("Cual es el número de legajo?\n");
    scanf("%i", &leg.num);
    do{
        printf("Sexo?\n");
        scanf("%s", &leg.sexo);    
        if(leg.sexo != 'M' && leg.sexo != 'F'){
            printf("ERROR: Debe ingresar M o F\n");
        }
    }while(leg.sexo != 'M' && leg.sexo != 'F');
}

void pushLegajo(PuntP &head, Legajo leg){
    Nodo * newNode = new Nodo;
    newNode->inf = leg;
    newNode->sig = head;
    head = newNode;
}

int getCantVarones(PuntP head){
    int cant = 0;
    Nodo * exp = head;
    while(!isEmpty(exp)){
        if(exp->inf.sexo == 'M'){
            cant++;
        }
        exp = exp->sig;
    }
    return cant;
}

int getPrimerLegMujer(PuntP head){
    Nodo * exp = head;
    while(!isEmpty(exp) && exp->inf.sexo != 'F'){
        if(exp->inf.sexo != 'F'){
            exp = exp->sig;
        }
    }
    if(isEmpty(exp)){
        return 0;
    }else{
        return exp->inf.num;
    }
}

void separarLegajosPorGenero(PuntP head, PuntP &headVarones, PuntP &headMujeres){
    PuntP aux = head; // Pila Original
    Legajo auxLeg;
    while(!isEmpty(aux)){
        verLegajo(aux, auxLeg);
        if(auxLeg.sexo == 'M'){
            pushLegajo(headVarones, auxLeg);
        }else{
            pushLegajo(headMujeres, auxLeg);
        }
        aux = aux->sig;
    }
}

void popLegajo(PuntP &head, Legajo &leg){
    if(!isEmpty(head)){
        PuntP bor = head;
        head = head->sig;
        leg = bor->inf;
        delete bor;
    }
}

void intercalarPorGenero(PuntP head, PuntP &headIntercalado){
    PuntP headAux = head;
    PuntP headV, headF;
    Legajo aux;
    separarLegajosPorGenero(headAux, headV, headF);

    while(!isEmpty(headV) && !isEmpty(headF)){
        popLegajo(headV, aux);
        pushLegajo(headIntercalado, aux);
        popLegajo(headF, aux);
        pushLegajo(headIntercalado, aux);
    }

    while(!isEmpty(headV)){
        popLegajo(headV, aux);
        pushLegajo(headIntercalado, aux);
    }

    while(!isEmpty(headV)){
        popLegajo(headF, aux);
        pushLegajo(headIntercalado, aux);
    }
}

// 100 200 300 400 500 --> headA
// 150 250 350 450 550 --> headB
// 550 500 450 400 350 300 250 200 150 100 --> headC resultante.
// Estoy devolviendo la pila de mayor a menor. Capaz conviene invertirla.
void ordenarPorNumeroLegajo(PuntP &headC){
    PuntP headA, headB;
    Legajo aux;
    init(headA);
    init(headB);
    printf("PILA DE LEGAJOS A\n");
    crearPilaLegajos(headA);
    printf("PILA DE LEGAJOS B\n");
    crearPilaLegajos(headB);
    while(!isEmpty(headA) && !isEmpty(headB)){
        if(headA->inf.num > headB->inf.num){
            popLegajo(headA,aux);
            pushLegajo(headC, aux);
        }else if(headB->inf.num > headA->inf.num){
            popLegajo(headB, aux);
            pushLegajo(headC, aux);
        }else{
            // Si el numero de legajo es igual, clavamos ambos valores.
            popLegajo(headA,aux);
            pushLegajo(headC, aux);
            popLegajo(headB, aux);
            pushLegajo(headC, aux);
        }
    }
    // Colocamos los restantes.
    while(!isEmpty(headA)){
        popLegajo(headA,aux);
        pushLegajo(headC, aux);
    }
    while(!isEmpty(headB)){
        popLegajo(headB, aux);
        pushLegajo(headC, aux);
    }

    // Invierto la pila
    invertirPila(headC);
}

void invertirPila(PuntP &head) {
    PuntP nuevaPila;
    init(nuevaPila);
    Legajo aux;
    while (!isEmpty(head)) {
        popLegajo(head, aux);
        pushLegajo(nuevaPila, aux);
    }
    head = nuevaPila;
}

void menu(){
    int opcion;
    int leg;
    PuntP head;
    PuntP headVarones;
    PuntP headMujeres;
    PuntP intercalados;
    PuntP ordenado;
    init(head);
    init(headVarones);
    init(headMujeres);
    init(intercalados);
    init(ordenado);
    do{
        mostrarMenu();
        scanf("%i", &opcion);
        switch(opcion){
            case 1:
                crearPilaLegajos(head);
                break;
            case 2:
                printf("La cantida de varones es: %i\n", getCantVarones(head));
                break;
            case 3:
                leg = getPrimerLegMujer(head);
                if(leg != 0){
                    printf("El numero de legajo de la primera mujer es: %i\n", leg);
                }else{
                    printf("No hay ninguna mujer en la pila de legajos.\n");
                }
                break;
            case 4:
                separarLegajosPorGenero(head, headVarones, headMujeres);
                printf("Legajo de Hombres\n");
                verLegajo(headVarones);
                printf("Legajo de Mujeres\n");
                verLegajo(headMujeres);
                break;
            case 5:
                ordenarPorNumeroLegajo(ordenado);
                printf("Legajo ordenado\n");
                verLegajo(ordenado);
                break;
            default:
                printf("Ingrese una opción valida");
                break;
        }
    }while(opcion != 0);
}

void mostrarMenu(){
    printf("Opcion 1 - Crear legajo\n");
    printf("Opcion 2 - Cantidad de varones\n");
    printf("Opcion 3 - Primer legajo de una mujer\n");
    printf("Opcion 4 - Crear legajo de hombres y mujeres\n");
    printf("Opcion 5 - Ordenar legajo de mayor a menor\n");
}

void verLegajo(PuntP head){ // Ya se que el TP pide que devuelva un legajo pero me dio paja.
    PuntP read = head;
    while(!isEmpty(read)){
        printf("Nro Legajo: %i - Sexo: %c\n", read->inf.num, read->inf.sexo);
        read = read->sig;
    }
}

void verLegajo(PuntP head, Legajo &leg){
    if(!isEmpty(head)){
        PuntP read = head;
        leg = read->inf;
    }
}