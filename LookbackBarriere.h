#ifndef LookbackBarriere_h
#define LookbackBarriere_h

#include <stdio.h>
#include "ProduitDerive.h"

#endif /* LookbackBarriere_h */

class LookbackBarriere :
public ProduitDerive
{
private:
    double S0, K, r, sigma, T, Percent;
    int nombrePas;
    GenerateurAleatoire* pU;
    
public:
    LookbackBarriere(double S0, double K, double r, double sigma, double T, double Percent, int nombrePas, GenerateurAleatoire* pU);
    double payoff();
	double payoffAT();
};