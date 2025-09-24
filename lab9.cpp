#include <iostream>
#include <vector>
#include <tuple>

//sa se creeze un set de angajati care sa fie retinuti intr un singur continer
//sa se traverseze containerul si sa se afiseze descrierea angajatilor si sa se afiseze bonusul pe care il are fiecare
//sa se traverseze cointainerul si sa se elibereze zona de memorie coresp fiecarui angajat
//


class Angajat
{
protected:
	std::string CNP, nume, prenume;
	std::tuple<int, int, int> dataN;
	double salariu;


public:
	Angajat(std::string CNP = "", std::string nume = "", std::string prenume = "", std::tuple<int, int, int> dataN = {0,0,0}, double salariu = 0) : CNP(CNP), nume(nume),
		prenume(prenume), dataN(dataN), salariu(salariu){}
	~Angajat() {
		std::cout << "destructor";
	}

	virtual void descriere() {
		std::cout << nume << " " << prenume << " CNP: " << CNP << " salariu: " << salariu << " data nasterii: " << std::get<0>(dataN) << "." << std::get<1>(dataN) << "." << std::get<2>(dataN)<<'\n';
	}
	
	virtual double calculeazaBonus() { //virtual pointer reuseste sa faca legatura cu metoda corecta (cea din programator) - polimorfism
		return 0;
	}
};

class ProjectOwner : Angajat
{
public:
	ProjectOwner(std::string proiect="", std::string CNP = "", std::string nume = "", std::string prenume = "", std::tuple<int, int, int> dataN = {0,0,0}, double salariu = 0) : Angajat(CNP,nume, prenume,dataN,salariu), proiect(proiect) {}
	~ProjectOwner() {
		std::cout << "destructor pjOwn";
	}
	void descriere() {
		Angajat::descriere();
		std::cout << "Proiectul" << proiect<<std::endl;
	}

	double calculeazaBonus() {
		return (15.0 / 100.0) * salariu;
	}

private:
	std::string proiect;
	
};


class Programator : Angajat
{
public:
	Programator(std::string nivel = "", std::string CNP = "", std::string nume = "", std::string prenume = "", std::tuple<int, int, int> dataN = { 0,0,0 }, double salariu = 0) : Angajat(CNP, nume, prenume, dataN, salariu), nivel(nivel) {}
	~Programator() {
		std::cout << "destructor programator";
	}
	void descriere() {
		Angajat::descriere();
		std::cout << "Nivelul programatorului: " << nivel<<std::endl;
	}
	double calculeazaBonus() {
		if (nivel == "Senior" || nivel == "Expert")
			return (10.0 / 100.0) * salariu;
	}

private:
	std::string nivel;

};

class Tester : Angajat
{
public:
	Tester(std::string tipTest = "", std::string CNP = "", std::string nume = "", std::string prenume = "", std::tuple<int, int, int> dataN = { 0,0,0 }, double salariu = 0) : Angajat(CNP, nume, prenume, dataN, salariu), tipTest(tipTest) {}
	~Tester() {
		std::cout << "destructor tester";
	}
	void descriere() {
		Angajat::descriere();
		std::cout << "Tipul de test efectuat: " << tipTest<<std::endl;
	}
	double calculeazaBonus() {
		if (tipTest == "automat")
			return  (5.0 / 100.0) * salariu;
		return 0;
	}

private:
	std::string tipTest;

};



int main() {
	std::vector<Angajat*> ang;
	ang.push_back(new Programator("Senior", "834232", "Ion", "Popescu", { 21,32,43 }, 4000));

	return 0;
}