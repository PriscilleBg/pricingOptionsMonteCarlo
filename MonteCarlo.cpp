#include "MonteCarlo.h"
using namespace std;

// Calcul du prix d'un produit dérivé par Monte-Carlo
double prixMC(ProduitDerive* P, int nombreIter, bool variableAntithetique)
{
	double sommePayoffs = 0.;
	int i;

	if (variableAntithetique)
	{
		for (i = 0; i < nombreIter; i++)
			sommePayoffs += P->payoffAT();
	}
	else
	{
		for (i = 0; i < nombreIter; i++)
			sommePayoffs += P->payoff();
	}

	return sommePayoffs / (double)nombreIter;
}

double prixMC(ProduitDerive* P, int nombreIter)
{
	return prixMC(P, nombreIter, false);
}


// Calcule une série de prix par la méthode de Monte-Carlo
vector<double> serieMC(ProduitDerive* pP, int nombreIter /*Nombre de simulations de payoffs pour chaque prix*/, 
	int nombreSimulations /* Nombre de prix MC donnés en résultat */, bool variableAntithetique)
{
	vector<double> seriePrix(nombreSimulations);
	for (int i = 0; i < nombreSimulations; i++)
		seriePrix[i] = prixMC(pP, nombreIter, variableAntithetique);

	return seriePrix;
}


// Ecart-type des prix Monte-Carlo (estimateur sans biais)
double STD(vector<double> seriePrix)
{
	int i, longueur = seriePrix.size();
	double somme = 0., sommeCarres = 0.;

	for (i = 0; i < longueur; i++)
	{
		somme += seriePrix[i];
		sommeCarres += seriePrix[i] * seriePrix[i];
	}

	return sqrt(sommeCarres / (longueur - 1) - somme*somme / (longueur*(longueur - 1)));
}


// Une trajectoire de Monte-Carlo
vector<double> Trajectoire(ProduitDerive* pP, int pas, int maxIter)
{
	vector<double> prix(maxIter / pas, 0.);
	int i;

	prix[0] = prixMC(pP, pas);

	for (i = 1; i < maxIter / pas; i++)
		prix[i] = (prix[i - 1] * i + prixMC(pP, pas)) / (i + 1);

	return prix;
}


// Fonction donnant à nombre d'itérations donné, la log-variance du prix Monte-Carlo
double stdMC(ProduitDerive* pP, int nombreIter, int nombreSimulations, bool variableAntithetique)
{
	vector<double> prixMC;
	double std;
	int i;

	std = STD(serieMC(pP, nombreIter, nombreSimulations, variableAntithetique));

	return log(std);
}

// Fonction estimant log(variance du prix MC) en fonction du nombre d'itérations (en puissances de 2)
vector<double> stdIter(ProduitDerive* pP, int expMin, int expMax, int nombreSimulations, bool variableAntithetique)
{
	// Le nombre d'itérations sera les puissances de 2, de 2^expMin à 2^expMax
	vector<double> logStd(expMax - expMin + 1);
	vector<double> prixMC;
	double std;
	int i;

	for (i = expMin; i <= expMax; i++)
	{
		prixMC = serieMC(pP, 1 << i, nombreSimulations, variableAntithetique);
		logStd[i - expMin] = log(STD(prixMC));
	}

	return logStd;
}