#include "VariableControle.h"


VariableControle::VariableControle(double S0, double K, double r, double sigma, double T, int nombrePas, GenerateurAleatoire* pU, CallVanille* pBS) : S0(S0), K(K), r(r), sigma(sigma), T(T), nombrePas(nombrePas), pU(pU), pBS(pBS)
{
}


// Simule un pay-off actualisé
// Option lookback Up and Out
double VariableControle::payoff()
{
    double W,A,C,BS, moyenne=0., St = S0;
    int i;
    
    BS = pBS->prixBS();
    
    for (i = 0; i < nombrePas; i++)
    {
        W = pU->norm();
        St = St * exp((r - sigma*sigma / 2)*T / nombrePas + sqrt(T / nombrePas)*sigma*W);
        moyenne += St;
    }
    moyenne /= nombrePas;
    
    A = (moyenne>K ? moyenne - K : 0)*exp(-r*T);
    C = (St > K ? St - K : 0)*exp(-r*T);
      
	return A - C + BS;
}

double VariableControle::payoffAT()
{
	double W, A, C, BS, moyenne1 = 0., moyenne2 = 0., St1= S0, St2 = S0;
	int i;

	BS = pBS->prixBS();

	for (i = 0; i < nombrePas; i++)
	{
		W = pU->norm();
		St1 = St1 * exp((r - sigma*sigma / 2)*T / nombrePas + sqrt(T / nombrePas)*sigma*W);
		moyenne1 += St1;
		St2 = St2 * exp((r - sigma*sigma / 2)*T / nombrePas - sqrt(T / nombrePas)*sigma*W);
		moyenne2 += St2;

	}
	moyenne1 /= nombrePas;
	moyenne2 /= nombrePas;

	A = ((moyenne1>K ? moyenne1 - K : 0) + (moyenne2>K ? moyenne2 - K : 0))/2.*exp(-r*T);
	C = ((St1 > K ? St1 - K : 0) + (St2 > K ? St2 - K : 0))*exp(-r*T)/2.;

	return (A - C + BS);
}