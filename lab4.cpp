#include <iostream>
#include <cstring>

// Sa se scrie o clasa BigNumber in care sa poata fi retinute numere intregi cu nr mare de cifre
//	- contructori + constructori de copiere
//	- destructor
//	- supra incarcarea operatorului =
// Sa se supra incarce operatorii + - * += -= >> <<
// 
// Sa se citeasca 2 numere mari de la tastatura si sa se calculeze si sa se afiseze suma si dif lor.
// 
// 
// 
// Supraincarcarea operatorilor
// 
// Op pot fi supraincarcate ca 
//		1.metode ale clasei
//		2.metoda externa clasei
//		3.metode prietena clasei
// 
// metodele prietene 
//	-nu sunt considereate metode ale clasei
//	-au in fata declaratiei cuvandul friend 
//	-declararea metodelor prietene clasei se face in interiorul clasei 
//	-au acces la membrii privati
//

class BigNumber {
public:
	int* number; //retinere in ordine inversa
	size_t noDigits;
	bool isNegative;
public:
	BigNumber() {
		this->number = nullptr;
		this->noDigits = 0;
		this->isNegative = false;
	}
	BigNumber(std::string number) {
		if (number[0] == '-') {
			isNegative = true;
			noDigits = number.size() - 1;
		}
		else {
			isNegative = false;
			noDigits = number.size();
		}
		this->number = new int[noDigits];
		for (int i = 0;i < noDigits;i++) {
			this->number[i] = number[number.size() - 1 - i]-'0';
		}
	}
	~BigNumber() {
		delete[] number;
	}
	BigNumber(BigNumber& nr) {
		number = new int[nr.noDigits];
		noDigits = nr.noDigits;
		isNegative = nr.isNegative;
		for (int i = 0;i < noDigits;i++)
			number[i] = nr.number[i];
	}

	BigNumber& operator =(BigNumber nr) {
		if (this != &nr) { //nu e acelasi obiect
			delete[] number;
			number = new int[nr.noDigits];
			noDigits = nr.noDigits;
			isNegative = nr.isNegative;
			for (int i = 0;i < noDigits;i++)
				number[i] = nr.number[i];
		}
		return *this;
	}
	
	friend std::ostream& operator <<(std::ostream& out,const BigNumber& nr) {
		if (nr.isNegative)
			out << '-';
		for (int i = nr.noDigits - 1;i >= 0;i--) {
			out << nr.number[i];
		}
		out << " ";
		return out;
	}

	friend std::istream& operator >>(std::istream& in, BigNumber& nr) {
		std::string number;
		in >> number;
		BigNumber nou(number);
		nr = nou;

		return in;
	}

	friend BigNumber& operator +(const BigNumber& nr, const BigNumber& nr2) {
		int* sum = new int[nr2.noDigits + nr.noDigits];
		int i = 0, j = 0, k = 0;
		while (i < nr.noDigits && j < nr2.noDigits)
		{
			if (nr.isNegative) {
				if (nr.number[i] > nr2.number[j++]) {
					nr.number[i] += 10;
					nr.number[i + 1]--;
				}
				sum[k] = nr2.number[j++] - nr.number[i++];
			}
			else {
				sum[k] = nr2.number[j++] + nr.number[i++];
				if (sum[k] > 9) {
					sum[k + 1] = sum[k] / 10;
					sum[k] = sum[k] % 10;
				}
			}
			k++;
		}
		while (i < nr.noDigits) {
			sum[k] = nr.number[i++];
			if (sum[k] > 9) {
				sum[k + 1] = sum[k] / 10;
				sum[k] = sum[k] % 10;
			}
			k++;
		}
		while (j < nr2.noDigits) {
			sum[k] = nr2.number[j++];
			if (sum[k] > 9) {
				sum[k + 1] = sum[k] / 10;
				sum[k] = sum[k] % 10;
			}
			k++;
		}
		BigNumber suma;
		suma.number = sum;
		suma.isNegative = false;
		suma.noDigits = k;
		return suma;
	}

	BigNumber& operator +=(const BigNumber& nr) {
		*this = *this + nr; // are nevoie de +
		return *this; 
	}

	void afisare() {
		for (int i = noDigits-1;i >= 0;i--) {
			std::cout << number[i];
		}
		std::cout << std::endl;
	}
};


int main() {
	BigNumber nr("123456");
	BigNumber nr2;
	nr2 = nr;
	BigNumber nr3(nr);
	nr.afisare();
	nr2.afisare();
	nr3.afisare();
	std::cin >> nr;
	std::cout << nr;
	nr += nr3;
	std::cout << nr;
	return 0;
}