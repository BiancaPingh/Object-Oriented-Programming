#include <iostream>


// Constructori. Destructori. Clase cu alocare dinamica 
// Sa scriem o clasa in c++ care sa replice comportamentul clsei std::vector si in care vectorul sa fie alocat dinamic.
// Sa se sccrie in clasa:
//	a) constructori  + constr de copiere
//	b) destructorul
//	c) size()
//	d) push_back()
//	e) at() // supraincarcare []
//	f) supraincarcare op =
// 
// 
// Constructorul de copiere se foloseste cand se fac copii ale obj. 
//		vector v =v1;   vector v(v1); 
//	+ la transmiterea param prin valoare sau la returnarea obiectelor din functii din valoare.
//
// po = si constr de copiere daca nu sunt gasite se fac automat si fac SHALLOW COPY (copierea bit cu bit a info dint un loc in altu)
// 
// In clasele cu alocare dinamica trebuie scris:
//	destructor
//	contructor de copiere	| -> au rol de a face o copie DEEP COPY
//	supraincarcare pt =		|
//


class vector
{
public:
	vector() {
		this->elem = new int[1];
		this->capacitate = 1;
		this->dim = 0;
	}
	vector(size_t dim) {
		if (dim > 0) {
			this->elem = new int[2 * dim];
		}
		else {
			this->elem = nullptr;
		}
		this->dim = dim;
		this->capacitate = 2 * dim;
		
	}

	vector(vector& v) { //pt a oprii eroarea de copiere
		elem = new int[v.capacitate];
		dim = v.dim;
		capacitate = v.capacitate;
		for (int i = 0;i < dim;i++)
			elem[i] = v.elem[i];
	}

	~vector() {
		delete[] this->elem;
	}

private:
	int* elem;
	size_t dim, capacitate;

	void realocare(size_t capacitate) {
		int* nou = new int[capacitate];
		for (int i = 0;i < this->dim;i++) {
			nou[i] = elem[i];
		}
		delete[] elem;
		elem = nou;
		this->capacitate = capacitate;
	}

public:
	size_t size() {
		return this->dim;
	}
	void push_back(int key) {
		if (this->dim == this->capacitate) {
			realocare(this->capacitate * 2);
		}
		elem[this->dim++] = key;
	}
	int at(int index) {
		if (index > 0 && index < dim)
			return elem[index];
		throw std::out_of_range("index in afara limitelor");
	}

	int& operator [](int index) {
		if (index >= 0 && index < dim)
			return elem[index];
		throw std::out_of_range("index in afara limitelor");

	}

	vector& operator =(vector v) {
		if (this != &v) { //nu e acelasi obiect
			delete[] elem;
			elem = new int[v.capacitate];
			dim = v.dim;
			capacitate = v.capacitate;
			for (int i = 0;i < dim;i++)
				elem[i] = v.elem[i];
		}
		return *this;
	}
	void resize(size_t size, int val=0) {
		if (size > this->capacitate) {
			realocare(size);
			for (int i = this->dim;i < size;i++) {
				elem[i] = 0;
			}
			this->dim = size;
		}
		else {
			this->dim = size;
			realocare(size);
		}
	}
	void afisare() {
		for (int i = 0;i < this->dim;i++) {
			std::cout << elem[i] << " ";
		}
		std::cout << std::endl;
	}
};

void copiere(vector v) { //eroare din cauza destructorului
	vector v1;
	v1 = v;

	return;
}

int main() {
	vector v(3), v2;

	v2.push_back(1);
	v2.push_back(3);
	v2.push_back(2);
	v2.push_back(4);
	v2.afisare();

	//v.push_back(1);
	//v.afisare();

	copiere(v2); 
	v2.resize(10);
	std::cout << v2.size() << std::endl;
	v2.afisare();

	return 0;
}