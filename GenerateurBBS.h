#pragma once
#include "GenerateurAleatoire.h"

// G�n�rateur Blum-Blum-Shub
// xn+1 = xn� mod M, o� M est le produit de deux premiers congrus � 3 modulo 4.
class GenerateurBBS :
	public GenerateurAleatoire
{
private:
	long long M, xn;
public:
	GenerateurBBS();
	GenerateurBBS(long long x0);
	double unif();
};