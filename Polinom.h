#pragma once
#include <iostream>
using namespace std;

class Polinom
{
    struct Element
    {
        int grad;
        double coeff;
        Element *next;

    }; // strcutura elementelor din lsita simplu inlantuita
    unsigned int size;
    Element *start, *end; // pointerele care ma duc la inceputul si finalul listei mele

public:
    Polinom();
    ~Polinom();
    Polinom(const Polinom &p);
    double getValueFor(double x) const;
    Polinom operator+(Polinom &) const;
    double &operator[](unsigned int) const;
    Polinom operator*(Polinom &)const;
    Polinom operator*(const double)const; // inmultirea cu un scalar
    Polinom operator/(Polinom &) const;
    double operator()(const double) const;
    void insert(double, unsigned int); //metoda alternativa ce a calcula un Polinom intr-un punct
    void erase(unsigned int);
    unsigned int getDeg();
    Polinom &operator=(const Polinom &);
    friend istream &operator>>(istream &, Polinom &);
    friend ostream &operator<<(ostream &, const Polinom &);
};