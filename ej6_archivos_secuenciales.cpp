// Ejercicio 6 -> Archivos secuenciales
#include <iostream>
#include <stdio.h>
using namespace std;

struct Examen{
    char nombre[50];
    int codMat;
    int nota;
    int codAlum;
};

void newFileExamenes(Examen []);
void setDatosAlum(int &, int &);
void informeAlum();
bool seguir();

int main(){
    Examen e[10] = {
        {"Pepe", 100, 8, 1500},
        {"Juan", 100, 3, 2500},
        {"Lautaro", 100, 9, 1200},
        {"Martina", 200, 7, 1800},
        {"Sofía", 200, 5, 2200},
        {"Carlos", 200, 6, 900},
        {"Valentina", 200, 4, 3000},
        {"Lucas", 300, 10, 400},
        {"Bruno", 300, 2, 500},
        {"Agustina", 300, 7, 600}
    };
    newFileExamenes(e);
    informeAlum();
    return(0);
}

void newFileExamenes(Examen vec[]){
    FILE * fptr = fopen("Examenes.dat", "wb");
    fwrite(vec, sizeof(Examen), 10, fptr);
    if (fptr == nullptr) {
        printf("Error al abrir el archivo para escritura.\n");
        exit(1);
    }
    fclose(fptr);
}

void setDatosAlum(int &codAlum, int &codMat){
    printf("Ingrese el codigo del alumno\n");
    scanf("%i", &codAlum);
    printf("Ingrese el codigo de la materia\n");
    scanf("%i", &codMat);
}

bool seguir(){
    int resp;
    do{
        printf("Seguir buscando notas? SI - [1] | NO - [0]\n");
        scanf("%i", &resp);
    }while(resp != 1 && resp != 0);
    return(resp == 1);
}

void informeAlum(){
    int codAlum, codMat, n;
    Examen e;
    FILE * fptr = fopen("Examenes.dat", "rb");
    do{
        setDatosAlum(codAlum, codMat);
        while((n = fread(&e, sizeof(Examen), 1, fptr)) == 1 && !(codAlum == e.codAlum && codMat == e.codMat)){}
        if(n == 0){
            printf("El alumno no rindio el examen.\n");
        }else{
            printf("El alumno %s rindio la materia %i y se saco un %i\n", e.nombre, e.codMat, e.nota);
        }
        rewind(fptr);
    }while(seguir());
    fclose(fptr);
}
