
class Nodo
{
public:
	Nodo() {}
	Nodo(int tamano, int ciu)
	{
		this->tam = tamano;
		sol[0] = ciu;
		for (int i = 0; i < this->tam; i++)
		{
			used[i] = false;
		}
		used[ciu] = true;
		k = 1;
		this->costeReal = 0;

	}
	Nodo(const Nodo& unNodo) {
		this->k = unNodo.k;
		this->costeReal = unNodo.costeReal;
		this->tam = unNodo.tam;
		this->costeEstimado = unNodo.costeEstimado;
		for (int i = 0; i < this->tam; i++)
		{
			if (i < k) {
				this->sol[i] = unNodo.sol[i];
			}
			this->used[i] = unNodo.used[i];
		}

	}
	~Nodo() {}
	bool operator<(const Nodo& otro) const {
		//return this->costeReal > otro.costeReal;
		return otro.costeReal <this->costeReal;
	}
	void setCosteEstimado(float ce) {
		this->costeEstimado = ce;
	}
	int getCosteReal() {
		return this->costeReal;
	}
	bool* usadoArray(){
		return this->used;
	}
	int getK() {
		return this->k;
	}
	float getCosteEstimado() const {
		return this->costeEstimado;
	}
	int lastCiudad() {
		return this->sol[this->k - 1];
	}
	bool usado(int n) {
		return used[n];
	}

	void meteCiudad(int ciudad) {
		this->used[ciudad] = true;
		this->sol[this->k] = ciudad;
		this->k++;
	}
	void setCosteReal(int coste) {
		this->costeReal = this->costeReal + coste;

	}
	float getCosteEstimado() {
		return this->costeEstimado;
	}
	int getKesimo(int n) {
		return this->sol[n];
	}

private:
	int tam;
	int sol[20];
	bool used[20];
	int k;
	float costeReal;
	float costeEstimado;

};


class AristaValor
{
public:
	AristaValor(int onodo, int value)
	{
		this->oNodo = onodo;
		this->valor = value;
	}
	~AristaValor() {}
	int getoNodo() {
		return this->oNodo;
	}
	int getValor(){
		return this->valor;
	}

private:
	int oNodo;
	int valor;
};


