// Dear reader only god knows what I did here. Good luck;

#include <iostream>
using namespace std;

struct vacas{
    int id;
    int raza;
    int lProm;
    int lecheAcum = 0;
    int registros = 0;
};

struct razas{
    int raza;
    int lecheAcum = 0;
};


// PROTOTIPOS
int getDimension();
void setInfoVacas(vacas vaca[], int dim, razas raza[], int dimRaza);
void setID(vacas vaca[], int index);
bool validoExistencia(int target, vacas vaca[], int dimension);
void setRaza(vacas vaca[], int index, razas raza[], int dimRaza);
void setPromL(vacas vaca[], int index);
bool hayDatos();
void cargaProd(bool exit, vacas vaca[], int dimension, razas raza[], int dimRaza);
int getIndex(vacas vaca[], int dimension);
int setLecheObtenida(vacas vaca[], int index);
void showInforme(vacas vaca[], razas raza[], int dimVacas, int dimRazas);
void sumRazaLeche(vacas vaca[], int index, razas raza[], int dimensionRazas, int lecheOb);

int main()
{
    int dim;
    bool exit;
    const int dimR = 4;
    razas raza[dimR] = {{10},{20},{30},{40}};
    dim = getDimension();
    vacas vaca[dim];
    setInfoVacas(vaca, dim, raza, dimR);
    exit = hayDatos();
    cargaProd(exit, vaca, dim, raza, dimR);
    showInforme(vaca, raza, dim, dimR);
    return(0);
}

int getDimension(){
    int dim;
    do{
        printf("Ingrese la cantidad de vacas\n");
        scanf("%i", &dim);
        if(dim <= 0)
            printf("ERROR: La cantidad debe ser mayor a 0.\n");
    }while(dim <= 0);
    return dim;
}

void setInfoVacas(vacas vaca[], int dim, razas raza[], int dimRaza){
    for(int i = 0; i < dim; i++){
        setID(vaca, i);
        setRaza(vaca, i, raza, dimRaza);
        setPromL(vaca, i);
    }
}

void setID(vacas vaca[], int index){
    bool existe;
    do{
        printf("Ingrese el ID de la vaca\n");
        scanf("%i", &vaca[index].id);
        existe = validoExistencia(vaca[index].id, vaca, index);
        if(existe)
            printf("ERROR: El ID %i ya existe.\n", vaca[index].id);
    }while(existe);
}

bool validoExistencia(int target, vacas vaca[], int dimension){
    int i = 0;
    while(i < dimension && target != vaca[i].id){
        if(target != vaca[i].id)
            i++;
    }
    if(i == dimension)
        return false;
    return true;
}

void setRaza(vacas vaca[], int index, razas raza[], int dimRaza){
    int indexR;
    do{
        printf("Ingrese la raza de la vaca:\n");
        scanf("%i", &vaca[index].raza);
        indexR = 0;
        while(indexR < dimRaza && vaca[index].raza != raza[indexR].raza){
            indexR++;
        }
        if(indexR == dimRaza){
            printf("ERROR: La raza ingresada no es valida.\n");
            printf("Las opciones validas son:\n");
            for(int i = 0; i < dimRaza; i++){
                printf("%i\t", raza[i].raza);
            }
            printf("\n");
        }
    }while(indexR == dimRaza);
}

void setPromL(vacas vaca[], int index){
    do{
        printf("Ingrese la cantidad de leche promedio mensual.\n");
        scanf("%i", &vaca[index].lProm);
        if(vaca[index].lProm <= 0){
            printf("ERROR: La cantidad de litros debe ser mayor a 0.\n");
        }
    }while(vaca[index].lProm <= 0);
}

bool hayDatos(){
    int answer;
    do{
        printf("Hay datos para cargar? [S:1 | N:0]\n");
        scanf("%i", &answer);
    }while(answer != 1 && answer != 0);
    if(answer == 1)
        return true;
    return false;
}

void cargaProd(bool exit, vacas vaca[], int dimension, razas raza[], int dimRaza){
    int idProd, cantL, indexVaca;
    while(exit){
        printf("Ingrese el ID de producción\n");
        scanf("%i", &idProd);
        indexVaca = getIndex(vaca, dimension);
        vaca[indexVaca].registros++;
        cantL = setLecheObtenida(vaca, indexVaca);
        sumRazaLeche(vaca, indexVaca, raza, dimRaza, cantL);
        exit = hayDatos();
    }
}

int getIndex(vacas vaca[], int dimension){
    int idVaca, index;
    bool existe;
    do{
        printf("Ingrese el ID de la vaca\n");
        scanf("%i", &idVaca);
        existe = validoExistencia(idVaca, vaca, dimension);
        if(!existe)
            printf("ERROR: El ID %i no existe.\n", idVaca);
    }while(!existe);
    index = 0;
    while(index < dimension && idVaca != vaca[index].id){
        index++;
    }
    return(index);
}

int setLecheObtenida(vacas vaca[], int index){
    int l;
    do{
        printf("Ingrese la cantidad de litros obtenidos.\n");
        scanf("%i", &l);
        if(l <= 0)
            printf("ERROR: La cantidad debe ser mayor a 0.\n");
    }while(l <= 0);
    vaca[index].lecheAcum+=l;
    return(l);
}

void showInforme(vacas vaca[], razas raza[], int dimVacas, int dimRazas){
    int totalL = 0, cantSupProm = 0;
    int maxID, minID, maxL, minL;
    // Punto 1
    printf("La cantidad de vacas es: %i\n", dimVacas);
    // Punto 2
    for(int i = 0; i < dimVacas; i++){
        printf("La vaca %i generó %iL\n", vaca[i].id, vaca[i].lecheAcum);
        totalL+= vaca[i].lecheAcum;
        if(i == 0){
            maxID = vaca[i].id;
            minID = vaca[i].id;
            maxL = vaca[i].lecheAcum;
            minL = vaca[i].lecheAcum;
        } else if(maxL < vaca[i].lecheAcum){
            maxL = vaca[i].lecheAcum;
            maxID = vaca[i].id;
        } else if(minL > vaca[i].lecheAcum){
            minL = vaca[i].lecheAcum;
            minID = vaca[i].id;
        }
        if(vaca[i].lProm < vaca[i].lecheAcum){
            cantSupProm++;
        }
    }
    // Punto 3
    printf("La cantidad de leche total entre todas la vacas es: %i\n", totalL);
    // Punto 4
    printf("La vaca %i fue la que generó más leche: %i\n", maxID, maxL);
    // Punto 5
    printf("La vaca %i fue la que generó menos leche: %i\n", minID, minL);
    // Punto 6
    for(int i = 0; i < dimRazas; i++){
        printf("La raza %i, generó %iL de leche.\n", raza[i].raza, raza[i].lecheAcum);
    }
    // Punto 7
    for(int i = 0; i < dimVacas; i++){
        printf("La vaca %i tuvo %i registros\n", vaca[i].id, vaca[i].registros);
    } 
    // Punto 8
    printf("La cantidad de vacas que superaron su producción fue: %i\n", cantSupProm);
}

void sumRazaLeche(vacas vaca[], int index, razas raza[], int dimensionRazas, int lecheOb){
    int i = 0;
    while(i < dimensionRazas && vaca[index].raza != raza[i].raza){
        i++;
    }
    raza[i].lecheAcum+=lecheOb;
}