#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>

const int n = 400;

int numeroHilos = 4;

int m1[n][n];

int m2[n][n];

int m3[n][n];


struct pasarArgumentos{
    int cantidad;
};

void llenar(int [n][n]);

void mostrar(int [n][n]);

void *multiplicar(void *args);


using namespace std;

int main(int argc, char const *argv[])
{
    int y = atoi(argv[4]);

    //Medir el tiempo de ejecucion

    clock_t tiempoInicio, tiempoFinal;
    double segundos;

    tiempoInicio = clock();


    //Creamos los hilos
    pthread_t hilos[numeroHilos];

    //Creamos las matrices

    llenar(m1);

    //mostrar(m1);

    llenar(m2);

    //mostrar(m2);

    int i = 0;
    pasarArgumentos info;
    //asignacion de los hilos
    for(i = 0; i < numeroHilos; i++){
        info.cantidad = i;
        pthread_create(&hilos[i], NULL, &multiplicar, &info);
    }

    //union de los hilos
    for(int i = 0; i < numeroHilos; i++){
        pthread_join(hilos[i], NULL);
    }

    //mostrar(m3);
  
    tiempoFinal = clock();

    segundos = (double) (tiempoFinal - tiempoInicio) / CLOCKS_PER_SEC;

    //Aqui se hace el guardado con archivos

    printf("Tamano Matriz %d * %d, tiempo =  %f segundos",n,n,segundos);

    printf("\n");

    printf("Numero de hilos:%d",numeroHilos);

    return 0;

}

void llenar(int matriz[n][n]){
    srand(time(NULL));
    for(int fila = 0; fila < n; fila++){
        for(int columna = 0; columna < n; columna++){
            matriz[fila][columna] = rand()%99+1;
        }
    }
}

void mostrar(int matriz[n][n]){
    for(int fila = 0; fila < n; fila++){
        for(int columna = 0; columna < n; columna++){
            printf("%d\t",matriz[fila][columna]);
        }
        printf("\n");
    }
}

void *multiplicar(void *args){
    //cuantas filas de trabajo le toca a cada hilos

    struct pasarArgumentos* Info=(struct pasarArgumentos*) args;

    int indiceDelHilo = Info->cantidad;

    //printf("%d\n",indiceDelHilo);

    //printf("%d\t",id);

    int filasPorHilos = n / numeroHilos;

    //Necesito saber un inicio del hilo
    int inicio = indiceDelHilo * filasPorHilos;


    //Necesito saber un final del hilo
    int final = (indiceDelHilo+1) * filasPorHilos;

    for(int x = inicio; x < final; x++){
        for(int y = 0; y < n; y++){
            for(int z = 0; z < n; z++){
                m3[x][y] += m1[x][z] * m2[z][y];

            }
        }
    }
    return 0;
}