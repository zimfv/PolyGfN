// polygfn_191012.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


template <typename T>
std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}
template <typename T>
T max(T a, T b)
{
	if (a > b)
		return a;
	return b;
}
template <typename T>
T min(T a, T b)
{
	if (a < b)
		return a;
	return b;
}


class polynom
{
private:
	int dim; //Dimension
	int charact; //Characteristic
	int *coefs; //Polynom coefficients

	//This function "clean" polynom: factor this by charact and delete all first zeros.
	void clean() { 
		int firstnonzero = 0;
		for (int i = dim; i <= dim; i++) 
		{
			coefs[i] = coefs[i] % charact;
			if ((firstnonzero == 0) && (coefs[i] != 0))
				firstnonzero = i;
		}
		if (firstnonzero < dim)
		{
			dim = firstnonzero;
			int *newcoefs;
			newcoefs = new int[dim];
			for(int i = 0; i < dim; i++)
				newcoefs[i] = coefs[i];
			delete coefs;
			coefs = new int[dim];
			for (int i = 0; i < dim; i++)
				coefs[i] = newcoefs[i];
		}
	}

	friend ostream& operator<<(ostream &os, const polynom& p);
	friend const polynom& operator+(const polynom& p1, const polynom& p2);
	friend const polynom& operator-(const polynom& p1, const polynom& p2);
	friend const polynom& operator*(const int& a, const polynom& p);
	friend const polynom& operator*(const polynom& p, const int& a);
	friend const polynom& operator*(const polynom& p1, const polynom& p2);

public:
	polynom(int _dim, int _charact) 
	{
		dim = _dim;
		charact = _charact;
		coefs = new int[dim + 1];
		for (int i = 0; i < dim; i++) 
		{
			coefs[i] = 0;
		}
		coefs[dim] = 1;
	}

	polynom(int _dim, int *_coefs, int _charact)
	{
		dim = _dim;
		charact = _charact;
		coefs = new int[dim + 1];
		for (int i = 0; i < dim + 1 ; i++)
		{
			coefs[i] = _coefs[i]%charact;
		}
	}

	int get_dim()
	{
		return dim;
	}

	int get_charact()
	{
		return charact;
	}

	int set_charact(int _charact)
	{
		charact = _charact;
	}

	
};

ostream& operator<<(ostream &os, const polynom& p) {
	if (p.dim == 0)
		return os << NumberToString(p.coefs[0]);
	std::string n = NumberToString(p.coefs[p.dim]);
	if (n == "1")
		n = "";
	std::string strp = n + "x^" + NumberToString(p.dim);
	for (int i = p.dim - 1; i > 0; i--) 
	{
		if (p.coefs[i] > 0)
		{
			strp = strp + " + ";
			if (p.coefs[i] > 1)
				strp = strp + NumberToString(p.coefs[i]);
			strp = strp + "x^" + NumberToString(i);
		}
	}
	if (p.coefs[0] > 0)
		strp = strp + " + " + NumberToString(p.coefs[0]);
	return os << strp;
}

// This function returns summ of two polynom with first polynom characteristic.
// I hope, you dont need summ polynoms with different characteristics, but
// if you need, write it youreself. (I don't understand, does it look like)
const polynom& operator+(const polynom& p1, const polynom& p2) {
	polynom pr(max(p1.dim, p2.dim),p1.charact);
	pr.coefs[pr.dim] = 0;
	for (int i = 0; i <= pr.dim; i++) {
		if (i <= p1.dim)
			pr.coefs[i] = pr.coefs[i] + p1.coefs[i];
		if (i <= p2.dim)
			pr.coefs[i] = pr.coefs[i] + p2.coefs[i];
	}
	/*
	for (int i = 0; i <= pr.dim; i++) 
	{
		//I start write anything else. Next commented string is wrong. Just delete it.
		//pr.coefs[i + 1] = pr.coefs[i + 1] + pr.coefs[i] / pr.charact;
		pr.coefs[i] = pr.coefs[i] % pr.charact;
	}
	*/
	pr.clean();
	return pr;
}

const polynom& operator-(const polynom& p1, const polynom& p2) {
	polynom p22 = p2;
	for (int i = 0; i <= p22.dim; i ++) 
	{
		p22.coefs[i] = p1.charact - p22.coefs[i];
	}
	polynom pr = p1 + p22;
	return pr;
}

const polynom& operator*(const int& a, const polynom& p) {
	int *prcoefs;
	prcoefs = new int[p.dim];
	for (int i = 0; i <= p.dim; i++)
	{
		prcoefs[i] = p.coefs[i] * a % p.charact;
	}
	polynom pr(p.dim, prcoefs, p.charact);
	return pr;
}

const polynom& operator*(const polynom& p, const int& a) {
	int *prcoefs;
	prcoefs = new int[p.dim];
	for (int i = 0; i <= p.dim; i++)
	{
		prcoefs[i] = p.coefs[i] * a %p.charact;
	}
	polynom pr(p.dim, prcoefs, p.charact);
	return pr;
}

const polynom& operator*(const polynom& p1, const polynom& p2) {
	int *prcoefs;
	prcoefs = new int[p1.dim + p2.dim];
	for (int i = 0; i <= p1.dim + p2.dim; i++)
	{
		prcoefs[i] = 0;
	}
	for (int i = 0; i <= p1.dim; i++) 
	{
		for (int k = 0; k <= p2.dim; k++)
		{
			prcoefs[i + k] = prcoefs[i + k] + (p1.coefs[i] * p2.coefs[k]);
		}
	}
	polynom pr(p1.dim + p2.dim, prcoefs, p1.charact);
	pr.clean();
	return pr;
}



int main()
{
	polynom a(4, 3);
	cout << "dim(a) = " << a.get_dim() << "    ";
	cout << "char(a) = " << a.get_charact() << endl;
	cout << "a = " << a << endl << endl;

	int cfsb[9] = { 1, 2, 3, 0, 2, 2, 3, 0, 1 };
	polynom b(8,cfsb,3);
	cout << "dim(b) = " << b.get_dim() << "    ";
	cout << "char(b) = " << b.get_charact() << endl;
	cout << "b = " << b << endl << endl;

	polynom c = a + b;
	cout << "a + b = " << c << endl << endl;
	c = a - b;
	cout << "a - b = " << c << endl << endl; 
	c = b - a;
	cout << "b - a = " << c << endl << endl;
	system("pause");
	c = 4 * a;
	cout << "4 * a = " << c << endl << endl;
	c = b * 5;
	cout << "b * 5 = " << c << endl << endl;
	c = a * b;
	cout << "a * b = " << c << endl << endl;
	system("pause");
	//c = a + a + a;
	//cout << "a + a + a = " << c << endl << endl;
	system("pause");
    return 0;
}

