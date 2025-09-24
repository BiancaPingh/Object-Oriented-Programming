//mostenire multipla
//	de ce e rau: de ex am functii de afisare la ambele clase de baza, sau un membru cu acelasi nume
//	trebuie specificat explicit(ex c.A::afisare() ->A e una din clasele de baza)
// 
// probleme si mai mari: problema diamantului (schema e mai complexa, o diagrama care se inchide - au acelasi obiect la baza) apare partea bazei comune de 
// mai multe ori in memorie(ABACE - a de baza, b si c bazele lui e)
//	se rezolva facand A virtual in momentul in care pun : class B : virtual public A (si la C)
// 
// ca sa nu se cheme constructorii de 2 ori: cand A e virtual, atunci e CAZ UNIC unde E poate sa cheme constructorul lui A 
// 
// alternative: 1. compozitia
// compozitie vs mostenire:
//	compozitia, o clasa cu un obiect din alta clasa - nu are suport la polimorfism
//	mostenirea, o clasa imbogatita de alta clasa
// 
//	2. folosirea interfetelor pure
//		interfata pura: (in c++ nu exista interfata) o clasa unde nu avem atribute, ci doar metode virtuale		
//

#include <iostream>
#include <string>
#include <vector>

class Angajat
{
public:
	Angajat(std::string nume, std::string mail, double salariuBaza) : nume(nume), mail(mail),salariuBaza(salariuBaza) {}
	virtual ~Angajat() {
		
	}

	void afiseazaDetalii() {
		std::cout << "Nume: " << nume << " mail: " << mail << " salariu de baza: " << salariuBaza;
	}
	virtual double calculeazaSalariu() { return salariuBaza; }
	std::string getNume() {
		return nume;
	}

private:
	std::string nume, mail;
	double salariuBaza;
};
class TeamLeader
{
public:
	TeamLeader(int nrSubordonati, double bonusConducere) : nrSubordonati(nrSubordonati), bonusConducere(bonusConducere) {}
	virtual ~TeamLeader() {}
	void organizeazaIntalnire(std::string tema) {
		std::cout << "Organizează o întâlnire cu tema "<< tema <<" pentru "<< nrSubordonati << "participanți.";
	}
	double calculeazaBonus() {
		return bonusConducere * nrSubordonati;
	}
	void adaugaMembru(std::string numeMembru) {
		echipaProiect.push_back(numeMembru);
		std::cout << numeMembru << "a fost adăugat în echipă.";
		nrSubordonati++;
	}
	void evaluareEchipa() {
		for (auto ang : echipaProiect) {
			std::cout << ang << " performanta: "<<std::endl;
		}
	}

private:
	int nrSubordonati=0;
	double bonusConducere;
	std::vector<std::string> echipaProiect;
};

class Specialist
{
public:
	Specialist(std::string specializare, int aniExperienta, double bonusTehnic) : specializare(specializare), aniExperienta(aniExperienta), bonusTehnic(bonusTehnic) {}
	virtual ~Specialist() {}

	void  rezolvaProblema(std::string descriereProblema) {
		std::cout << "Rezolvă problema " << descriereProblema << " folosind cunoștințe de " << specializare << " acumulate în " << aniExperienta << " ani." << std::endl;

	}
	double calculeazaBonus() {
		return bonusTehnic * aniExperienta;
	}
	void adaugaCertificare(std::string numeCertificare) {
		certificari.push_back(numeCertificare);
		std::cout << "Certificare obținută: " << numeCertificare<<std::endl;

	}
	void participaTraining(std::string numeTraining){
		std::cout << "Participă la trainingul " << numeTraining << "pentru a - și îmbunătăți cunoștințele de" << specializare << std::endl;

	}
	void afiseazaCertificari() {
		std::cout << "Certificari:";
		for (auto certificare : certificari) {
			std::cout << " - " << certificare;
		}
	}

protected:
	std::string specializare;
	int aniExperienta;
	double bonusTehnic;
	std::vector<std::string> certificari;
};

