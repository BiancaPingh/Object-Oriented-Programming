#include <iostream>

using namespace std;

//el clasei sunt in mod implicit private (nu am acces in afara clasei)
// accesul la atributele clasei este permis prin intermediul metodelor clasei
// 
// 
//mofidicatori de acces: cuv vheie -> se specifica nivelul de acces la membrul clasei
// 3 tipuri: private(interiorul clasei), public(oricine are acces), protected(nu am acces din afara clasei; am acccees numai in 
// clasa sau clasele derivate din ea
// 
// 
//contructori: sunt metode care se apeleaza atunci cand se creaza ob. de tipul clasei/structurii 
// contructorii trebuie sa aiba ACELASI NUME ca si clasa/struct
//			si NU AU TIP RETURNAT nici macar void
//	rolul lor este de a initializa atrib. clasei cand se creaza obiectul
//	daca nu se scrie  in mod explicit contructorul -> compilatorul il face default (fara parametrii)
//	pot exista in aceeasi clasa mai multi contructori
//

class ContBancar {
private:
	string detinator,moneda;
	double suma;

public:
	ContBancar() {
		detinator = "-";
		moneda = "ron";
		suma = 0;
	}
	ContBancar(string detinator, string moneda) {
		this->detinator = detinator;
		this->moneda = moneda;
		suma = 0;
	}
	ContBancar(string detinator, string moneda, double suma){
		this->detinator = detinator;
		this->moneda = moneda;
		if (suma >= 0)
			this->suma = suma;
		else
			this->suma = 0;
	}
	//metode de tip set (setter)
	void set_detinator(string detinator) {
		this->detinator = detinator;
	}
	void set_moneda(string moneda) {
		this->moneda = moneda;
	}
	void set_suma(double suma) {
		if (suma >= 0) 
			this->suma = suma;
	}
	//metode care permit afisarea val atr ->getters
	double get_suma() {
		return this->suma;
	}
	string get_detinator() {
		return this->detinator;
	}
	string get_moneda() {
		return this->moneda;
	}
	void afisare_delatii() {
		cout << detinator << ": " << suma << " " << moneda<<endl;
	}
};

int main() {

	ContBancar c("Andrei Popescu", "ron");
	c.set_suma(200);
	cout<<c.get_suma();
	c.afisare_delatii();

	//contructor de copiere - se apeleaza cand initial. un obiect cu inf din alt obiect
	//generat implicit; cand un obiect e creat si initializat cu atributele unui alt obiect specificat ca parametru
	//face copiere bit cu bit a informatiei din obiectul existent in cel nou
	ContBancar c1(c);
	c.afisare_delatii();
	return 0;
}