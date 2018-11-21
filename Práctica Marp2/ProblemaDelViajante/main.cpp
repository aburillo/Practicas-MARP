//Adrian Burillo Elmaleh El problema del viajante
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <queue>
#include <vector>
#include <queue>
#include "NodoyMatriz.cpp"
float NodosCreados = 0;
float NodosExpandidos = 0;
using namespace std;
typedef struct {
	int ocup;
	vector<AristaValor> * grafo[50];
}Matriz;
bool existeArista(Matriz &m, Nodo &x, int ini, int &costeMejor);
void RamificacionyPodaAjustada(Matriz & m, int NodoIni, int  solMejor[], int &costeMejor);
void RamificacionYPodaIngenua(Matriz & m, int NodoIni, int  solMejor[], int &costeMejor);
void RamificacionYPodaSinCota(Matriz & m, int NodoIni, int  solMejor[], int &costeMejor);
float EstimaCoste2(Matriz & m, int cr,int max, bool usados[], int minF[]);
void generaAleatorio();
float EstimaCoste(Matriz & m, int min, int max,int cr, int k);
int minMatriz(Matriz & m,int &max);
void minFila(Matriz & m, int minimos[],int &max);
int main() {
	char n;
	int nodoIni;
	int coste;
	clock_t ini = 0;
	clock_t fin = 0;
	double sec;
	int sol[50];
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
	file.open("pruebas2.txt");
	char c;
	char v;
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
			m.grafo[i] = new vector<AristaValor>();
			for (int j = 0; j < m.ocup; j++) {
				file >> c;
				file >> v;
				if (c == '1') {
					
					m.grafo[i]->push_back( AristaValor(j,v-48));
				}
			}
		}

		for (int i = 0; i < m.ocup; i++)
		{
			cout << i<<" ";
			for (int j = 0; j < m.grafo[i]->size(); j++)
			{
				cout <<m.grafo[i]->at(j).getoNodo()<<" "<< m.grafo[i]->at(j).getValor();
			}
			cout << endl;
		}
		cout << "En que nodo desea empezar?" << endl;
		cin >> nodoIni;
		//tiempo antes de ejecutar el algortimo con poda Ajustada
		ini = ini + clock();
		cout << "ALGORITMO CON PODA AJUSTADA" << endl;
		//cuerpo principal del programa donde se aplica todo
		RamificacionyPodaAjustada(m,nodoIni,sol,coste);
		//Nos muestra la solucion si existe, si nos nos dice que no hay solucion
		if (coste != 9999) {//uso 9999 en mi programa como si fuese una cota superior mas infinito
			cout << "Solucion ";
			for (int i = 0; i <m.ocup + 1; i++)
			{
				cout << sol[i] << " -> ";
			}
			cout << endl;
			cout << "costeReal "<<coste << endl;
		}
		else cout << "No tiene solucion" << endl;
		//tiempo que ha tardado el programa
		fin = fin + clock();
		sec = (double)(fin - ini) / CLOCKS_PER_SEC;
		cout << "El programa ha tardado " << sec << " segundos" << endl;
		cout << "Ha Creado " << NodosCreados << " nodos" << endl;
		cout << "Ha Expandido " << NodosExpandidos << " nodos" << endl;
		cout << "El tiempo medio(tiempo/nodos)" << sec / NodosCreados << endl;
		
		//tiempo antes de ejecutar el algortimo con poda ingenua
		ini = ini + clock();
		cout << "ALGORITMO CON PODA INGENUA" << endl;
		//cuerpo principal del programa donde se aplica todo
		RamificacionYPodaIngenua(m, nodoIni, sol, coste);
		//Nos muestra la solucion si existe, si nos nos dice que no hay solucion
		if (coste != 9999) {//uso 9999 en mi programa como si fuese una cota superior mas infinito
			cout << "Solucion ";
			for (int i = 0; i <m.ocup + 1; i++)
			{
				cout << sol[i] << " -> ";
			}
			cout << endl;
			cout <<"CosteReal" << coste << endl;
		}
		else cout << "No tiene solucion" << endl;
		//tiempo que ha tardado el programa
		fin = fin + clock();
		sec = (double)(fin - ini) / CLOCKS_PER_SEC;
		cout << "El programa ha tardado " << sec << " segundos" << endl;
		cout << "Ha Creado " << NodosCreados << " nodos" << endl;
		cout << "Ha Expandido " << NodosExpandidos << " nodos" << endl;
		cout << "El tiempo medio(tiempo/nodos)" << sec / NodosCreados << endl;
		
		//tiempo antes de ejecutar el algortimo sin poda
		ini = ini + clock();
		cout << "ALGORITMO SIN PODA" << endl;
		//cuerpo principal del programa donde se aplica todo
		RamificacionYPodaSinCota(m, nodoIni, sol, coste);
		//Nos muestra la solucion si existe, si nos nos dice que no hay solucion
		if (coste != 9999) {//uso 9999 en mi programa como si fuese una cota superior mas infinito
			cout << "Solucion ";
			for (int i = 0; i <m.ocup + 1; i++)
			{
				cout << sol[i] << " -> ";
			}
			cout << endl;
			cout <<"costeReal"<< coste << endl;
		}
		else cout << "No tiene solucion" << endl;
		//tiempo que ha tardado el programa
		fin = fin + clock();
		sec = (double)(fin - ini) / CLOCKS_PER_SEC;
		cout << "El programa ha tardado " << sec << " segundos" << endl;
		cout << "Ha Creado " << NodosCreados << " nodos" << endl;
		cout << "Ha Expandido " << NodosExpandidos << " nodos" << endl;
		cout << "El tiempo medio(tiempo/nodos)" << sec / NodosCreados << endl;
		file >> c;

	}

	file.close();
	//nos guarda en un archivo grafica, el tiempo respecto de los nodos
	//tiempo(tiempos, nodes, cont);
	system("pause");
	return 0;
}
	// nos genera n casos aleatorios y nos lo guarda en pruebas.txt para que lo ejecute el programa,todo lo que crea tiene solucion ya que es un grafo completo
	void generaAleatorio() {
		srand(time(NULL));
		ofstream pruebas;
		pruebas.open("pruebas.txt");
		int aux;
		for (int i = 5; i < 15; i = i + 1)
		{
			pruebas << i << "\n";
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < i; k++) {
					//if (k !=0) {
						//pruebas << " ";
					//}
					if (j == k) { 
						pruebas << 0;
						pruebas << " ";
						pruebas << 0;
					}

					else {
						aux = 1;
						pruebas << 1;
						pruebas << " ";
						if (aux == 1) { pruebas << (rand() % 5)+1; }
						else pruebas <<0;
					}

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
	void RamificacionyPodaAjustada(Matriz & m, int NodoIni,int  solMejor[],int &costeMejor) {
		Nodo raiz(m.ocup, NodoIni);
		NodosCreados=1;
		NodosExpandidos = 0;

		Nodo y;
		priority_queue<Nodo> cola;
		int aux;
		int max;
		//int min = minMatriz(m);
		int minF[20];
		minFila(m, minF,max);
		costeMejor = 9999;
		//raiz.setCosteEstimado(EstimaCoste(m, min, raiz.getCosteReal(), raiz.getK()));
		raiz.setCosteEstimado(EstimaCoste2(m, raiz.getCosteReal(), max,raiz.usadoArray(), minF));
		cola.push(raiz);
		while (!cola.empty() && cola.top().getCosteEstimado() < costeMejor) {
			  y = cola.top();
			  NodosExpandidos++;
			cola.pop();
			for (int i = 0; i < m.grafo[y.lastCiudad()]->size(); i++)
			{
				if (!y.usado(m.grafo[y.lastCiudad()]->at(i).getoNodo())) {//Solo escojo nodos que no esten en usados, por eso evito repeticiones
					//Para cada nodo hijo no usado, lo creo estimo su costeestimado, actualizo k y le doy su coste Real!
					Nodo x(y);
				NodosCreados++;
					x.meteCiudad(m.grafo[y.lastCiudad()]->at(i).getoNodo());
					x.setCosteReal(m.grafo[y.lastCiudad()]->at(i).getValor());
					//x.setCosteEstimado(EstimaCoste(m, min, raiz.getCosteReal(), raiz.getK()));
					raiz.setCosteEstimado(EstimaCoste2(m, raiz.getCosteReal(),max, raiz.usadoArray(), minF));
					//De cada nodo hijo si su coste estimado es mejor que el CosteMejor
					if (x.getCosteEstimado() < costeMejor) {
						//si ya he usado todos los nodos, miro si exxiste arista entre el ultimo nodo y el inicial y si es coste Real es mejor que el Costemejor
						//lo actualizo
						if (x.getK() == m.ocup) {//si es solucion
							aux = costeMejor;
							if (existeArista(m, x, NodoIni, costeMejor) && (aux!=costeMejor)) {
								for (int i = 0; i < m.ocup; i++)
								{
									solMejor[i] = x.getKesimo(i);
								}
								solMejor[m.ocup] = x.getKesimo(0);
							}
						}
							else {
								//si todavia no es solucion pues lo meto en la cola de prioridad
								cola.push(x);
							
							
							}
						}

					}

				}



			}


		}
	//Algoritmo que usa la cota ingenua, que es la cota del minimo de la matriz
	void RamificacionYPodaIngenua(Matriz & m, int NodoIni, int  solMejor[], int &costeMejor) {
	
		Nodo raiz(m.ocup, NodoIni);
		NodosCreados = 1;
		NodosExpandidos = 0;

		Nodo y;
		priority_queue<Nodo> cola;
		int aux;
		int max;
		int min = minMatriz(m,max);
		costeMejor = 9999;
		raiz.setCosteEstimado(EstimaCoste(m, min, max,raiz.getCosteReal(), raiz.getK()));		
		cola.push(raiz);
		while (!cola.empty() && cola.top().getCosteEstimado() < costeMejor) {
			y = cola.top();
			NodosExpandidos++;
			cola.pop();
			for (int i = 0; i < m.grafo[y.lastCiudad()]->size(); i++)
			{
				if (!y.usado(m.grafo[y.lastCiudad()]->at(i).getoNodo())) {//Solo escojo nodos que no esten en usados, por eso evito repeticiones
																		  //Para cada nodo hijo no usado, lo creo estimo su costeestimado, actualizo k y le doy su coste Real!
					Nodo x(y);
					NodosCreados++;
					x.meteCiudad(m.grafo[y.lastCiudad()]->at(i).getoNodo());
					x.setCosteReal(m.grafo[y.lastCiudad()]->at(i).getValor());
					x.setCosteEstimado(EstimaCoste(m, min,max, raiz.getCosteReal(), raiz.getK()));
					//De cada nodo hijo si su coste estimado es mejor que el CosteMejor
					if (x.getCosteEstimado() < costeMejor) {
						//si ya he usado todos los nodos, miro si exxiste arista entre el ultimo nodo y el inicial y si es coste Real es mejor que el Costemejor
						//lo actualizo
						if (x.getK() == m.ocup) {//si es solucion
							aux = costeMejor;
							if (existeArista(m, x, NodoIni, costeMejor) && (aux != costeMejor)) {
								for (int i = 0; i < m.ocup; i++)
								{
									solMejor[i] = x.getKesimo(i);
								}
								solMejor[m.ocup] = x.getKesimo(0);
							}
						}
						else {
							//si todavia no es solucion pues lo meto en la cola de prioridad
							cola.push(x);

						}
					}

				}

			}



		}
	
	}
	void RamificacionYPodaSinCota(Matriz & m, int NodoIni, int  solMejor[], int &costeMejor) {
		Nodo raiz(m.ocup, NodoIni);
		NodosCreados = 1;
		NodosExpandidos = 0;
		Nodo y;
		priority_queue<Nodo> cola;
		int aux;
		costeMejor = 9999;
		cola.push(raiz);
		while (!cola.empty()) {
			y = cola.top();
			NodosExpandidos++;
			cola.pop();
			for (int i = 0; i < m.grafo[y.lastCiudad()]->size(); i++)
			{
				if (!y.usado(m.grafo[y.lastCiudad()]->at(i).getoNodo())) {//Solo escojo nodos que no esten en usados, por eso evito repeticiones
																		  //Para cada nodo hijo no usado, lo creo estimo su costeestimado, actualizo k y le doy su coste Real!
					Nodo x(y);
					NodosCreados++;
					x.meteCiudad(m.grafo[y.lastCiudad()]->at(i).getoNodo());
					x.setCosteReal(m.grafo[y.lastCiudad()]->at(i).getValor());
						//si ya he usado todos los nodos, miro si exxiste arista entre el ultimo nodo y el inicial y si es coste Real es mejor que el Costemejor
						//lo actualizo
						if (x.getK() == m.ocup) {//si es solucion
							aux = costeMejor;
							if (existeArista(m, x, NodoIni, costeMejor) && (aux != costeMejor)) {
								for (int i = 0; i < m.ocup; i++)
								{
									solMejor[i] = x.getKesimo(i);
								}
								solMejor[m.ocup] = x.getKesimo(0);
							}
						}
						else {
							//si todavia no es solucion pues lo meto en la cola de prioridad
							cola.push(x);

					}

				}

			}



		}

	
	}
	
	//Una costa optimista(ingenua) que devuelve el coste Real mas la minima arista de la matriz por los nodos que me quedan por anadir + 1(por que tengo que tener una arista al nodo inicial)
	float EstimaCoste(Matriz & m,int min,int max,int cr,int k) {
		return cr + (m.ocup - k + 1) * ((min + max)/2);
	
	}
	//Otra costa optimista, en este caso devuelvo el coste real mas el minimo de cada nodo que no he usado, y le sumo el minimo global como si fuese la arista
	// que conecta el ultimo nodo con el primero
	float EstimaCoste2(Matriz & m, int cr,int max, bool usados[],int minF[]) {
		float c2=cr;
		int min=9999;
		for (int i = 0; i < m.ocup; i++)
		{
			if (usados[i] == false) {
				if (minF[i] < min) {
					min = minF[i];
				}
				c2 = c2 + (minF[i]+max)/2;
			}

		}
		return c2 + (min+max)/2;
	}
	//calculo el minimo de la matriz
	int minMatriz(Matriz & m,int &max) {
		int min = 100;
		max = 0;
		for (int i = 0; i < m.ocup; i++)
		{
			for (int j = 0; j < m.grafo[i]->size(); j++) 
			{
				if (m.grafo[i]->at(j).getValor() != 0 &&
					m.grafo[i]->at(j).getValor() < min) {
					min = m.grafo[i]->at(j).getValor();
				}
				if (m.grafo[i]->at(j).getValor() > max) {
					max = m.grafo[i]->at(j).getValor();
				}
			}
		}
		return min;
	}
	//calculo el minimo por filas
	void minFila(Matriz & m,int minimos[],int &max) {
		int min;
		max = 0;
		for (int i = 0; i < m.ocup; i++)
		{
			min = 9999;
			for (int j = 0; j < m.grafo[i]->size();j++) {
				if (m.grafo[i]->at(j).getValor() < min) {
					min = m.grafo[i]->at(j).getValor();
				}
				if (m.grafo[i]->at(j).getValor() > max) {
					max = m.grafo[i]->at(j).getValor();
				}
			}
			minimos[i] = min;
		}
	
	}
	//nos dice si existe una aritaa entre el ultimo nodo y el nodo donde ha empezado el algortimo
	bool existeArista(Matriz &m,Nodo &x,int ini,int &costeMejor) {
		bool si = false;
		for (int i = 0; i < m.grafo[x.lastCiudad()]->size(); i++)
		{
			if (m.grafo[x.lastCiudad()]->at(i).getoNodo() == ini) {
				si = true;
				if (x.getCosteReal() + m.grafo[x.lastCiudad()]->at(i).getValor() < costeMejor) {
					costeMejor = x.getCosteReal() + m.grafo[x.lastCiudad()]->at(i).getValor();
				}
			}
		}
		return si;
	}
