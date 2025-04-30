// Mad cow disease wasnt that bad.
#include <iostream>
using namespace std;

int main()
{   
    int dim, id, indexV, indexR, cantRazas, exit, idProduccion, cantL, totalL, cantPromSup;
    int minL, maxL, maxID, minID;
    bool flag = true;
    cantRazas = 4;
    cantPromSup = 0;
    totalL = 0;
    do{
        printf("Ingrese la cantidad de vacas\n");
        cin>>dim;
        if(dim < 1){
            printf("ERROR: Debe ingresar una cantidad mayor a 0.\n");
        }
    }while(dim < 1);
    int vID[dim] = {0}, vRaza[dim], vPromL[dim], vCantL[dim] = {0}, vCantReg[dim] = {0};
    int razas[cantRazas] = {10,20,30,40}, razasCantL[cantRazas] = {0};
    for(int i = 0; i < dim; i++){
        // Arranca validación ID
        do{
            printf("Ingrese la identificación de la vaca\n");
            cin>>id;
            indexV = 0;
            while((indexV < i) && (id != vID[indexV])){
                //printf("Entre al while\n");
                //printf("Y comparé %i contra %i\n", id, vID[indexV]);
                indexV++;
            }
            if(indexV != i){
                printf("ERROR: El ID %i ya existe.\n", id);
            }
        }while(indexV != i);
        //printf("Voy a guardar %i\n", id);
        vID[i] = id;
        // Arranca validación razas.
        do{
            printf("Ingrese la raza entre las siguientes opciones:\n");
            for(int j = 0; j < cantRazas; j++){
                printf("%i\t", razas[j]);
            }
            printf("\n");
            cin>>vRaza[i];
            indexR = 0;
            while(indexR < cantRazas && vRaza[i] != razas[indexR]){
                indexR++;
            }
            if(indexR == cantRazas){
                printf("ERROR: La raza ingresada es invalida.\n");
            }
        }while(indexR == cantRazas);
        // Arranca validacion prom leche mensual x vaca.
        do{
            printf("Ingrese la cantidad de leche mensual promedio\n");
            cin>>vPromL[i];
            if(vPromL[i] < 0){
                printf("ERROR: La cantidad de leche debe ser mayor a 0.\n");
            }
        }while(vPromL[i] < 1);
    }
    // Comienzo carga de datos produccion
    do{
        printf("Hay datos para cargar? [S:1 | N:0]\n");
        cin>>exit;
        if(exit != 1 && exit != 0){
            printf("ERROR: Respuesta invalida.\n");
        }
    }while(exit != 1 && exit != 0);

    while(exit != 0){
        printf("Ingrese el ID de producción\n");
        cin>>idProduccion;
        do{
            printf("Ingrese el ID de la vaca\n");
            cin>>id;
            indexV = 0;
            while(indexV < dim && id != vID[indexV]){
                indexV++;
            }
            if(indexV == dim){
                printf("ERROR: El ID %i, no existe.\n", id);
            }
        }while(indexV == dim);
        vCantReg[indexV]++; // Cant Reg x Vaca
        do{
            printf("Ingrese la cantidad de leche obtenida.\n");
            cin>>cantL;
            if(cantL < 1){
                printf("ERROR: La cantidad debe ser mayor a 0.\n");
            }
        }while(cantL < 1);
        vCantL[indexV]+= cantL; // Cant Leche x Vaca
        totalL+= cantL;
        indexR = 0;
        while(razas[indexR] != vRaza[indexV]){
            indexR++;
        }
        razasCantL[indexR]+= cantL;
        do{
            printf("Hay datos para cargar? [S:1 | N:0]\n");
            cin>>exit;
            if(exit != 1 && exit != 0){
                printf("ERROR: Respuesta invalida.\n");
            }
        }while(exit != 1 && exit != 0);
    }

    for(int i = 0; i < dim; i++){
        if(flag){
            maxID = vID[i];
            minID = vID[i];
            maxL = vCantL[i];
            minL = vCantL[i];
            flag = false;
        } else if(maxL < vCantL[i]){
            maxL = vCantL[i];
            maxID = vID[i];
        } else if(minL > vCantL[i]){
            minID = vID[i];
            minL = vCantL[i];
        }
        if(vCantL[i] > vPromL[i]){
            cantPromSup++;
        }
    }

    // Punto 1
    printf("La cantidad de vacas total es: %i\n", dim);
    // Punto 2
    for(int i = 0; i < dim; i++){
        printf("La vaca %i produjo: %i\n", vID[i], vCantL[i]);
    }
    // Punto 3
    printf("Entre todas las vacas se produjo: %i\n", totalL);
    // Punto 4
    printf("La vaca %i fue la que más leche generó: %iL\n", maxID, maxL);
    // Punto 5
    printf("La vaca %i fue la que menos leche generó: %iL\n", minID, minL);
    // Punto 6
    for(int i = 0; i < cantRazas; i++){
        printf("La raza %i generó: %iL\n", razas[i], razasCantL[i]);
    }
    // Punto 7
    for(int i = 0; i < dim; i++){
        printf("La vaca %i tiene %i registros.\n", vID[i], vCantReg[i]);
    }
    // Punto 8
    printf("Vacas superaron su produccion promedio: %i\n", cantPromSup);
    return(0);
}