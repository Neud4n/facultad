#include <iostream>
#include <stdio.h>

struct Venta{
    int cod;
    float montoTotal;
};

struct Nodo {
    Venta inf;
    Nodo * sig;
};

typedef Nodo * PuntP;

void init(PuntP &);
bool isEmpty(PuntP);
bool salir();
void cargarVentas(PuntP &);
void cargarDatosVentas(Venta &);
void pushVenta(PuntP &, Venta);
void popVenta(PuntP &, Venta &);
void sumarSemestres(PuntP &, PuntP &, PuntP &);
void mostrarVentas(PuntP &);

int main()
{
    PuntP primerSemestre;
    PuntP segundoSemestre;
    PuntP anual;
    init(primerSemestre);
    init(segundoSemestre);
    init(anual);
    printf("===============\n");
    printf("Primer Semestre\n");
    printf("===============\n");
    cargarVentas(primerSemestre);
    printf("================\n");
    printf("Segundo Semestre\n");
    printf("================\n");
    cargarVentas(segundoSemestre);
    sumarSemestres(primerSemestre, segundoSemestre, anual);
    printf("=============\n");
    printf("Informe Anual\n");
    printf("=============\n");
    mostrarVentas(anual);
    return 0;
}

void init(PuntP &head){
    head = NULL;
}

bool isEmpty(PuntP head){
    return head == NULL;
}

void cargarVentas(PuntP &head){
    Venta aux;
    do{
        cargarDatosVentas(aux);
        pushVenta(head, aux);
    }while(salir());
}

void cargarDatosVentas(Venta &venta){
    printf("Ingrese el codigo del vendedor\n");
    scanf("%i", &venta.cod);
    printf("Ingrese el monto total vendido\n");
    scanf("%f", &venta.montoTotal);
}

void pushVenta(PuntP &head, Venta venta){
    PuntP newNode = new Nodo;
    newNode->inf = venta;
    newNode->sig = head;
    head = newNode;
}

void popVenta(PuntP &head, Venta &venta){
    if(!isEmpty(head)){
        PuntP bor = head;
        venta = bor->inf;
        head = head->sig;
        delete bor;
    }
}

bool salir(){
    int resp;
    do{
        printf("Hay mas datos? 1 [Si] - 0 [No]\n");
        scanf("%i", &resp);
        if(resp != 1 && resp != 0){
            printf("Ingresaste una opcion invalida, bobinola.\n");
        }
    }while(resp != 1 && resp != 0);
    return resp == 1;
}

void sumarSemestres(PuntP &primerSem, PuntP &segundoSem, PuntP &anual){
    Venta aux, aux2;
    while(!isEmpty(primerSem) && !isEmpty(segundoSem)){
        if(primerSem->inf.cod > segundoSem->inf.cod){
            popVenta(primerSem, aux);
            pushVenta(anual, aux);
        } else if(segundoSem->inf.cod > primerSem->inf.cod){
            popVenta(segundoSem, aux);
            pushVenta(anual, aux);
        } else {
            popVenta(primerSem, aux);
            popVenta(segundoSem, aux2);
            aux.montoTotal += aux2.montoTotal;
            pushVenta(anual,aux);
        }
    }

    while(!isEmpty(primerSem)){
        popVenta(primerSem, aux);
        pushVenta(anual, aux);
    }

    while(!isEmpty(segundoSem)){
        popVenta(segundoSem, aux);
        pushVenta(anual, aux);
    }
}

void mostrarVentas(PuntP &head){
    PuntP exp = head;
    while(!isEmpty(exp)){
        printf("Cod: %i - Monto: %0.2f\n", exp->inf.cod, exp->inf.montoTotal);
        exp = exp->sig;
    }
}