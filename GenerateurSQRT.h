#pragma once
#include "GenerateurAleatoire.h"


// Un générateur pas du tout aléatoire utilisant la méthode SQRT
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

	// Générateur de loi uniforme
	double unif();
};

