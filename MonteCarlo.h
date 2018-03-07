#pragma once
#include "GenerateurAleatoire.h"
#include "Asiatique.h"
#include "CallVanille.h"
#include <vector>


// Calcul du prix d'un produit d�riv� par Monte-Carlo
double prixMC(ProduitDerive* P, int nombreIter, bool variableAntithetique);
double prixMC(ProduitDerive* P, int nombreIter);

// Calcule une s�rie de prix par la m�thode de Monte-Carlo
std::vector<double> serieMC(ProduitDerive* pP, int nombreIter, int nombreSimulations, bool variableAntithetique);

// Ecart-type des prix Monte-Carlo
double STD(std::vector<double> seriePrix);

// Une trajectoire de Monte-Carlo
std::vector<double> Trajectoire(ProduitDerive* pP, int pas, int maxIter);

// Fonction donnant � nombre d'it�rations donn�, la log-variance du prix Monte-Carlo
double stdMC(ProduitDerive* pP, int nombreIter, int nombreSimulations, bool variableAntithetique);

// Fonction estimant log-variance du prix MC en fonction du nombre d'it�rations
std::vector<double> stdIter(ProduitDerive* pP, int expMin, int expMax, int nombreSimulations, bool variableAntithetique);