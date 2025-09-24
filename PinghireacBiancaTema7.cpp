#include <iostream>
#include <string>
#include <list>
#include <vector>

class Carte
{
private:
	std::string titlu, autor, ISBN, editura, categorie, detalii;
	int an, pagini;
	bool status;
public:
	Carte(std::string titlu, std::string autor, int an, std::string editura, std::string categorie, int pagini) {
		this->titlu = titlu;
		this->autor = autor;
		this->editura = editura;
		this->categorie = categorie;
		this->pagini = pagini;
		this->detalii = "-";
		this->an = an;
		this->status = false;
		std::hash<std::string> cod;
		this->ISBN = cod(titlu + autor) % 100;
	}

	std::string getTitlu() {
		return this->titlu;
	}
	std::string getAutor() {
		return this->autor;
	}
	std::string getEditura() {
		return this->editura;
	}
	std::string getISBN() {
		return this->ISBN;
	}
	std::string getCategorie() {
		return this->categorie;
	}
	std::string getDetaliiPersoana() {
		return this->detalii;
	}
	bool getStatus() {
		return this->status;
	}
	int getAn() {
		return this->an;
	}
	int getPagini() {
		return this->pagini;
	}
	void imprumuta(std::string numePersoana, std::string dataImprumut) {
		this->status = true;
		this->detalii = numePersoana + " " + dataImprumut;
	}
	void returneaza() {
		this->status = false;
		this->detalii = "-";
	}
	void afiseazaDetalii() {
		std::cout << titlu << " " << autor << " " << editura << " " << categorie << " " << pagini << " " << detalii << " " << status << " " << "\n";
	}
	bool operator==(const Carte& other) const {
		return this->ISBN == other.ISBN;
	}

	friend std::ostream& operator <<(std::ostream& out, const Carte& nr) {
		out << nr.titlu << " " << nr.autor << " " << nr.editura << " " << nr.categorie << " " << nr.pagini << " " << nr.detalii << " " << nr.status << " " << "\n";
		out << "\n";
		return out;
	}
};

class Membru
{
private:
	int ID;
	std::string nume, adresa, telefon, email;
	std::list<Carte> cartiImprumutate;
public:
	Membru(int ID, std::string nume, std::string adresa, std::string telefon, std::string email) {
		this->ID = ID;
		this->nume = nume;
		this->adresa = adresa;
		this->telefon = telefon;
		this->email = email;
	}
	~Membru() {
		cartiImprumutate.clear();
	}

	int getId() {
		return this->ID;
	}
	std::string getNume() {
		return this->nume;
	}
	std::string getAdresa() {
		return this->adresa;
	}
	std::string getEmail() {
		return this->email;
	}
	std::string getTelefon() {
		return this->telefon;
	}
	std::list<Carte> getListaCarti() {
		return this->cartiImprumutate;
	}

	void setId(int id) {
		this->ID = id;
	}
	void setAdresa(std::string adresa) {
		this->adresa = adresa;
	}
	void setNume(std::string nume) {
		this->nume = nume;
	}
	void setEmail(std::string email) {
		this->email = email;
	}
	void setTelefon(std::string telefon) {
		this->telefon = telefon;
	}
	

	void imprumutaCarte(Carte* carte, const std::string& dataImprumut) {
		if (carte) {
			carte->imprumuta(nume, dataImprumut);
			cartiImprumutate.push_back(*carte);
		}
	}

	void returneazaCarte(Carte* carte) {
		if (carte) {
			carte->returneaza();
			cartiImprumutate.remove(*carte);
		}
	}
	void afiseazaCartiImprumutate() {
		for (const auto& carte : cartiImprumutate) {
			std::cout << carte << "\n";
		}
	}
	size_t getNumarCartiImprumutate() {
		return cartiImprumutate.size();
	}

	friend std::ostream& operator <<(std::ostream& out, const Membru& n) {
		out << n.ID<<n.nume << n.adresa << n.telefon<< n.email<< "\n";
		return out;
	}
};

class Rezervare
{
private:
	int ID;
	Membru* m;
	Carte* c;
	std::string dataRezervarii;
	bool status; //activ sau inactiv
public:
	Rezervare(int id, Membru* m, Carte* c, std::string dataRezervarii) {
		this->ID = id;
		this->m = m;
		this->c = c;
		this->dataRezervarii = dataRezervarii;
		this->status = true;
	}

	int getId() {
		return this->ID;
	}
	Membru* getMembru() {
		return this->m;
	}
	Carte* getCarte() {
		return this->c;
	}
	std::string getDataRezervare() {
		return this->dataRezervarii;
	}
	bool getStatus() {
		return this->status;
	}
	void anuleaza() {
		this->status = false;
		this->dataRezervarii = "-";
	}
	void proceseaza(std::string dataImprumut) {
		this->m->imprumutaCarte(this->c, dataImprumut);
	}
	bool getEsteActiva() {
		return this->status;
	}
	friend std::ostream& operator <<(std::ostream& out, const Rezervare& r) {
		out << "Rezervare ID: " << r.ID << ", Membru: " << r.m->getNume()
			<< ", Carte: " << r.c->getTitlu() << ", Data: " << r.dataRezervarii
			<< ", Status: " << (r.status ? "activa" : "inactiva") << "\n";
		return out;
	}
};

