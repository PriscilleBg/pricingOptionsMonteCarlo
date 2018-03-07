#include "LookbackBarriere.h"

LookbackBarriere::LookbackBarriere(double S0, double K, double r, double sigma, double T, double Percent, int nombrePas, GenerateurAleatoire* pU) : S0(S0), K(K), r(r), sigma(sigma), T(T), Percent(Percent),  nombrePas(nombrePas), pU(pU)
{
}


// Simule un pay-off actualisé
// Option lookback Up and Out
double LookbackBarriere::payoff()
{
	double W, Max = 0., St = S0;
	int i;

	for (i = 0; i < nombrePas; i++)
	{
		W = pU->norm();
		St = St * exp((r - sigma*sigma / 2)*T / nombrePas + sqrt(T / nombrePas)*sigma*W);
		if (Max<St) {
			Max = St;
		}
	}

	if (Max < K * Percent)
	{
		return (Max>K ? Max - K : 0)*exp(-r*T);
	}

	else return 0;

}


double LookbackBarriere::payoffAT()
{
	double W, Max1 = 0., Max2 = 0., St1 = S0, St2 = S0, prix1 = 0., prix2 = 0.;
	int i;

	for (i = 0; i < nombrePas; i++)
	{
		W = pU->norm();
		St1 = St1 * exp((r - sigma*sigma / 2)*T / nombrePas + sqrt(T / nombrePas)*sigma*W);
		St2 = St2 * exp((r - sigma*sigma / 2)*T / nombrePas - sqrt(T / nombrePas)*sigma*W);
		if (Max1<St1)
			Max1 = St1;
		if (Max2<St2)
			Max2 = St2;
	}

	if (Max1 < K * Percent)
		prix1 = (Max1>K ? Max1 - K : 0)*exp(-r*T);
	if (Max2 < K * Percent)
		prix2 = (Max2>K ? Max2 - K : 0)*exp(-r*T);

	else return (prix1 + prix2) / 2;
}