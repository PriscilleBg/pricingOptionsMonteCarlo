#pragma once
#include "ProduitDerive.h"
class AsiatMoinsCall :
	public ProduitDerive
{
private:
	double S0, K, r, sigma, T;
	int nombrePas;
	GenerateurAleatoire* pU;
public:
	AsiatMoinsCall(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU);
	double payoff();
	double payoffAT();
};