class Amenda
{
private:
	int ID;
	Membru* m;
	Carte* c;
	std::string motiv;
	double suma;
	bool status; //platita sau neplatita
public:
	Amenda(int ID, Membru* m, Carte* c, std::string motiv, double suma) {
		this->ID = ID;
		this->m = m;
		this->c = c;
		this->motiv = motiv;
		this->suma = suma;
		status = false;
	}

	int getId() { return this->ID; }
	Membru* getMembru() { return this->m; }
	Carte* getCarte() { return this->c; }
	std::string getMotiv() { return this->motiv; }
	double getSuma() { return this->suma; }
	bool getStatus() { return this->status; }

	void plateste() {
		this->status = true;
		this->suma = 0;
	}
	bool getEstePlatita() { return this->status; }
	friend std::ostream& operator <<(std::ostream& out, const Amenda& n) {
		out << "\n Membru: " << *n.m << "\n Carte: " << *n.c << "\n Suma:" << n.suma << "\n Motiv: " << n.motiv<<"\n Status: "<< (n.status ? "activa" : "inactiva") << "\n";
		return out;
	}
};

class Biblioteca{

private:
	std::string nume, adresa;
	std::vector<Carte> inventarCarti;
	std::vector<Membru> listaMembri;
	std::vector<Rezervare> listaRezervari;
	std::vector<Amenda> listaAmenzi;
	int contorIdMembri, contorIdRezervari, contorIdAmenzi;

public:
	Biblioteca(std::string nume, std::string adresa) {
		this->nume = nume;
		this->adresa = adresa;
		contorIdAmenzi = 0;
		contorIdMembri = 0;
		contorIdRezervari = 0;
	}
	~Biblioteca()
	{
		inventarCarti.clear();
		listaMembri.clear();
		listaAmenzi.clear();
		listaRezervari.clear();

	}

	void adaugaCarte(std::string titlu, std::string autor, int an, std::string editura, std::string categorie, int pagini) {
		Carte c(titlu, autor, an, editura, categorie, pagini);
		inventarCarti.push_back(c);
	}

	void eliminaCarte(std::string ISBN) {
		std::vector<Carte> inventarCartiNou;
		for (auto& carte : inventarCarti) {
			if (carte.getISBN() != ISBN) {
				inventarCartiNou.push_back(carte);
			}
		}
		inventarCarti = inventarCartiNou;
	}
	
	Carte& gasesteCarteDupaTitlu(std::string titlu) {
		for (auto& carte : inventarCarti) {
			if (carte.getTitlu() == titlu) {
				return carte;
			}
		}
		throw std::runtime_error("Carte negasita");
	}
	
	std::vector<Carte> gasesteCarteDupaAutor(std::string autor) {
		std::vector<Carte> rezultat;
		for (auto& c : inventarCarti)
			if (c.getAutor() == autor) rezultat.push_back(c);
		return rezultat;
	}


	std::vector<Carte> gasesteCarteDupaCategorie(std::string categorie) {
		std::vector<Carte> rezultat;
		for (auto& c : inventarCarti)
			if (c.getCategorie() == categorie) rezultat.push_back(c);
		return rezultat;
	}

	Carte* gasesteCarteDupaISBN(std::string ISBN) {
		for (auto& c : inventarCarti)
			if (c.getISBN() == ISBN) return &c;  // acesta este unic deci exista doar unul
		return nullptr;
	}

	// membri
	void adaugaMembru(std::string nume, std::string adresa, std::string telefon, std::string email) {
		listaMembri.emplace_back(contorIdMembri++, nume, adresa, telefon, email);
	}

	void eliminaMembru(int idMembru) {
		listaMembri.erase(std::remove_if(listaMembri.begin(), listaMembri.end(), [idMembru](Membru& m) { 
				return m.getId() == idMembru;
			}), listaMembri.end());
	}

	Membru* gasesteMembruDupaId(int id) {
		for (auto& m : listaMembri)
			if (m.getId() == id) return &m;
		return nullptr;
	}

	std::vector<Membru*> gasesteMembruDupaNume(std::string nume) {
		std::vector<Membru*> rezultat;
		for (auto& m : listaMembri)
			if (m.getNume() == nume) rezultat.push_back(&m);
		return rezultat;
	}

	// Împrumut
	void imprumutaCarte(int idMembru, const std::string& titlu, const std::string& dataImprumut) {
		try {
			Membru* m = gasesteMembruDupaId(idMembru);
			if (!m) {
				std::cout << "Eroare: membru inexistent\n";
				return;
			}

			Carte& carte = gasesteCarteDupaTitlu(titlu);
			if (carte.getStatus()) {
				std::cout << "Cartea este deja imprumutata\n";
				return;
			}

			m->imprumutaCarte(&carte, dataImprumut);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Eroare: " << e.what() << "\n";
		}
	}

