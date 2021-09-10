#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>   
#include <stdio.h>
#include <fstream>
//Para convertir el texto a numero en excel se usa: =SUSTITUIR(SUSTITUIR(SUSTITUIR(B3;"'";;1);"'";;1);".";",")

//Numeros aleatorios
int RANGO=20;

int N=800;
int NHilos=4;
using namespace std;
struct PasarParametros
{
	int **MatRes;
	int **Mat1;
	int **Mat2;
	int N;
	int colI;
	int colF;
};

void *MultiplicarMatrices(void * args)
{
	struct PasarParametros* Info=(struct PasarParametros*) args;
	
 	for(int a=Info->colI;a<Info->colF;a++){
        for(int i=0;i<Info->N;i++) {
            int suma=0;
            for (int j=0;j<Info->N;j++) {
                suma+=Info->Mat1[i][j]*Info->Mat2[j][a];
            }
            Info->MatRes[i][a]=suma;
        }
    }				
}

int main(int argc, char const *argv[])
{
	ofstream file;//Guardar info en block de notas
	//N=atoi(argv[1]);
	//NHilos=atoi(argv[2]);
	//int NIntentos=atoi(argv[3]);
	int NIntentos=2;
	clock_t tiempoInicio, tiempoFinal;
	double segundos;
	srand((unsigned)time(NULL));
	int **P_Matriz1;
	P_Matriz1=new int*[N];
	int **P_Matriz2;
	P_Matriz2=new int*[N];
	int **P_MatrizR;
	P_MatrizR=new int*[N];
	file.open("Resultados.txt",ios::app);
	file << "'Resultados para N=" << N << " y H=" << NHilos <<"'\n";
	for(int i=0;i<N;i++)
	{
		P_Matriz1[i]=new int[N];
		P_Matriz2[i]=new int[N];
		P_MatrizR[i]=new int[N];
	}
	//LLENADO DE MATRICES 1 Y 2
	for(int x=0;x<N;x++)
		for(int y=0;y<N;y++)
		{
			P_Matriz1[x][y]=(rand()%(RANGO+1))-(RANGO/2);
			P_Matriz2[x][y]=(rand()%(RANGO+1))-(RANGO/2);
		}
	for(int Inte=0;Inte<NIntentos;Inte++)
		{
			pthread_t Hilos[N];
			tiempoInicio = clock();
			int NColHilos=N/NHilos;
			int ColActual=0;
			for(long int i=0;i<NHilos;i++)
			{//Creo los hilos
			    PasarParametros Info;
				Info.N=N;
				Info.colI=ColActual;
				Info.colF=ColActual+NColHilos;
				Info.MatRes=P_MatrizR;
				Info.Mat1=P_Matriz1;
				Info.Mat2=P_Matriz2;
			    pthread_create(&Hilos[i],NULL,&MultiplicarMatrices,&Info);
			    ColActual+=NColHilos;
			}
			for(int i=0;i<N;i++)
			{//Arranco los hilos
			    pthread_join(Hilos[i],NULL);
			}
			tiempoFinal = clock();
			segundos = (double) (tiempoFinal - tiempoInicio) / CLOCKS_PER_SEC;
			cout << "Tamano Matriz: " << N << "x" << N << " tardo: " << segundos << " segundos con "<< NHilos << " hilos" << endl;
			file << "'Intento #" << Inte+1 << "=';'" << segundos <<"';\n";	
			
			}
		file.close();
			
		
	
	
    return 0;
}
