#include <iostream>
using namespace std;

// Prototipos
void setCantParticipantes(int *);
bool validarRango(int, int, int);
bool validarDesde(int, int);
int buscarValor(int [], int, int);
void inicializarVectorValor(int [], int, int);
//void inicializarVectorBool(bool [], int, bool);
void cargarDatosCompetidores(int [], int[], int[], int);
void cargarResultadosCompetidores(int [], int [], int [], int [], int);
bool posicionesIguales(int [], int [], int [], int);
bool hayDatos(); // Si hay datos para cargar devuelve TRUE, de lo contrario FALSE.
void mostrarResultadosCompetidores(int [], int [], int [], int [], int [], int);
int buscarMenorVector(int [], int);
int sumaTotal(int [], int[], int[], int);

int main()
{   
    int dim;
    setCantParticipantes(&dim);
    int nroComp[dim], puestoActual[dim], categoria[dim], tiempoNatacion[dim], tiempoRunning[dim], tiempoCiclismo[dim], tiempoTotal[dim];
    inicializarVectorValor(tiempoNatacion, dim, 0);
    inicializarVectorValor(tiempoRunning, dim, 0);
    inicializarVectorValor(tiempoCiclismo, dim, 0);
    inicializarVectorValor(tiempoTotal, dim, 0);
    cargarDatosCompetidores(nroComp, puestoActual, categoria, dim);
    cargarResultadosCompetidores(nroComp, tiempoNatacion, tiempoRunning, tiempoCiclismo, dim);
    mostrarResultadosCompetidores(nroComp, tiempoNatacion, tiempoRunning, tiempoCiclismo, tiempoTotal, dim);
}

void setCantParticipantes(int *dimension){
    do{
        printf("Ingrese la cantidad de participantes\n");
        scanf("%d", &(*dimension));
        if(*dimension <= 0){
            printf("ERROR: Debe ingresar un valor mayor a 0\n");
        }
    }while(*dimension <= 0);
}

void inicializarVectorValor(int vector[], int dim, int nroIniciar){
    for(int i = 0; i < dim; i++){
        vector[i] = 0;
    }
}

void cargarDatosCompetidores(int nroComp[], int puestoActual[], int categoria[], int dimension){
    bool rangoOk;
    for(int i = 0; i < dimension; i++){
        do{
            printf("Ingrese el nro para el competidor %d\n", i+1);
            scanf("%d", &nroComp[i]);
            rangoOk = validarDesde(nroComp[i], 0);
            if(!rangoOk)
                printf("ERROR: El nro de competidor debe ser mayor a 0.\n");
        }while(!rangoOk);
        do{
            printf("Ingrese el puesto actual en el Ranking [0 - 10000]\n");
            scanf("%d", &puestoActual[i]); 
            rangoOk = validarRango(puestoActual[i], 0, 10000);
            if(!rangoOk)
                printf("ERROR: El puesto ingresado es invalido.\n");
        }while(!rangoOk);
        do{
            printf("Ingrese la categoria del competidor [ 1 / 2 / 3 / 4]\n");
            scanf("%d", &categoria[i]);
            rangoOk = validarRango(categoria[i],1, 4);
            if(!rangoOk)
                printf("ERROR: La categoria ingresada es invalida\n");
        }while(!rangoOk);
    }
}

bool validarRango(int nroValidar, int nroDesde, int nroHasta){
    // Si está dentro del rango devuelve TRUE, de lo contrario FALSE.
    return ((nroValidar >= nroDesde) && (nroValidar <= nroHasta));
}

bool validarDesde(int nroValidar, int nroBase){
    // Devuelve TRUE si el número a validar es superior al número base.
    return(nroValidar > nroBase);
}

