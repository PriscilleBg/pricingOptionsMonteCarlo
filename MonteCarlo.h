#pragma once
#include "GenerateurAleatoire.h"
#include "Asiatique.h"
#include "CallVanille.h"
#include <vector>


// Calcul du prix d'un produit dérivé par Monte-Carlo
double prixMC(ProduitDerive* P, int nombreIter, bool variableAntithetique);
double prixMC(ProduitDerive* P, int nombreIter);

// Calcule une série de prix par la méthode de Monte-Carlo
std::vector<double> serieMC(ProduitDerive* pP, int nombreIter, int nombreSimulations, bool variableAntithetique);

// Ecart-type des prix Monte-Carlo
double STD(std::vector<double> seriePrix);

// Une trajectoire de Monte-Carlo
std::vector<double> Trajectoire(ProduitDerive* pP, int pas, int maxIter);

// Fonction donnant à nombre d'itérations donné, la log-variance du prix Monte-Carlo
double stdMC(ProduitDerive* pP, int nombreIter, int nombreSimulations, bool variableAntithetique);

// Fonction estimant log-variance du prix MC en fonction du nombre d'itérations
std::vector<double> stdIter(ProduitDerive* pP, int expMin, int expMax, int nombreSimulations, bool variableAntithetique);