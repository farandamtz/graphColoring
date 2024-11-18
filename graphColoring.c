//PROBLEMA NP-COMPLETO - COLOREADO DE GRAFOS
//COMPLEJIDAD DEL ALGORITMO: O(V²), DONDE V=NÚMERO DE VERTICES DEL GRAFO A COLOREAR

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>

struct Nodo* createNode(int destino);
struct Grafo* createGraph(int V);
void addEdge(struct Grafo* grafo, int origen, int destino);
void printGraph(struct Grafo* grafo);
void eraseGraph(struct Grafo* grafo);
int graphColoring(struct Grafo* grafo);
void printSolution(int V, int colores[]);
struct Grafo* createGraphManually(int V);
struct Grafo* createRandomGraph(int V, int E);
void tryManualGraph();
void try10Vertices();
void try100Vertices();
void try1000Vertices();

struct Nodo{
    int destino;
    struct Nodo* siguiente;
};

struct Arista{
    struct Nodo *cabeza;
};

struct Grafo{
    int vertices;
    struct Arista* arr;
};

struct Nodo* createNode(int destino){
    struct Nodo* nuevoNodo=(struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->destino=destino;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

struct Grafo* createGraph(int V){
    struct Grafo* grafo=(struct Grafo*) malloc(sizeof(struct Grafo));
    grafo->vertices=V;
    grafo->arr=(struct Arista*) malloc(V * sizeof(struct Arista));
    for(int i=0; i<V; i++)
        grafo->arr[i].cabeza=NULL;
    return grafo;
}

void addEdge(struct Grafo* grafo, int origen, int destino){
    struct Nodo* nuevoNodo=createNode(destino);
    nuevoNodo->siguiente=grafo->arr[origen].cabeza;
    grafo->arr[origen].cabeza=nuevoNodo;
    nuevoNodo=createNode(origen);
    nuevoNodo->siguiente=grafo->arr[destino].cabeza;
    grafo->arr[destino].cabeza=nuevoNodo;
}

void printGraph(struct Grafo* grafo){
    for(int i=0; i<grafo->vertices; i++){
        struct Nodo* recorrido=grafo->arr[i].cabeza;
        printf("\nAristas del vertice %d\n%d", i, i);
        while(recorrido!=NULL){
            printf(" -> %d", recorrido->destino);
            recorrido=recorrido->siguiente;
        }
        printf("\n");
    }
}

void eraseGraph(struct Grafo* grafo){
    free(grafo);
}

int graphColoring(struct Grafo* grafo){
    int V=grafo->vertices, colores[V], coloresUsados=-1;
    bool disponibilidad[V];
    for(int a=0; a<V; a++)
        colores[a]=-1;
    colores[0]=0;

    for(int b=0; b<V; b++)
        disponibilidad[b]=true;
    
    for(int k=1; k<V; k++){
        struct Nodo* recorrido=grafo->arr[k].cabeza;
        while(recorrido!=NULL){
            if(colores[recorrido->destino]!=-1){
                disponibilidad[colores[recorrido->destino]]=false;
            }
            recorrido=recorrido->siguiente;
        }
        
        int j=0;
        for(j=0; j<V; j++)
            if(disponibilidad[j]==true)
                break;
        colores[k]=j;
        
        recorrido=grafo->arr[k].cabeza;
        while(recorrido!=NULL){
            if(colores[recorrido->destino]!=-1)
                disponibilidad[colores[recorrido->destino]]=true;
            recorrido=recorrido->siguiente;
        }
    }
    for(int m=0; m<V; m++){
        if(colores[m]>coloresUsados)
            coloresUsados=colores[m];
    }
    printSolution(V, colores);
    return(coloresUsados+1);
}

void printSolution(int V, int colores[]){
    for(int i=0; i<V; i++)
        printf("Vertice %d -> color %d\n", i, colores[i]);
}

struct Grafo* createGraphManually(int V){
    struct Grafo* grafo=createGraph(V);
    addEdge(grafo, 0, 1);
    addEdge(grafo, 0, 4);
    addEdge(grafo, 1, 2);
    addEdge(grafo, 1, 3);
    addEdge(grafo, 1, 4);
    addEdge(grafo, 2, 3);
    addEdge(grafo, 3, 4);
    addEdge(grafo, 4, 5);
    addEdge(grafo, 4, 6);
    addEdge(grafo, 2, 6);
    addEdge(grafo, 3, 5);
    addEdge(grafo, 2, 7);
    addEdge(grafo, 5, 8);
    addEdge(grafo, 7, 8);
    addEdge(grafo, 6, 9);
    addEdge(grafo, 8, 9);
    return(grafo);
}

struct Grafo* createRandomGraph(int V, int E){
    struct Grafo* grafo=createGraph(V);
    int origen, destino;
    for(int i=0; i<E;i++){
        origen=rand()%V;
        destino=rand()%V;
        while(origen==destino)
            destino=rand()%V;
        addEdge(grafo, origen, destino);
    }
    return grafo;
}

void tryManualGraph(){
    int V=10, coloresUsados=0;
    struct Grafo* grafo=createGraphManually(10);
    printGraph(grafo);
    printf("\nGrafo con %d vertices\n", V);
    coloresUsados=graphColoring(grafo);
    printf("\nColores usados: %d\n", coloresUsados);
    eraseGraph(grafo);
}

void try10Vertices(){
    int V=10, E=40, coloresUsados=0;
    struct Grafo* grafo=createGraph(V);
    grafo=createRandomGraph(V, E);
    printGraph(grafo);
    printf("\nGrafo con %d vertices y %d aristas\n", V, E);
    coloresUsados=graphColoring(grafo);
    printf("\nColores usados: %d\n", coloresUsados);
    eraseGraph(grafo);
}

void try100Vertices(){
    int V=100, E=190, coloresUsados=0;
    struct Grafo* grafo=createGraph(V);
    grafo=createRandomGraph(V, E);
    printGraph(grafo);
    printf("\nGrafo con %d vertices y %d aristas\n", V, E);
    coloresUsados=graphColoring(grafo);
    printf("\nColores usados: %d\n", coloresUsados);
    eraseGraph(grafo);
}

void try1000Vertices(){
    int V=1000, E=2500, coloresUsados=0;
    struct Grafo* grafo=createGraph(V);
    grafo=createRandomGraph(V, E);
    printGraph(grafo);
    printf("\nGrafo con %d vertices y %d aristas\n", V, E);
    coloresUsados=graphColoring(grafo);
    printf("\nColores usados: %d\n", coloresUsados);
    eraseGraph(grafo);
}

int main(){
    srand(time(0));
    printf("\n************COLOREADO DE GRAFOS************\n");
    //try10Vertices();
    //try100Vertices();
    try1000Vertices();
    //tryManualGraph();
    return 0;
}