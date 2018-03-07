#include "Asiatique.h"


Asiatique::Asiatique(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU) : S0(S0), K(K), r(r), sigma(sigma), T(T), nombrePas(nombrePas), pU(pU)
{
}


// Simule un pay-off actualisé
double Asiatique::payoff()
{
	double W, moyenne = 0., St = S0;
	int i;

	for (i = 0; i < nombrePas; i++)
	{
		W = pU->norm();
		St = St * exp((r - sigma*sigma / 2)*T / nombrePas + sqrt(T / nombrePas)*sigma*W);
		moyenne += St;
	}
	moyenne /= nombrePas;
	return (moyenne>K ? moyenne - K : 0)*exp(-r*T);
}

double Asiatique::payoffAT()
{
	double W, moyenne1 = 0., moyenne2 = 0., St1 = S0, St2 = 0;
	double expW, increment = exp((r - sigma*sigma / 2)*T / nombrePas);
	int i;

	for (i = 0; i < nombrePas; i++)
	{
		W = pU->norm();

		expW = exp(sqrt(T / nombrePas)*sigma*W);
		St1 = St1 * increment*expW;
		St2 = St2 * increment / expW;
		moyenne1 += St1;
		moyenne2 += St2;
	}
	moyenne1 /= nombrePas;
	moyenne2 /= nombrePas;
	return ((moyenne1>K ? moyenne1 - K : 0) + (moyenne2 > K ? moyenne2 - K : 0)) / 2 * exp(-r*T);
}