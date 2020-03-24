#include <iostream>
#include <fstream>
#include <assert.h>
#include "Polinom.h"

std::ifstream f("input.in");

void runTestsPolinom()
{
    Polinom p, p2, p3;
    f >> p;
    cout << "p: " << p << endl;
    p3 = p;
    assert(p3[2] == p[2]);             // verific operatorul [] si copierea
    assert(p3.getDeg() == p.getDeg()); // verific daca am grade egale
    assert(p.getValueFor(2) == 14);    // verific calculul intr-un anumit punct
    assert(p(2) == 14);                // verific calculul intr-un anumit punct cu ()
    cout << "p4:" << p3 << endl;
    cout << "p4/p: " << p3 / p << endl;
    assert((p3 / p).getDeg() == 0); // verific daca am obrinut 1 (careare gradul 0)
    f >> p2;

    f.close();
    cout << "p2:" << p2 << endl;
    assert((p2 * p).getDeg() == (p2.getDeg() + p.getDeg())); //verific adunarea stiing ca gradul polinomului rezultant trebuie sa fie suma celor doua
    cout << "p2*3:" << p2 * 3 << endl;
    cout << "p2/p:" << p2 / p << endl;
    assert((p2 / p).getDeg() == (p2.getDeg() - p.getDeg())); // iar la impartire diferenta lor
    p2.erase(5);
    assert(p2.getDeg() == 2); //testez functia de stergere
}

int main()
{
    runTestsPolinom();
    return 0;
}