	void returneazaCarte(int idMembru, const std::string& titlu) {
		try {
			Membru* m = gasesteMembruDupaId(idMembru);
			if (!m) {
				std::cout << "Eroare: membru inexistent\n";
				return;
			}

			Carte& carte = gasesteCarteDupaTitlu(titlu);
			m->returneazaCarte(&carte);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Eroare: " << e.what() << "\n";
		}
	}


	// Rezervari
	void adaugaRezervare(int idMembru, const std::string& titlu, const std::string& dataRezervare) {
		try {
			Membru* m = gasesteMembruDupaId(idMembru);
			if (!m) {
				std::cout << "Eroare: membru inexistent\n";
				return;
			}

			Carte& carte = gasesteCarteDupaTitlu(titlu);
			listaRezervari.emplace_back(contorIdRezervari++, m, &carte, dataRezervare);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Eroare: " << e.what() << "\n";
		}
	}

	void proceseazaRezervare(int idRezervare, std::string dataImprumut) {
		if (idRezervare < 0 || idRezervare >= listaRezervari.size()) {
			std::cout << "Rezervare inexistenta.\n";
			return;
		}
		listaRezervari[idRezervare].proceseaza(dataImprumut);
	}

	// Amenzi
	void adaugaAmenda(int idMembru, const std::string& titlu, const std::string& motiv, double suma) {
		try {
			Membru* m = gasesteMembruDupaId(idMembru);
			if (!m) {
				std::cout << "Eroare: membru inexistent\n";
				return;
			}

			Carte& carte = gasesteCarteDupaTitlu(titlu);
			listaAmenzi.emplace_back(contorIdAmenzi++, m, &carte, motiv, suma);
		}
		catch (const std::runtime_error& e) {
			std::cout << "Eroare: " << e.what() << "\n";
		}
	}

	void platesteAmenda(int idAmenda) {
		if (idAmenda < 0 || idAmenda >= listaAmenzi.size()) {
			std::cout << "Amenda inexistenta.\n";
			return;
		}
		listaAmenzi[idAmenda].plateste();
	}

	// Rapoarte
	void afiseazaInventarCarti() {
		for (auto& c : inventarCarti) std::cout << c;
	}

	void afiseazaMembri() {
		for (auto& m : listaMembri) std::cout << m;
	}

	void afiseazaRezervariActive() {
		for (auto& r : listaRezervari)
			if (r.getEsteActiva()) std::cout << r;
	}

	void afiseazaAmenziNeplatite() {
		for (auto& a : listaAmenzi)
			if (!a.getEstePlatita()) std::cout << a;
	}

private:
	int numaraCartiImprumutate() {
		int count = 0;
		for (auto& carte : inventarCarti) {
			if (!carte.getStatus()) {
				count++;
			}
		}
		return count;
	}
	int numaraAmenziNeplatite() {
		int count = 0;
		for (auto& amenda : listaAmenzi) {
			if (!amenda.getEstePlatita()) {
				count++;
			}
		}
		return count;
	}

public:

	void afiseazaStatisticiBiblioteca() {
		std::cout << "Numar carti: " << inventarCarti.size() << "\n";
		std::cout << "Numar membri: " << listaMembri.size() << "\n";
		std::cout << "Rezervari active: " << numaraCartiImprumutate() << "\n";
		std::cout << "Amenzi neplatite: " << numaraAmenziNeplatite()  << "\n";
	}

	
};



int main() {
	Biblioteca biblioteca("Biblioteca", "Str. Jjdajsfal");

	biblioteca.adaugaCarte("C++ Modern", "B.S.", 2013, "1", "Programare", 350);
	biblioteca.adaugaCarte("Clean Code", "R.M", 2008, "2", "Programare", 450);
	biblioteca.adaugaCarte("1984", "George Orwell", 1949, "3", "Fictiune", 300);

	std::cout << "=== Inventar carti ===\n";
	biblioteca.afiseazaInventarCarti();

	biblioteca.adaugaMembru("Andrei Popescu", "----", "09320392", "email@...");
	biblioteca.adaugaMembru("Ioana Ionescu", "----", "87432879432", "ioana@email.com");

	std::cout << "\n=== Membri ===\n";
	biblioteca.afiseazaMembri();

	biblioteca.imprumutaCarte(0, "C++ Modern", "2025-04-05");
	biblioteca.returneazaCarte(0, "C++ Modern");
	biblioteca.imprumutaCarte(1, "C++ Modern", "2025-04-07");

	biblioteca.adaugaRezervare(0, "Clean Code", "2025-04-05");
	biblioteca.proceseazaRezervare(0, "2025-04-06");

	biblioteca.adaugaAmenda(1, "C++ Modern", "Intarziere returnare", 25.0);

	std::cout << "\n=== Amenzi neplatite ===\n";
	biblioteca.afiseazaAmenziNeplatite();

	biblioteca.platesteAmenda(0);

	std::cout << "\n=== Amenzi neplatite dupa plata ===\n";
	biblioteca.afiseazaAmenziNeplatite();

	std::cout << "\n=== Rezervari active ===\n";
	biblioteca.afiseazaRezervariActive();

	std::cout << "\n=== Statistici Biblioteca ===\n";
	biblioteca.afiseazaStatisticiBiblioteca();

	return 0;
}