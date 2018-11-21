#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;
const int MAX_NODES = 220;
enum Color {Blanco,Gris,Negro};
typedef struct  {
	int grafo[MAX_NODES][MAX_NODES];
	int ocup;
}Matriz;
typedef struct{
	int n;
	int padre;
	int i;
	int f;
	Color color;

}Nodo;
//Parametros grafo, nodos, ordenacion, array que va a ser rellenado con los nodos en orden topologico y un booleano que nos indicara si es ciclico el grafo o no
void DFS(Matriz & matrizAdyacencia, Nodo  nodos[], int ordenacion[], bool &ciclico);
////Parametros, grafo , nodos, array de ordenacion, n= nodo actual, tiempo que llevo actualemten,indexof nos dice el indice del array ordenaciomn
void DfsVisit(Matriz & matrizAdyacencia, Nodo nodos[], int ordenacion[], int n, int &time, bool &ciclico, int & indexOrd);
//
void DFSConexo(Matriz & matrizAdyacencia, Nodo  nodos[], int ordenado[]);
void cuerpo(Matriz & matrizAdyacencia);
Matriz Traspuesta(Matriz & matrizAdyacencia);
void generaAleatorio();
void tiempo(double tiempos[], int nodes[], int n);
int main() {
	double tiempos[50];
	int nodes[50];
	int cont = 0;
	clock_t ini=0;
	clock_t fin=0;
	double sec;
	char n;
	cout << "Desea crear casos aleatorios(en el caso de por N,se usaran los creados anteriormente) (S o N)" << endl;
	cin >> n;
	while (n != 'S' && n != 'N') {
		cout << "Desea crear casos aleatorios(en el caso de por N,se usaran los creados anteriormente) (S o N)" << endl;
		cin >> n;
	}
	if (n == 'S') {
		generaAleatorio();
	}
	//Lectura de Archivo y relleno el struct Matriz
	ifstream file;
	file.open("pruebas.txt");
	char c;
	file >> c;
	Matriz m;
	while (c != 'F')
	{
		m.ocup = 0;
		while (c != '\n') {
			m.ocup = m.ocup * 10 + (c - 48);
			file.get(c);
		}
		for (int i = 0; i < m.ocup; i++)
		{
			for (int j = 0; j < m.ocup; j++) {
				file >> c;
				m.grafo[i][j] = c - 48;
			}
		}
		//tiempo antes de ejecutar el algortimo
		ini = ini + clock();
		//cuerpo principal del programa donde se aplica todo
		cuerpo(m);
		//tiempo que ha tardado el programa
		fin = fin + clock();
		sec = (double)(fin - ini) / CLOCKS_PER_SEC;
		if (m.ocup > 0){
			tiempos[cont] = sec;
		nodes[cont] = m.ocup;
		cont++;
	}
		file >> c;
	}

	file.close();
	//nos guarda en un archivo grafica, el tiempo respecto de los nodos
	tiempo(tiempos, nodes, cont);
	system("pause");
	return 0;
}
void tiempo(double tiempos[], int nodes[], int n) {
	ofstream pruebas;
	pruebas.open("grafica.txt");

		for (int i = 0; i < n; i++)
		{
			pruebas << tiempos[i] <<" "<< nodes[i] << "\n";
		}
		

	pruebas.close();

}
void cuerpo(Matriz & matrizAdyacencia) {

	Nodo nodos[MAX_NODES];
	// en ordenacion tendre los nodos ordenados topologicamente en caso de ser aciclico
	int ordenacion[MAX_NODES];
	bool ciclico = false;
	Matriz Tras;
	//LLamo a dfs para calcular si es ciclico o no y su ordenacion topologica
	DFS(matrizAdyacencia, nodos, ordenacion, ciclico);

	if (ciclico) { cout << "ciclico" << endl; 
	// si es ciclico hago la traspuesta 
	Tras = Traspuesta(matrizAdyacencia);
	// dDFS conexo nos calcula las componentes conexas
	DFSConexo(Tras, nodos, ordenacion);
	}
	else {
		// en caso de ser aciclico nos muestra la ordenacion topologica
		cout << "aciclico" << matrizAdyacencia.ocup<<  endl;
		for (int i = 0; i < matrizAdyacencia.ocup; i++)
		{
			cout << ordenacion[i] <<i<< endl;
			
		}
	}


}
void DFS(Matriz & matrizAdyacencia, Nodo  nodos[],int ordenacion[],bool &ciclico) {
	int time = 0;
	//ponemos todos los nodos a blanco y su padre a -1
	for (int i = 0; i < matrizAdyacencia.ocup; i++)
	{
		nodos[i].color = Blanco;
		nodos[i].padre = -1;
	}
	int inicial = 0;
	 for (int i = 0; i < matrizAdyacencia.ocup; i++)
	{
		 if (nodos[i].color == Blanco) {
			 //mandamos dfs visit para visitar las componentes conexas 
			 DfsVisit( matrizAdyacencia,nodos,ordenacion,i,time,ciclico,inicial);
		 }
	}
}
 void DfsVisit(Matriz & matrizAdyacencia, Nodo nodos[], int ordenacion [],int n,int &time,bool &ciclico,int & indexOrd) {
	 nodos[n].color = Gris;
	 time = time++;
	 nodos[n].i = time;
	 for (int i = 0; i < matrizAdyacencia.ocup; i++)
	 {
		 if (matrizAdyacencia.grafo[n][i] == 1) {
			 if (nodos[i].color == Blanco) {
				 nodos[i].padre = n;
				 DfsVisit(matrizAdyacencia, nodos,ordenacion, i, time, ciclico,indexOrd);
			 }
			 else if (nodos[i].color == Gris) {
				 //al llegar a un nodos gris quiere decir que existe un ciclo
				 ciclico = true;
			 }
		 }
	 }
	 nodos[n].color = Negro;
	 time = time++;
	 nodos[n].f = time;
	 ordenacion[indexOrd] = n;
	 indexOrd++;

}
 void DFSConexo(Matriz & matrizAdyacencia, Nodo  nodos[], int ordenado[]) {
	 int time = 0;
	 int tamano = matrizAdyacencia.ocup;
	 int ord[MAX_NODES];
	 bool ciclico = false;
	 //ponemos todos los nodos a blanco y su padre a -1
	 for (int i = 0; i < matrizAdyacencia.ocup; i++)
	 {
		 nodos[i].color = Blanco;
		 nodos[i].padre = -1;
	 }
	 int index;
	 int comp=0;
	 for (int i = 0; i < matrizAdyacencia.ocup; i++)
	 {
		  index = 0;
		  //tenemos que empezar por lo nodos que antes han sido puestos a negro segun el algortimo.
		 if (nodos[ordenado[i]].color == Blanco) {
			 DfsVisit(matrizAdyacencia, nodos, ord, ordenado[i], time, ciclico,index);
			 //nos muestra los nodos que pertenecen a cada componnente fuertemente conexa.
			 cout << "componente conexa numero"<<comp << endl;
			 for (int j = 0; j < index; j++)
			 {
				 cout << ord[j] << " ";
			 }
			 cout << endl;
			 comp++;
		 }
	 }
 }

 Matriz Traspuesta(Matriz & matrizAdyacencia) {
	 Matriz traspuesta;
	 traspuesta.ocup = matrizAdyacencia.ocup;
	 for (int i = 0; i < matrizAdyacencia.ocup; i++)
	 {
		 for (int j = 0; j < matrizAdyacencia.ocup; j++)
		 {
			 traspuesta.grafo[j][i] = matrizAdyacencia.grafo[i][j];
		 }
	 }
	 return traspuesta;
 }
// nos genera n casos aleatorios y nos lo guarda en pruebas para que lo ejecute el programa
 void generaAleatorio()
 {
	 srand(time(NULL));
	 ofstream pruebas;
	 pruebas.open("pruebas.txt");
	 for (int i = 15; i < 220; i =i+ 10)
	 {
		 pruebas << i << "\n";
		 for (int j = 0; j < i; j++) {
			 for (int k = 0; k < i; k++) {
				 if (j == k) { pruebas << 0; }
				 else { pruebas << rand() % 2; }

				 if (k < i) {
					 pruebas << " ";
				 }
			 }
			 pruebas << "\n";
		 }
	 }
	 pruebas << 'F';

	 pruebas.close();
 }
