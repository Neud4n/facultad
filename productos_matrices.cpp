// Mejor me cambio a turismo.
#include <stdio.h>
using namespace std;

#define CANT_CLI 3
#define CANT_PRO 3
#define CANT_PAIS 3

struct cliente{
    int id;
    int codPais;
};

struct producto{
    int cod;
    int price;
};

void setClientes(cliente [], int);
bool rangoOk(int, int, int);
void setProductos(producto [], int);
int getIndexCliente(cliente [], int, int);
void setDatos(int [][CANT_PRO], cliente [], producto [], int[][CANT_PRO]);
void inicializarMatriz(int [][CANT_PRO], int, int, int);
bool hayDatos();
void informe(int [][CANT_PRO], cliente [], producto [], int [][CANT_PRO]);
void inicializarVector(int [], int, int);
void sumFilasMatriz(int [][CANT_PRO], int [], int);
void getSinPedidos(int [], int [], int &);

int main()
{
    cliente clientes[CANT_CLI]; producto productos[CANT_PRO];
    int cliProd[CANT_CLI][CANT_PRO], prodPais[CANT_PAIS][CANT_PRO];
    setClientes(clientes, CANT_CLI);
    setProductos(productos, CANT_PRO);
    inicializarMatriz(cliProd,CANT_CLI, CANT_PRO, 0);
    inicializarMatriz(prodPais, CANT_PAIS , CANT_PRO, 0);
    setDatos(cliProd, clientes, productos, prodPais);
    informe(cliProd, clientes, productos, prodPais);
}

void setClientes(cliente vec[], int dim){
    int index;
    bool rango;
    for(int i = 0; i < dim; i ++){
        do{
            printf("Ingrese el ID del cliente\n");
            scanf("%i", &vec[i].id);
            index = getIndexCliente(vec, i, vec[i].id);
            if(index != -999){
                printf("ERROR: El cliente %i ya existe.\n", vec[i].id);
            }
        }while(index != -999);
        do{
            printf("Ingrese el pais del cliente\n");
            scanf("%i", &vec[i].codPais);
            rango = rangoOk(vec[i].codPais, 1, CANT_PAIS);
            if(!rango){
                printf("ERROR: El código del país debe estar entre 1 - %i\n", CANT_PAIS);
            }
        }while(!rango);
    }
}

int getIndexCliente(cliente vec[], int dim, int target){
    int i = 0;
    while(i < dim && vec[i].id != target){
        i++;
    }
    if(i == dim){
        return(-999);
    } else{
        return(i);
    }
}

int getIndexProd(producto vec[], int dim, int target){
    int i = 0;
    while(i < dim && vec[i].cod != target){
        i++;
    }
    if(i == dim){
        return(-999);
    } else{
        return(i);
    }
}

bool rangoOk(int num, int desde, int hasta){
    return((num <= hasta) && (num >= desde));
}

void setProductos(producto vec[], int dim){
    int index;
    bool rango;
    for(int i = 0; i < dim; i ++){
        do{
            printf("Ingrese el ID del producto\n");
            scanf("%i", &vec[i].cod);
            index = getIndexProd(vec, i, vec[i].cod);
            if(index != -999){
                printf("ERROR: El producto %i ya existe.\n", vec[i].cod);
            }
        }while(index != -999);
        do{
            printf("Ingrese el precio del producto\n");
            scanf("%i", &vec[i].price);
        }while(vec[i].price < 0);
    }
}

void inicializarMatriz(int mat[][CANT_PRO], int f, int c, int num){
    for(int i = 0; i < f; i++){
        for(int j = 0; j < c; j++){
            mat[i][j] = num;
        }
    }
}

bool hayDatos(){
    bool rango;
    int resp;
    do{
        printf("Hay datos? - Si [1] | No [0]\n");
        scanf("%i", &resp);
        rango = rangoOk(resp, 0, 1);
    }while(!rango);
    if(resp == 1){
        return(true);
    }else{
        return(false);
    }
}

