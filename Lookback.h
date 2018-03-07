#ifndef lookback_h
#define Lookback_h


#endif /* Lookback_h */

#pragma once
#include "ProduitDerive.h"

class Lookback :
public ProduitDerive
{
private:
    double S0, K, r, sigma, T;
    int nombrePas;
    GenerateurAleatoire* pU;
    
public:
    Lookback(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU);
    double payoff();
	double payoffAT();
};