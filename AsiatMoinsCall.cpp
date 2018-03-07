#include "AsiatMoinsCall.h"


AsiatMoinsCall::AsiatMoinsCall(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU) : S0(S0), K(K), r(r), sigma(sigma), T(T), nombrePas(nombrePas), pU(pU)
{
}

double AsiatMoinsCall::payoff()
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
	return ((moyenne>K ? moyenne - K : 0) - (St > K ? St - K : 0.))*exp(-r*T);
}

double AsiatMoinsCall::payoffAT()
{
	double W, moyenne1 = 0., moyenne2 = 0., St1 = S0, St2 = 0, payoff1, payoff2;
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

	payoff1 = (moyenne1 > K ? moyenne1 - K : 0.) - (St1 > K ? St1 - K : 0.);
	payoff2 = (moyenne2 > K ? moyenne2 - K : 0.) - (St2 > K ? St2 - K : 0.);

	return (payoff1 + payoff2) / 2 * exp(-r*T);
}