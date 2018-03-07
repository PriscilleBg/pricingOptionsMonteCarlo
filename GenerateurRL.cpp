#include "GenerateurRL.h"


// Constructeur avec tous les param�tres
GenerateurRL::GenerateurRL(long long x0, long long a, long long b, long long m) : xn(x0), a(a), b(b), m(m)
{}

// Constructeur avec tous les param�tres sauf la 'seed'
GenerateurRL::GenerateurRL(long long a, long long b, long long m) : xn(1497 % m), a(a), b(b), m(m)
{}

// Constructeur sans aucun param�tres choisi par l'utilisateur
GenerateurRL::GenerateurRL() : xn(1984 % m), a(31415821), b(1), m(1e8)
{}

// Fonction g�n�ratrice
double GenerateurRL::unif()
{
	xn = ((a*xn + b) % m);
	return ((double)xn) / ((double)m);
}