void setDatos(int mat[][CANT_PRO], cliente vecCli[], producto vecProd[], int matPais[][CANT_PRO]){
    bool exit = hayDatos();
    int idCli, codProd, dia, cantPedido, indexCli, indexProd;
    while(exit){
        do{
            printf("Ingrese el código del cliente\n");
            scanf("%i", &idCli);
            indexCli = getIndexCliente(vecCli, CANT_CLI, idCli);
            if(indexCli == -999){
                printf("ERROR: El ID %i no existe.\n", idCli);
            } 
        }while(indexCli == -999);
        do{
            printf("Ingrese el código del producto\n");
            scanf("%i", &codProd);
            indexProd = getIndexProd(vecProd, CANT_PRO, codProd);
            if(indexProd == -999){
                printf("ERROR: El código de producto %i no existe.\n", codProd);
            }
        }while(indexProd == -999);
        /* annoying asf
        do{
            printf("Ingrese el día del pedido [1-31]\n");
            scanf("%i", &dia);
            if(!rangoOk(dia, 1, 31)){
                printf("ERROR: El día %i es invalido\n", dia);
            }
        }while(!rangoOk(dia, 1, 31));
        */
        do{
            printf("Ingrese la cantidad pedida del producto\n");
            scanf("%i", &cantPedido);
            if(cantPedido <= 0){
                printf("ERROR: La cantidad debe ser superior a 0.\n");
            }
        }while(cantPedido <= 0);
        mat[indexCli][indexProd] += cantPedido;
        matPais[vecCli[indexCli].codPais-1][indexProd] += cantPedido;
        exit = hayDatos();
    }
}

void inicializarVector(int vec[], int dim, int num){
    for(int i = 0; i < dim; i++){
        vec[i] = num;
    }
}

void sumFilasMatriz(int mat[][CANT_PRO], int vec[], int dim){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < CANT_PRO; j++){
            vec[i] += mat[i][j];
        }
    }
}

/*
500     0       0
0       500     0
0       0       0
0       0       0
0       0       0
*/
void sumColumMatriz(int mat[][CANT_PRO], int vec[], int dim){
    for(int i = 0; i < CANT_PRO; i++){
        for(int j = 0; j < dim; j++){
            vec[i] += mat[j][i];
        }
    }
}

void getSinPedidos(int pedidosPais[], int paisesSinPedido[], int &newDim){
    for(int i = 0; i < CANT_PAIS; i++){
        if(pedidosPais[i] == 0){
            paisesSinPedido[newDim] = i;
            newDim++;
        }
    }
}

void informe(int mat[][CANT_PRO], cliente vecCli[], producto vecProd[], int matPais[][CANT_PRO]){
    int totalProductos[CANT_PRO];
    int totalPaises[CANT_PAIS];
    int sinPedido[CANT_PAIS];
    int cantSinPedido = 0;
    inicializarVector(totalProductos, CANT_PRO, 0);
    inicializarVector(totalPaises, CANT_PAIS, 0);
    // PUNTO 1
    printf("====================================\n");
    printf("PEDIDOS POR CLIENTE\n");
    printf("====================================\n");
    for(int i = 0; i < CANT_CLI; i++){
        printf("* CLIENTE %i\n", vecCli[i].id);
        for(int j = 0; j < CANT_PRO; j++){
            printf("Producto %i  - Cant: %i\n", vecProd[j].cod, mat[i][j]);
        }
    }
    // PUNTO 2
    printf("====================================\n");
    printf("PEDIDOS POR PAIS\n");
    printf("====================================\n");
    for(int i = 0; i < CANT_PAIS; i++){
        printf("* PAIS %i\n", i+1);
        for(int j = 0; j < CANT_PRO; j++){
            printf("Producto %i  - Cant: %i\n", vecProd[j].cod, matPais[i][j]);
        }
    }
    // PUNTO 3
    printf("====================================\n");
    printf("INFORME POR PRODUCTO - TOTAL PEDIDOS\n");
    printf("====================================\n");
    sumColumMatriz(mat, totalProductos, CANT_CLI);
    for(int i = 0; i < CANT_PRO; i++){
        printf("Producto %i - Cant: %i\n", vecProd[i].cod ,totalProductos[i]);
    }
    // PUNTO 4
    printf("====================================\n");
    printf("INFORME POR PAIS - TOTAL PEDIDOS\n");
    printf("====================================\n");
    sumFilasMatriz(matPais, totalPaises, CANT_PAIS);
    for(int i = 0; i < CANT_PAIS; i++){
        printf("Pais %i - Cant: %i\n", i+1, totalPaises[i]);
    }
    // PUNTO 5
    printf("====================================\n");
    printf("INFORME POR PRODUCTO - MONTO x PAIS\n");
    printf("====================================\n");
    for(int i = 0; i < CANT_PRO; i ++){
        printf("Producto: %i\n", vecProd[i].cod);
        for(int j = 0; j < CANT_PAIS; j ++){
            printf("Pais: %i - Costo: %i\n", j+1, matPais[j][i]*vecProd[i].price);
        }
    }
    // PUNTO 6
    printf("====================================\n");
    printf("INFORME DE PAISES SIN PEDIDOS\n");
    printf("====================================\n");
    getSinPedidos(totalPaises, sinPedido, cantSinPedido);
    for(int i = 0; i < cantSinPedido; i++){
        printf("PAIS: %i\n", sinPedido[i]+1);
    }
}