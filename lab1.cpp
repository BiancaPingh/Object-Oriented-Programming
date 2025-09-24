#include <iostream>

using namespace std;

//sa se scrie un program care implementeaza o stiva si functionalitatea ei
struct Stiva {
	int elemente[100];
	int vf=-1;

	void push( int elem) {
		vf++;
		elemente[vf] = elem;
	}
	bool gol() {
		return vf == -1;
	}
	void pop() {
		if (vf > -1) {
			vf--;
			elemente[vf] = 0;
		}
	}

	int top() {
		if(vf>-1)
			return elemente[vf];
		else {
			throw ("Stiva este vida"); //exceptie
		}
	}

};

struct NrComplexe {
	float p_img, p_real;

	NrComplexe(float re, float im) {  //constructor
		p_img = im;
		p_real = re;
	}

	void afisare() {
		cout << p_real;
		if (p_img < 0)
			cout << p_img << "* i";
		else cout << "+" << p_img << "* i";
	}
	

	NrComplexe operator +(NrComplexe c2) { //primul e obiect curent - care cheama metoda
		return NrComplexe(p_real + c2.p_img, p_img + c2.p_img);
	}
};

int main() {
	Stiva s;
	s.push(5);
	s.push(10);

	NrComplexe a(2,5), b(1,-7);
	a = a + b;
	a.afisare();


	return 0;
}