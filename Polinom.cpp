#include "Polinom.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <exception>
Polinom::Polinom()
{
    this->size = 0;
    start = 0;
    end = 0;
}
Polinom::Polinom(const Polinom &p)
{
    size = 0;
    start = end = 0;
    Element *aux = p.start; // iau primul element din p
    while (aux)
    {
        this->insert(aux->coeff, aux->grad); // il adaug in elemntul in care copiez
        aux = aux->next;                     // trec la urmatorul element
    }
}

Polinom::~Polinom()
{
    this->size = 0;
    Element *current = start;
    Element *next;

    while (current != NULL)
    {
        next = current->next; // accesez urm pozitie
        delete current;       // sterg pozitia curenta
        current = next;       // trec pe urmaotarea poz
    }
    start = end = 0;
}

Polinom &Polinom::operator=(const Polinom &source)
{
    if (this == &source)
    {
        return *this; // daca atribui un ob la acelasi obiect, il returnez direct
    }

    Element *p = source.start; // iau primul element din source
    this->size = 0;            // fac dimensiunea elem actual 0

    Element *current = start;
    Element *next;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }

    start = end = 0; // refac ce fac in destructor
    //delete this; // am crezut ca merge direct cu delete, dar nu
    while (p)
    {                                    // cat timp am noduri in source
        this->insert(p->coeff, p->grad); // il inserez in Polinomul curent
        p = p->next;                     // trec la urmatorul element
    }
    return *this; // returnez obiectul
}

void Polinom::insert(double val, unsigned int deg)
{
    /*
	@param
		val - coeficientul elementului de un anumit grad
		deg - gradul elemntului
	@descriere
		Fac un nod nou si il introduc in coada si pastrez proprietatea ca elementele sa fie ordonate descrescator dupa grad
	*/
    if (val == 0)
    {
        return; // daca valoarea e 0, nu inserez nimic
    }
    Element *new_elem = new Element();
    new_elem->coeff = val;
    new_elem->grad = deg;
    new_elem->next = 0; // fac un element nou

    if (!size)
    { // daca am un polinom gol, start si end sunt la fel
        start = end = new_elem;
    }
    else
    {
        if (deg > start->grad)
        { //daca elem este primul
            new_elem->next = start;
            start = new_elem; //schimb start
            ++size;
            return; // ma intorc
        }
        if (deg < end->grad)
        { //daca noul element este ultimul
            end->next = new_elem;
            end = new_elem; // schimb end
            ++size;
            return; // ma intorc
        }
        Element *last = start;
        Element *p = start;
        while (p)
        {                       // trec prin lsita
            if (p->grad <= deg) // daca am gasit un nod cu grad <= decat noul meu nod
                break;          // ma opresc
            last = p;           //retin nodul precendet
            p = p->next;        // merg la urmatorul
        }
        if (p->grad == deg)
        {                    // daca gradul este egal
            p->coeff += val; // doar adaug valoarea, fara sa mai fac adaug nodul
            return;          // ma intorc
        }
        last->next = new_elem; // elem anterio pointeza la noul element, pt ca avea grad mai mare
        new_elem->next = p;    // noul nod pointeza catre actualul, fiindca sigur are grad mai mic
    }
    ++size; //incrementez size-ul
}

void Polinom::erase(unsigned int grad)
{
    /*
	@param
		grad- gradul elementului care trebuie eliminat
	*/

    if (size == 0)                                // daca Polinomul este gol
        throw length_error("Polinomul este gol"); // eroare
    if (size == 1)
    { // daca am doar un nod
        if (start->grad == grad)
        { //il sterg doar daca are gradul din paramtru
            delete start;
            start = end = 0;
            return;
        }
        else
            throw invalid_argument("Polinomul pe care s-a apelat functia nu are indexul din argument"); // altfel eroare
    }
    Element *aux = this->start; // primul nod din coada
    Element *prev = aux;
    while (aux) // cat timp am elemente in lista
    {
        if (aux->grad < grad) // daca am ajuns la un grad mai mic, sigur nu am gasit gradul deoarece elem sun sortate
            break;
        if (aux->grad == grad)
        { // daca am gasit gradul cerut
            if (aux == end)
            { //daca gradul este ultimul in polinom
                prev = end;
                delete aux;
                return;
            }
            if (aux == start)        // daca elementul cautat este primul
                start = start->next; // actualizez pointerul catrea inceput
            prev->next = aux->next;  // nodul precedent o sa pointeze catre urmatorul
            delete aux;
            return; // il sterg si ies
        }
        prev = aux;
        aux = aux->next;
    }
    throw invalid_argument("Polinomul pe care s-a apelat functia nu are indexul din argument"); // eroare daca nu am sters nimic
}

double Polinom::getValueFor(double x) const
{
    /*
	@param
		x- valoarea in care trebuei sa calculam polinomul
	@returns
		double - valoarea polinomului in punctul x
	*/
    Element *p = start;
    double result = 0;
    while (p)
    {
        result += (p->coeff * pow(x, p->grad)); // adaugam la rezultat coeficientul * x la puterea grad
        p = p->next;
    }
    return result;
}

