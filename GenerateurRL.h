#pragma once
#include "GenerateurAleatoire.h"


// Un g�n�rateur utilisant une relation de r�currence lin�aire
class GenerateurRL :
	public GenerateurAleatoire
{
private:
	long long xn, a, b, m;
public:

	// Diff�rents constructeurs
	GenerateurRL();
	GenerateurRL(long long x0, long long a, long long b, long long m);
	GenerateurRL(long long a, long long b, long long m);

	// Fonction g�n�ratrice d'une loi uniforme
	double unif();
};