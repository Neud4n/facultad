/*
Se pide hacer un programa que ingrese por teclado los datos de las personas que se
inscribieron para el plan de vacunación. Por cada persona inscripta se ingresa:
Número de documento
Apellido y nombre
Código postal de la localidad donde reside
Se pide generar el archivo “RegistroVacunas.dat” con un registro por persona ordenado por
número de documento, verificar no guardar registros repetidos en el archivo. Utilizar un
árbol binario como estructura auxiliar
*/
#include <iostream>
#include <stdio.h>

struct Persona{
    int dni;
    char nombre[25];
    char apellido[25];
    int codPostal;
};

struct NodoArbol{
    Persona dato;
    NodoArbol *izq;
    NodoArbol *der;
};

typedef NodoArbol * PuntA;

void cargarDatosPersona(Persona &);
void mostrarDatosPersona(Persona);
void crearArchivo();
void insertarNodo(PuntA &, Persona);
bool validarExistencia(PuntA, int);
bool salir();
void imprimirArchivo();
void cargarOrdenado(PuntA, FILE * &);

int main(){
    crearArchivo();
    imprimirArchivo();
    return 0;
}

void insertarNodo(PuntA &raiz, Persona dato){
    if(raiz==NULL){
        PuntA nuevo = new NodoArbol;
        nuevo->dato = dato;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        raiz = nuevo;
    }else{
        if(raiz->dato.dni > dato.dni){
            insertarNodo(raiz->izq, dato);
        }else if (raiz->dato.dni < dato.dni){
            insertarNodo(raiz->der, dato);
        }
    }
}

bool validarExistencia(PuntA raiz, int dni){
    while(raiz && raiz->dato.dni != dni){
        if(raiz->dato.dni > dni){
            raiz = raiz->izq;
        }else{
            raiz = raiz->der;
        }
    }
    if(raiz!=NULL){
        return true;
    }
    return false;
}

void cargarDatosPersona(Persona &persona){
    printf("Ingrese el DNI de la persona\n");
    scanf("%i", &persona.dni);
    printf("Ingrese el nombre de la persona\n");
    scanf("%s", persona.nombre);
    printf("Ingrese el apellido de la persona\n");
    scanf("%s", persona.apellido);
    printf("Ingrese el codigo postal de la persona\n");
    scanf("%i", &persona.codPostal);
}

void crearArchivo(){
    FILE * fptr = fopen("RegistroVacunas.dat", "wb");
    if(fptr == NULL){
        printf("No se pudo generar el archivo\n");
        exit(EXIT_FAILURE);
    }
    Persona persona;
    PuntA aux = NULL;
    while(salir()){
        bool existe;
        do{
            cargarDatosPersona(persona);
            existe = validarExistencia(aux, persona.dni);
            if(existe){
                printf("La persona ingresada ya existe.\n");
            }
        }while(existe);
        insertarNodo(aux, persona);
    }
    cargarOrdenado(aux, fptr);
    fclose(fptr);
}

void cargarOrdenado(PuntA raiz, FILE * &file){
    if(raiz!=NULL){
        cargarOrdenado(raiz->izq, file);
        Persona persona = raiz->dato;
        fwrite(&persona, sizeof(Persona), 1, file);
        cargarOrdenado(raiz->der, file);
    }
}

bool salir(){
    int resp;
    do{
        printf("Hay datos para cargar?\n");
        scanf("%i", &resp);
        if(resp!=1 && resp!=0){
            printf("ERROR: Ingresó una respuesta invalida\n");
        }
    }while(resp!=1 && resp!=0);
    return resp == 1;
}

void mostrarDatosPersona(Persona p){
    printf("DNI: %i\n", p.dni);
    printf("Nombre: %s\n", p.nombre);
    printf("Apellido: %s\n", p.apellido);
    printf("Cod. Postal: %i\n", p.codPostal);
}

void imprimirArchivo(){
    FILE * fptr = fopen("RegistroVacunas.dat", "rb");
    if(!fptr){
        printf("No se pudo abrir el archivo en modo lectura.\n");
        exit(EXIT_FAILURE);
    }
    Persona aux;
    while(fread(&aux, sizeof(Persona), 1, fptr)){
        mostrarDatosPersona(aux);
    }
    fclose(fptr);
}