void cargarResultadosCompetidores(int nroComp[], int tiempoNatacion[], int tiempoRunning[], int tiempoCiclismo[], int dim){
    int index, nro;
    bool exit = hayDatos(), rangoOk, flagDisciplina;
    while(exit){
        do{
            printf("Ingrese el numero del competidor:\n");
            scanf("%d", &nro);
            index = buscarValor(nroComp, nro, dim);
            if(index == -999)
                printf("El nro de competidor %i no existe.\n");
        }while(index == -999);
        do{
            printf("Ingrese la disciplina en la que participo el competidor %i:\n", nroComp[index]);
            printf("1 - Running\n2 - Ciclismo\n3 - Natacion\n");
            scanf("%d", &nro); // Reutilizo la variable.
            rangoOk = validarRango(nro, 1, 3);
            flagDisciplina = false;
            if(!rangoOk)
                printf("ERROR: El número de disciplina ingresado es invalido.\n");
            switch (nro){
                case 1:
                    if(tiempoRunning[index] != 0){
                        printf("ERROR: Para Running el competidor ya tiene un tiempo registrado.\n");
                        flagDisciplina = true;
                    }
                    break;
                case 2:
                    if(tiempoCiclismo[index] != 0){
                        printf("ERROR: Para Ciclismo el competidor ya tiene un tiempo registrado.\n");
                        flagDisciplina = true;
                    }
                    break;
                case 3:
                    if(tiempoNatacion[index] != 0){
                        printf("ERROR: Para Natacion el competidor ya tiene un tiempo registrado.\n");
                        flagDisciplina = true;
                    }
                break;
            }    
        }while(!rangoOk || flagDisciplina);
        switch(nro){
            case 1:
                do{
                    printf("Ingrese el tiempo que tuvo en Running el competidor %i\n", nroComp[index]);
                    scanf("%d", &tiempoRunning[index]);
                    rangoOk = validarDesde(tiempoRunning[index], 0);
                    if(!rangoOk)
                        printf("ERROR: El tiempo ingresado debe ser mayor a 0.\n");
                }while(!rangoOk);
                break;
            case 2:
                do{
                    printf("Ingrese el tiempo que tuvo en Ciclismo el competidor %i\n", nroComp[index]);
                    scanf("%d", &tiempoCiclismo[index]);
                    rangoOk = validarDesde(tiempoCiclismo[index], 0);
                    if(!rangoOk)
                        printf("ERROR: El tiempo ingresado debe ser mayor a 0.\n");
                }while(!rangoOk);
                break;
            case 3:
                do{
                    printf("Ingrese el tiempo que tuvo en Natacion el competidor %i\n", nroComp[index]);
                    scanf("%d", &tiempoNatacion[index]);
                    rangoOk = validarDesde(tiempoNatacion[index], 0);
                    if(!rangoOk)
                        printf("ERROR: El tiempo ingresado debe ser mayor a 0.\n");
                }while(!rangoOk);
                break;
        }
        exit = hayDatos();
    }
}

int buscarValor(int nroComp[], int target, int dim){
    int i = 0;
    while(i < dim && nroComp[i] != target){
        i ++;
    }
    if(i == dim)
        return(-999); // Si no existe el competidor devuelvo -1
    return i; // Recupero el incide del competidor para luego cargar los datos.
}

bool hayDatos(){
    int exit;
    do{
        printf("Hay registros para cargar? [ S: 1 | N: 0 ]\n");
        scanf("%d", &exit);
        if(exit != 0 && exit != 1)
            printf("ERROR: Respuesta invalida.\n");
    }while(exit != 0 && exit != 1);
    if(exit == 0)
        return(false);
    return(true);
}

