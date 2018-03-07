#pragma once
#include "GenerateurAleatoire.h"


// Un g�n�rateur pas du tout al�atoire utilisant la m�thode SQRT
class GenerateurSQRT :
	public GenerateurAleatoire
{
private:
	double sqrtP1, sqrtP2, x1n, x2n;
	bool P1ouP2;

public:
	// Constructeurs
	GenerateurSQRT();
	GenerateurSQRT(int p1, int p2);

	// G�n�rateur de loi uniforme
	double unif();
};

