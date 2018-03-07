#pragma once
#include "GenerateurAleatoire.h"


// Un générateur XOR-Shift (Cf. Numerical Recipes - The Art of Scientific Computing)
class GenerateurXS :
	public GenerateurAleatoire
{
private :
	int xn, a1, a2, a3;

public:
	// Différents constructeurs
	GenerateurXS();
	GenerateurXS(unsigned long long x0, int a1, int a2, int a3);

	// Fonction génératrice d'une loi uniforme
	double unif();
};