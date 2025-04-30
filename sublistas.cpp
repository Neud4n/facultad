// Ejercicio Sublistas - Terminado.

#include <iostream>
#include <stdio.h>

struct Materia{
    int cod;
    char nombre[50];
};

struct NodoM{
    Materia inf;
    NodoM * sig;
};

typedef NodoM * PuntSL;

struct Docente{
    int legajo;
    char nombre[50];
    PuntSL materias;
};

struct NodoD{
    Docente inf;
    NodoD * sig;
};

typedef NodoD * PuntL;

// Funciones
bool salir();
void cargarDatosDocente(Docente &);
void cargarDatosMateria(Materia &);
void menu();
void mostrarMenu();
void pedirLegajo(int &);
// Funciones para la lista
void inicializarLista(PuntL &);
bool isEmpty(PuntL);
void crearListaDocentes(PuntL &);
void agregarPrimeroLista(PuntL &, Docente);
void agregarOrdenadoLista(PuntL &, Docente);
void agregarUltimoLista(PuntL &, Docente);
void eliminarDeLaLista(PuntL &, int); // Recibe el nro de legajo.
void listarDatosLista(PuntL);
void borrarLista(PuntL &);
// Funciones para la sublista
void inicializarSubLista(PuntSL &);
bool isEmpty(PuntSL);
void agregarPrimeroSubLista(PuntL &, int, Materia);
void agregarOrdenadoSubLista(PuntL &, int, Materia);
void agregarUltimoSubLista(PuntL &, int, Materia);
void eliminarDeLaSubLista(PuntL &, int, int);
void borrarSubLista(PuntSL &);
// Funcion para limpiar la memoria


int main()
{
    menu();
}

void inicializarLista(PuntL &l){
    l = NULL;
}

bool isEmpty(PuntL l){
    return l == NULL;
}

void agregarPrimeroLista(PuntL &l, Docente d){
    PuntL nuevo = new NodoD;
    nuevo->inf = d;
    nuevo->sig = l;
    l = nuevo;
}

void agregarUltimoLista(PuntL &l, Docente d){
    if(isEmpty(l)){
        agregarPrimeroLista(l, d);
    }else{
        PuntL aux = l;
        while(aux->sig){
            aux = aux->sig;
        }
        PuntL nuevo = new NodoD;
        nuevo->inf = d;
        nuevo->sig = NULL;
        aux->sig = nuevo;
    }
}

void agregarOrdenadoLista(PuntL &l, Docente d){
    PuntL ant = NULL;
    PuntL actual = l;
    while(actual && d.legajo > actual->inf.legajo){
        ant = actual;
        actual = actual->sig;
    }
    PuntL nuevo = new NodoD;
    nuevo->inf = d;
    if(ant){
        ant->sig = nuevo;
    }else{
        l = nuevo;
    }
    nuevo->sig = actual;
}

void eliminarDeLaLista(PuntL &l, int leg){
    if(!isEmpty(l)){
        PuntL ant = NULL;
        PuntL bor = l;
        while(bor && bor->inf.legajo != leg){
            ant = bor;
            bor = bor->sig;
        }
        if(bor){ // Si encontré el legajo a borrar
            if(ant){ // Si el legajo a borrar no era el primero de la lista.
                ant->sig = bor->sig;
            }else{
                // Como ant == NULL, el legajo encontrado (bor) era el primero de la lista, el tope de la lista
                // El tope de la lista ahora apunta al que le sigue.
                l = bor->sig; 
            }
        }
        borrarSubLista(bor->inf.materias);
        delete bor;
    }
}

void listarDatosLista(PuntL l){
    PuntL view = l;
    printf("=====================\n");
    printf("Listado de profesores\n");
    printf("=====================\n");
    while(view){
        bool dicta = false;
        printf("Profesor: %s\n", view->inf.nombre);
        printf("Legajo: %i\n", view->inf.legajo);
        printf("Dicta las siguientes materias: ");
        PuntSL viewM = view->inf.materias;

        while(viewM){
            dicta = true;
            printf("%s ", viewM->inf.nombre);
            viewM = viewM->sig;
        }
        if(!dicta){
            puts("Actualmente no dicta ninguna materia.");
        }
        view = view->sig;
        printf("-----\n");
    }
    
}

void inicializarSubLista(PuntSL &sl){
    sl = NULL;
}

bool isEmpty(PuntSL sl){
    return sl == NULL;
}

void agregarPrimeroSubLista(PuntL &l, int leg, Materia m){
    PuntL r = l;
    while(r && leg != r->inf.legajo){
        r = r->sig;
    }
    if(r){
        PuntSL nuevo = new NodoM;
        nuevo->inf = m;
        nuevo->sig = r->inf.materias;
        r->inf.materias = nuevo;
    }else{
        puts("No existe el legajo.");
    }
}

void agregarUltimoSubLista(PuntL &l, int leg, Materia m){
    PuntL r = l;
    while(r && leg != r->inf.legajo){
        r = r->sig;
    }
    if(r){
       if(isEmpty(r->inf.materias)){
            agregarPrimeroSubLista(l, leg, m);
       }else{
            PuntSL nuevo = new NodoM;
            nuevo->inf = m;
            nuevo->sig = NULL;
            PuntSL actual = r->inf.materias;
            while(actual->sig){
                actual = actual->sig;
            }
            actual->sig = nuevo;
       }
    }else{
        puts("No existe el legajo.");
    }
}

