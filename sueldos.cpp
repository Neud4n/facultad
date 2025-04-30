// Ejercicio 7 y 8
#include <iostream>
#include <stdio.h>
using namespace std;

#define CANT_E 5
#define CANT_H 6
struct Empleado{
    int leg;
    int sueldo;
};

struct HoraExtra{
    int leg;
    int horasExtra;
};

bool seguir();
void setDatosPaga(int &, int &);
void newFileEmpleados(Empleado []);
void newFileSueldos(); 
void newFileHorasExtras(HoraExtra []);
void newFilePagaHorasExtra();
void mostrarPagaHorasExtra();

int main(){
    Empleado e[CANT_E] = {
        {1, 50000},
        {2, 40000},
        {3, 25000},
        {4, 42500},
        {5, 30000}
    };
    HoraExtra h[CANT_H] = {
        {1, 5},
        {2, 0},
        {3, 2},
        {4, 1},
        {5, 8},
        {3, 2}
    };
    newFileEmpleados(e);
    newFileSueldos();
    newFileHorasExtras(h);
    newFilePagaHorasExtra();
    mostrarPagaHorasExtra();
}

void newFileEmpleados(Empleado vec[]){
    FILE * fptr = fopen("Empleados.dat", "wb");
    if(fptr == nullptr){
        printf("No se pudo crear el archivo\n");
        exit(1);
    }
    fwrite(vec,sizeof(Empleado), CANT_E, fptr);
    fclose(fptr);
}

void newFileSueldos(){
    Empleado e;
    FILE * fpe = fopen("Empleados.dat", "rb");
    FILE * fps = fopen("SueldoBajo.dat", "wb");
    while(fread(&e, sizeof(Empleado), 1, fpe) == 1){
        if(e.sueldo < 40000){
            fwrite(&e, sizeof(Empleado), 1, fps);
        }
    }
    fclose(fpe);
    fclose(fps);
}

void newFileHorasExtras(HoraExtra vec[]){
    FILE * fptr = fopen("HorasExtras.dat", "wb");
    fwrite(vec, sizeof(HoraExtra), CANT_H, fptr);
    fclose(fptr);
}

bool seguir(){
    int resp;
    do{
        printf("Hay datos para cargar?\n");
        scanf("%i", &resp);
    }while(resp != 1 && resp != 0);
    return(resp == 1);
}

void setDatosPaga(int &leg, int &valor){
    printf("Ingrese el número de legajo\n");
    scanf("%i", &leg);
    printf("Ingrese el valor de la hora\n");
    scanf("%i", &valor);
}

void newFilePagaHorasExtra(){
    HoraExtra h;
    FILE * fptr = fopen("HorasExtras.dat", "rb");
    if( fptr == nullptr){
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }
    FILE * newFile = fopen("PagaHsExtras.dat", "wb");
    if( newFile == nullptr){
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }
    int numLeg, valorHora, paga;
    while(seguir()){
        setDatosPaga(numLeg, valorHora);
        paga = 0;
        while(fread(&h, sizeof(HoraExtra), 1, fptr) == 1){
            if(h.leg == numLeg){
                paga+= (valorHora * h.horasExtra);
            }
        }
        if(paga != 0){
            h.horasExtra = paga;
            h.leg = numLeg;
            fwrite(&h, sizeof(HoraExtra), 1, newFile);
        }else{
            printf("El empleado %i no realizo horas extra.\n", numLeg);
        }
        rewind(fptr);
    }
    fclose(newFile);
    fclose(fptr);
}

void mostrarPagaHorasExtra(){
    HoraExtra h;
    FILE * fptr = fopen("PagaHsExtras.dat", "rb");
    if( fptr == nullptr){
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }
    while(fread(&h, sizeof(HoraExtra), 1, fptr) == 1){
        printf("Al empleado %i hay que pagarle %i pesos de horas extra.\n", h.leg, h.horasExtra);
    }
    fclose(fptr);
}