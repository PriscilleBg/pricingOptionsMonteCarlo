#pragma once
#include "ProduitDerive.h"


class Asiatique :
	public ProduitDerive
{
private:
	double S0, K, r, sigma, T;
	int nombrePas;
	GenerateurAleatoire* pU;

public:
	Asiatique(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU);
	double payoff();
	double payoffAT();
};

