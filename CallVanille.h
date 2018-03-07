#pragma once
#include "ProduitDerive.h"

double F(double x);
double FSerie(double x);

class CallVanille :
	public ProduitDerive
{
private :
	double S0, K, r, sigma, T;
	GenerateurAleatoire* pU;
public:
	CallVanille(double S0, double K, double r, double sigma, double T, GenerateurAleatoire* U);
	double payoff();
	double payoffAT();
	double prixBS();
};