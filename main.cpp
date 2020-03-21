#include <iostream>
#include <fstream>
#include <assert.h>
#include "Polinom.h"

std::ifstream f("input.in");

int main()
{
	Polinom p, p2, p3;
	f >> p;
	cout <<"p: "<< p<< endl;
	p3 = p;
	assert(p3.getDeg() == p.getDeg());
	cout << "p4:" << p3 << endl;
	cout << "p4/p: " << p3/p << endl;
	assert((p3 / p).getDeg() == 0);
	f >> p2;
	f.close();
	cout <<"p2:"<< p2 << endl;
	assert((p2 * p).getDeg() == (p2.getDeg() + p.getDeg()));
	cout <<"p2*3:"<< p2*3<<endl;
	cout << "p2/p:" << p2/p << endl;
	assert((p2 / p).getDeg() == (p2.getDeg() - p.getDeg()));
	return 0;
}