#pragma once
#include "GenerateurAleatoire.h"


// G�n�rateur utilisant la m�thode de Halton
class GenerateurHalton :
	public GenerateurAleatoire
{
private:
	int p1, p2, n;
	bool P1ouP2;
public:

	// Constructeurs
	GenerateurHalton();
	GenerateurHalton(int p1, int p2);

	// G�n�rateur uniforme
	double unif();
};

