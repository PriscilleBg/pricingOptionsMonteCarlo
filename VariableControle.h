#ifndef VariableControle_h
#define VariableControle_h


#endif /* VariableControle_h */

# pragma once
# include "GenerateurAleatoire.h"
#include "ProduitDerive.h"
#include "CallVanille.h"




class VariableControle :
public ProduitDerive
{
private:
    double S0, K, r, sigma, T;
    int nombrePas;
    GenerateurAleatoire* pU;
    CallVanille* pBS;
    
public:
    VariableControle(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU, CallVanille* pBS);
	double payoff(), payoffAT();
};