Polinom Polinom::operator+(Polinom &p2) const
{
    Polinom *result = new Polinom(); // fac un polinom nou in care construiesc rezulatul
    Element *p = start;              // startul pt polinomul din stanga
    Element *q = p2.start;           // startul pt polinomul din dreapta
    while (p && q)
    { // cat timp sunt elemente
        if (p->grad == q->grad)
        {                                                 // daca sunt egale gradele
            result->insert(p->coeff + q->coeff, p->grad); //inserez un nod cu suma coef
            p = p->next;
            q = q->next; // trec la urmatoarele elemente in ambele polinoame
        }
        else if (p->grad > q->grad)
        {                                      // daca primul are grad mai mare
            result->insert(p->coeff, p->grad); // il inserez pe acela
            p = p->next;                       // trec la urmatorul element doar in primul polinom
        }
        else
        {
            result->insert(q->coeff, q->grad);
            q = q->next; // altfel il inserez pe celalalt si mut pozitia
        }
    }
    while (p)
    { // daca mi-au ramas elem in p le inserez
        if (p->coeff)
            result->insert(p->coeff, p->grad);
        p = p->next;
    }
    while (q)
    { // daca mi-au ramas elemente in q le inserez
        if (q->coeff)
            result->insert(q->coeff, q->grad);
        q = q->next;
    }
    return *result; // returnez polinomul construit
}

Polinom Polinom::operator*(Polinom &p2) const
{
    Polinom result;        // un polinom pe care il returnez
    Element *p = start;    // pointer catre elem primului polinom
    Element *q = p2.start; // pointer catre elementele celui de al doilea polinom
    while (p)
    { // fiecare element din primul polinom
        Element *aux = q;
        while (aux)
        { // il inmultesc cu fiecare element din al doilea polinom
            result.insert(p->coeff * aux->coeff, p->grad + aux->grad);
            aux = aux->next;
        }
        p = p->next;
    }
    return result;
}

Polinom Polinom::operator*(const double scalar) const
{
    /*
	@param
		scalar - numar real pe care il inmultesc cu elementele polinomului
	*/
    Polinom result;
    Element *p = start;
    while (p)
    {                                              // fiecare element din Polinomul actual
        result.insert(p->coeff * scalar, p->grad); // il inmultesc cu scalar si il adaug in result
        p = p->next;                               // trec la urmatorul element
    }
    return result;
}

Polinom Polinom::operator/(Polinom &p2) const
{
    if (p2.start->grad > start->grad)
    {
        // daca impart la un polinom cu grad mai mare, intorc un Polinom gol
        return *(new Polinom());
    }
    Polinom deimpartit(*this); // copiez elementul pe care trebuie sa-l impart
    Polinom result;
    while (deimpartit.start && (deimpartit.getDeg() >= p2.getDeg()))
    {                                                                                                // cat timp am deimpartit si gradul lui e mai mic deact al impartitorului
        result.insert(deimpartit.start->coeff / p2.start->coeff, deimpartit.getDeg() - p2.getDeg()); // inserez element in result
        Polinom single;
        single.insert(-1 * deimpartit.start->coeff / p2.start->coeff, deimpartit.getDeg() - p2.getDeg()); // elementul din dreapta
        single = p2 * single;                                                                             // il inmultesc cu impartitorul
        deimpartit = deimpartit + single;                                                                 // actualizez deimpartitul
    }
    return result;
}

double &Polinom::operator[](unsigned int i) const
{
    /*
	@param
		i - gradul elementului pe care il caut
	@return
		double - coeficientul elementului de grad i
	*/
    Element *p = start; // primul element din polinom
    while (p)
    { // cat tim am element
        if (p->grad == i)
        {                    // daca gradul este cel din paramteru
            return p->coeff; // returnez coeficientul
        }
        p = p->next;
    }
    throw invalid_argument("Polinomul nu are element cu gradul din []");
}

double Polinom::operator()(const double val) const
{
    double result = this->getValueFor(val); //apelez cealalta funcite de aflat valoarea
    return result;
}

std::istream &operator>>(std::istream &input, Polinom &p)
{
    unsigned int nrElem;
    double coeff;
    unsigned int putere;
    input >> nrElem; // iau mai intai numarul de elemente
    while (nrElem--)
    {
        input >> coeff >> putere; // introduc elemente din perechi de tipul (coeficient,putere)
        p.insert(coeff, putere);
    }
    return input;
}
std::ostream &operator<<(std::ostream &out, const Polinom &p)
{
    Polinom::Element *curr = p.start; // iau inceputul polinomului
    while (curr)
    {
        out << curr->coeff << "x^" << curr->grad << " "; // afisez coeficientul si puterea
        curr = curr->next;                               // rec la urmatorul element
    }
    return out;
}

unsigned int Polinom::getDeg()
{
    return start->grad; // returnez gradul primului nod, fiindca este cel mai mare
}
