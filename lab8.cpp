#include <iostream>
#include <vector>

// MOSTENIREA: (cea de peste se numeste supraclasa)
//	-permite extinderea functionalitatii unor clase deja existente, lasand in acelasi timp clasa initala nemodificata
//	-permite implementarea unor ierarhii de clase
//	-se pot face si cu structuri (clasa derivata o structura sau clasa de baza o strucutraa)
//	
//	Clasa derivata mosteneste tot ce are clasa de baza(atr. si met.) - nu are neaparat si acces (protected)
//	Si mostenirea poate fi publica privata sau protected
//	
// 
// CONVERSII IMPLICITE INTRE CLASE DE BAZA SI CLASE DERIVATE
// 
// 
//

class Personaj
{
public:

protected:
	std::string nume;
	int viata;

public:
	Personaj(std::string nume = "", int viata = 0) : nume(nume), viata(viata)
	{
		std::cout << "apel clasa de baza\n";
	}
	void setNume(std::string nume) {
		this->nume = nume;
	}
	std::string getNume() {
		return this->nume;
	}
	void afisare() {
		std::cout << nume << viata;
	}
};

class Vrajitor : public Personaj  //modul in care sunt reprezentati membrii din personaj
{
public:
	
	Vrajitor(std::string nume, int viata, int magie) : Personaj(nume,viata), magie(magie){ // asa nu sunt goale initial apoi suprascrise, se face direct
		//this->nume = nume; //prima data "" apoi nume
		//this->viata = viata; //prima data 0 apoi viata
		//this->magie = magie;

		std::cout << "apel clasa derivata\n";
		
	}

	void afisare() {
		Personaj::afisare(); //apelare functii
		std::cout << magie << "\n";
	}
private:
	int magie;
};

class Varcolac : public Personaj
{
public:
	Varcolac(std::string nume, int viata, int putere) : Personaj(nume, viata), putere(putere){}

	

private:
	int putere;
};



int main() {
	Personaj p("varcolac", 20);
	Personaj* pp = &p;

	Vrajitor vr("merlin", 200, 120);
	Vrajitor* pvr = &vr;
	vr.afisare();

	Varcolac varcolac("Mario", 100, 200);


	//conversii implicite intre obiecte
	p = vr; //slice-ing 
	//vr = p; - nu se poate face

	//conversii implicite intre pointeri
	pp = pvr;
	//pvr = pp; - nu se poate face pentru ca pvr vede prea mult in memorie
	pp->afisare();

	//diferenta fata de atribuirea la nivel de obiete este ca nu se face slice-ing ; informatia exista in memorie


	//putem retine entitati de tip Varcolac si vrajitor (mai multe)

	std::vector<Personaj> personaje; //rau
	personaje.push_back(varcolac);
	personaje.push_back(vr);

	std::vector<Personaj*> adr_personaje; //bun - nu taie, nu modifica informatia
	adr_personaje.push_back(&varcolac);
	adr_personaje.push_back(&vr);
	return 0;
}