#pragma once
#include "GenerateurAleatoire.h"


// Un générateur utilisant une relation de récurrence linéaire
class GenerateurRL :
	public GenerateurAleatoire
{
private:
	long long xn, a, b, m;
public:

	// Différents constructeurs
	GenerateurRL();
	GenerateurRL(long long x0, long long a, long long b, long long m);
	GenerateurRL(long long a, long long b, long long m);

	// Fonction génératrice d'une loi uniforme
	double unif();
};