void agregarOrdenadoSubLista(PuntL &l, int leg, Materia m){
    PuntL r = l;
    while(r && leg != r->inf.legajo){
        r = r->sig;
    }
    if(r){
        // Creo el nuevo nodo.
        PuntSL nuevo = new NodoM;
        nuevo->inf = m;
        nuevo->sig = NULL;

        // Busco donde posicionarlo.
        PuntSL ant = NULL;
        PuntSL actual = r->inf.materias;
        while(actual && m.cod > actual->inf.cod){
            ant = actual;
            actual = actual->sig;
        }
        
        //Re apunto los nodos.
        nuevo->sig = actual;
        if(ant){
            ant->sig = nuevo;
        }else{
            r->inf.materias = nuevo;
        }
    }else{
        puts("No existe el legajo.");
    }
}

void eliminarDeLaSubLista(PuntL &l, int leg, int cod){
    PuntL r = l;
    while(r && leg != r->inf.legajo){
        r = r->sig;
    }
    if(r){
        PuntSL ant = NULL;
        PuntSL bor = r->inf.materias;
        while(bor && cod != bor->inf.cod){
            ant = bor;
            bor = bor->sig;
        }
        if(bor){
            if(ant){
                ant->sig = bor->sig;
            }else{
                r->inf.materias = bor->sig;
            }
            delete bor;
        }else{
            puts("No existe el codigo.");
        }
    }else{
        puts("No existe el legajo.");
    }
}

bool salir(){
    int resp;
    do{
        puts("Hay mas datos? 1 - Si | 0 - No");
        scanf("%i", &resp);
        if(resp != 1 && resp != 0){
            puts("Ingresa una respuesta valida.");
        }
    }while(resp != 1 && resp != 0);
    return resp == 1;
}

void cargarDatosDocente(Docente &d){
    puts("Ingrese el numero de legajo:");
    scanf("%i", &d.legajo);
    puts("Ingrese el nombre del docente");
    scanf("%49s", d.nombre);
    inicializarSubLista(d.materias);
}

void crearListaDocentes(PuntL &l){
    Docente aux;
    inicializarLista(l);
    do{
        cargarDatosDocente(aux);
        agregarOrdenadoLista(l, aux);
    }while(salir());
}

void cargarDatosMateria(Materia &m){
    puts("Ingrese el codigo de la materia:");
    scanf("%i", &m.cod);
    puts("Ingrese el nombre del la materia");
    scanf("%49s", m.nombre);
}

void mostrarMenu(){
    puts("==============");
    puts("MENU PRINCIPAL");
    puts("==============");
    puts("1.- Crear lista de docentes");
    puts("2.- Agregar un docente al principio de la lista");
    puts("3.- Agregar un docente al final de la lista");
    puts("4.- Agregar un docente de manera ordenada");
    puts("5.- Eliminar un docente de la lista");
    puts("6.- Mostrar lista de docentes");
    puts("7.- Agregar Materia al principio de la lista");
    puts("8.- Agregar Materia al final de la lista");
    puts("9.- Agregar Materia de manera ordenada");
    puts("10.- Borrar la lista de docentes");
    puts("0.- Salir");
}

void menu(){
    int op, leg;
    Docente auxD;
    Materia auxM;
    PuntL l;
    inicializarLista(l);
    do{
        mostrarMenu();
        scanf("%i", &op);
        switch(op){
            case 1:
                if(isEmpty(l)){
                    crearListaDocentes(l);
                }else{
                    puts("Ya existe una lista.");
                }
                break;
            case 2:
                if(!isEmpty(l)){
                    cargarDatosDocente(auxD);
                    agregarPrimeroLista(l, auxD);
                }else{
                    puts("Debe crear una lista antes de cargar un docente.");
                }
                break;
            case 3:
                if(!isEmpty(l)){
                    cargarDatosDocente(auxD);
                    agregarUltimoLista(l, auxD);
                }else{
                    puts("Debe crear una lista antes de cargar un docente.");
                }
                break;
            case 4:
                if(!isEmpty(l)){
                    cargarDatosDocente(auxD);
                    agregarOrdenadoLista(l, auxD);
                }else{
                    puts("Debe crear una lista antes de cargar un docente.");
                }
                break;
            case 5:
                if(!isEmpty(l)){
                    pedirLegajo(leg);
                    eliminarDeLaLista(l, leg);
                }else{
                    puts("La lista esta vacia.");
                }
                break;
            case 6:
                listarDatosLista(l);
                break;
            case 7:
                if(!isEmpty(l)){
                    pedirLegajo(leg);
                    cargarDatosMateria(auxM);
                    agregarPrimeroSubLista(l, leg, auxM);
                }else{
                    puts("No existe ninguna lista de docentes.");
                }
                break;
            case 8:
                if(!isEmpty(l)){
                    pedirLegajo(leg);
                    cargarDatosMateria(auxM);
                    agregarUltimoSubLista(l, leg, auxM);
                }else{
                    puts("No existe ninguna lista de docentes.");
                }
                break;
            case 9:
                if(!isEmpty(l)){
                    pedirLegajo(leg);
                    cargarDatosMateria(auxM);
                    agregarOrdenadoSubLista(l, leg, auxM);
                }else{
                    puts("No existe ninguna lista de docentes.");
                }
                break;
            case 10:
                borrarLista(l);
                break;
            case 0:
                borrarLista(l);
                break;
            default:
                puts("Opcion elegida erronea.");
                break;
        }
    }while(op != 0);
}

void pedirLegajo(int &leg){
    puts("Ingrese el numero de legajo del docente");
    scanf("%i", &leg);
}

void borrarLista(PuntL &l){
    while(l){
        PuntL bor = l;
        l = l->sig;
        borrarSubLista(bor->inf.materias);
        delete bor;
    }
    l = NULL;
}

void borrarSubLista(PuntSL &sl){
    while(sl){
        PuntSL bor = sl;
        sl = sl->sig;
        delete bor; 
    }
    sl = NULL;
}