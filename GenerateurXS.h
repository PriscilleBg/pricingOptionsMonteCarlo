#pragma once
#include "GenerateurAleatoire.h"


// Un g�n�rateur XOR-Shift (Cf. Numerical Recipes - The Art of Scientific Computing)
class GenerateurXS :
	public GenerateurAleatoire
{
private :
	int xn, a1, a2, a3;

public:
	// Diff�rents constructeurs
	GenerateurXS();
	GenerateurXS(unsigned long long x0, int a1, int a2, int a3);

	// Fonction g�n�ratrice d'une loi uniforme
	double unif();
};