class ManagerTehnic: virtual public Angajat, public TeamLeader, public Specialist
{
public:
	ManagerTehnic(std::string nume, std::string mail, double salariuBaza, int nrSubordonati, double bonusConducere, std::string specializare, int aniExperienta, double bonusTehnic) : Angajat(nume,mail,salariuBaza), TeamLeader(nrSubordonati,bonusConducere), Specialist(specializare,aniExperienta,bonusTehnic) {}
	~ManagerTehnic() {}
	void afiseazaDetalii() {

	}
	double calculeazaSalariu() {
		return salariuBaza + TeamLeader::calculeazaBonus() + Specialist::calculeazaBonus();
	}
	void coordoneazaProiect(std::string numeProiect) {
		std::cout << "Managerul tehnic" << nume << "coordonează proiectul" << numeProiect << "folosind expertiza în" << specializare << std::endl;

	}
	void aprobareSolutie(std::string solutie, bool aprobat) {
		if (aprobat) {
			std::cout << "Soluția tehnică " << solutie << " a fost aprobată. \n";
		}
		else
			std::cout << "Soluția tehnică " << solutie << " nu a fost aprobată. \n";
	}

private:
	std::string nume, mail; double salariuBaza; int nrSubordonati; double bonusConducere; std::string specializare; int aniExperient; double bonusTehnic;
};

class DeveloperSenior : virtual public Angajat, public Specialist
{
public:
	DeveloperSenior(std::string nume, std::string mail, double salariuBaza, std::string specializare, int aniExperienta, double bonusTehnic, std::string limbajPrincipal, std::vector<std::string> proiecteFinalizate) : Angajat(nume, mail, salariuBaza), Specialist(specializare, aniExperienta, bonusTehnic), limbajPrincipal(limbajPrincipal), proiecteFinalizate(proiecteFinalizate) {}
	~DeveloperSenior() {}

	void afisareDetalii() {
		std::cout << "afisare detalii developersenior";
	}
	double calculeazaSalariul() {
		return salariuBaza + Specialist::calculeazaBonus();
	}
	void scrieCod(std::string functionalitate) {
		std::cout << "Dezvoltatorul" << nume << " implementează " << functionalitate << " folosind " << limbajPrincipal;
	}
	void adaugaProiect(std::string numeProiect) {

	}
	void codeReview() {

	}
	void afiseazaProiecte() {

	}

private:
	std::string limbajPrincipal;
	std::vector<std::string> proiecteFinalizate;
	std::string nume, mail; double salariuBaza; std::string specializare; int aniExperienta; double bonusTehnic;
};

class ManagerProiect
{
public:
	ManagerProiect();
	~ManagerProiect();

private:

};

int main() {
	std::vector<Angajat*> angajati;
	//audauga toate tipurile
	DeveloperSenior dv("Ion", "mail", 10, "C++", 4, 30, "Py", { "1","2" });

	angajati.push_back(&dv);
	double sal_max = 0;
	Angajat* ang_sal_max = nullptr;
	for (auto angajat : angajati) {
		double sal = angajat->calculeazaSalariu();
		std::cout << sal;
		if (sal_max < sal) {
			sal_max = sal;
			ang_sal_max = angajat; //adresa ang cu salariu maxim
		}

	}//cum imi dau seama ce functie e acest angajat?
	if (dynamic_cast<ManagerTehnic*>(ang_sal_max)) //pot sa convertesc?? atunci poiter valid, altfel nullptr
		std::cout << "manager tehnic";
	else if (dynamic_cast<ManagerProiect*>(ang_sal_max)) //nu se poate folosi daca clasa de baza nu are o clasa virtuala (se pune si destructorul)
		std::cout << "manager proiect";
	else if (dynamic_cast<DeveloperSenior*>(ang_sal_max))
		std::cout << "developer senior";
	return 0;
}