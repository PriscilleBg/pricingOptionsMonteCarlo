#pragma once
#include "GenerateurAleatoire.h"

// Générateur Blum-Blum-Shub
// xn+1 = xn² mod M, où M est le produit de deux premiers congrus à 3 modulo 4.
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