void mostrarResultadosCompetidores(int nroComp[], int tiempoNatacion[], int tiempoRunning[], int tiempoCiclismo[], int tiempoTotal[], int dim){
    int compAllDis = 0, indexMenorT;
    int cantCompDis[3] = {0}; // 0 - Running | 1 - Ciclismo | 2 - Natacion
    // Punto 1
    printf("====================================\n");
    printf("Informe por competidor\n");
    printf("====================================\n");
    for(int i = 0; i < dim; i++){
        printf("Informe del competidor Nro %i\n", nroComp[i]);
        if(tiempoNatacion[i] == 0){
        	printf("No participo de natacion.\n");
		}else{
			printf("Participo de natacion y hizo un tiempo de %d minutos.\n", tiempoNatacion[i]);	
		}
        if(tiempoRunning[i] == 0){
        	printf("No participo de running.\n");
		}else{
			printf("Participo de running y hizo un tiempo de %d minutos\n", tiempoRunning[i]);	
		}
        if(tiempoCiclismo[i] == 0){
        	printf("No participo de ciclismo.\n");	
		}else{
			printf("Participo de ciclismo y hizo un tiempo de %d minutos\n", tiempoCiclismo[i]);	
		}
    }
    // Punto 2
    for(int i = 0; i < dim; i++){
        if(posicionesIguales(tiempoNatacion, tiempoRunning, tiempoCiclismo, i))
            compAllDis+=1;
    }
    printf("La cantidad de competidores que finalizaron las 3 etapas: %d\n", compAllDis);
    // Punto 3
    for(int i = 0; i < dim; i ++){
        if(tiempoRunning[i] != 0)
            cantCompDis[0]+=1;
        if(tiempoCiclismo[i] != 0)
            cantCompDis[1]+=1;
        if(tiempoNatacion[i] != 0)
            cantCompDis[2]+=1;
    }
    printf("La cantidad de competidores que finalizaron Running fue: %d\n", cantCompDis[0]);
    printf("La cantidad de competidores que finalizaron Ciclismo fue: %d\n", cantCompDis[1]);
    printf("La cantidad de competidores que finalizaron Natacion fue: %d\n", cantCompDis[2]);
    if(cantCompDis[0] > 0){
    	indexMenorT = buscarMenorVector(tiempoRunning, dim);
    	printf("El menor tiempo en running pertenece a %i con un tiempo de %im\n", nroComp[indexMenorT], tiempoRunning[indexMenorT]);	
	}
	if(cantCompDis[1] > 0){
    	indexMenorT = buscarMenorVector(tiempoCiclismo, dim);
    	printf("El menor tiempo en ciclismo pertenece a %i con un tiempo de %im\n", nroComp[indexMenorT], tiempoCiclismo[indexMenorT]);
	}
	if(cantCompDis[2] > 0){
    	indexMenorT = buscarMenorVector(tiempoNatacion, dim);
    	printf("El menor tiempo en natacion pertenece a %i con un tiempo de %im\n", nroComp[indexMenorT], tiempoNatacion[indexMenorT]);
	}
    //printf("El mejor tiempo logrado en Running es %d y lo logro %d", tiempoRunning[indexMenorT],  )
    for(int i = 0; i < dim; i++){
    	tiempoTotal[i] = sumaTotal(tiempoRunning, tiempoCiclismo, tiempoNatacion, i);
    	if(tiempoTotal[i] != 0){
    		printf("El competidor %i tardo %i en finalizar todas las disciplinas.\n", nroComp[i], tiempoTotal[i]);
		}
	}
}

bool posicionesIguales(int tiempoNatacion[], int tiempoRunning[], int tiempoCiclismo[], int index){
    return((tiempoNatacion[index] != 0 && tiempoCiclismo[index] != 0 && tiempoRunning[index] != 0));
}

/*
void inicializarVectorBool(bool compCheckDis[], int dim, bool iniciarValor){
    
}
*/

int buscarMenorVector(int vecTiempo[], int dim){
    int index, minTiempo;
    bool flag = true;
    for(int i = 0; i < dim; i ++){
    	if(vecTiempo[i] != 0){
    		if(flag){
    			index = i;
    			minTiempo = vecTiempo[i];
    			flag == false;
			}else{
				if(minTiempo > vecTiempo[i]){
					minTiempo = vecTiempo[i];
					index = i;
				}
			}
		}
    }
    return index;
}

int sumaTotal(int tiempoRunning[], int tiempoCiclismo[], int tiempoNatacion[], int index){
	int sum = 0;
	if(posicionesIguales(tiempoRunning, tiempoCiclismo, tiempoNatacion, index)){
		sum = tiempoRunning[index] + tiempoCiclismo[index] + tiempoNatacion[index];
	}
	return sum;
}