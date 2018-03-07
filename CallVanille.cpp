#include "CallVanille.h"

// Approximation de la fonction de répartition de la loi normale (Cf Lamberton & Lapeyre)
double F(double x)
{
	double p = 0.2316419;
	double t = 1 / (1 + p*x);
	if (x >= 0)
		return 1 - exp(-x*x / 2)*t*(0.319381530 + t * (-0.356563782 + t*(1.781477937 + t*(-1.821255978 + 1.330274429*t)))) / sqrt(2.*3.14159265359);
	else
		return 1 - F(-x);
}

// Utilise un développement en série entière pour
// Diverge pour les réels supérieurs à 7 : à partir de 6, on tronque à 0 ou 1 (sachant que F(-6) < 10e-9)
double FSerie(double x)
{
	double precision = 1e-8, resultat = x, terme = x, x2 = x*x;
	if (abs(x) > 6)
		return x > 0 ? 1 : 0.;
	// terme = (-1)^n * x^(2n+1)/(2n+1)!
	int n = 1, fac = 1;
	do
	{
		terme = -terme * x2 / (2 * n);
		resultat += terme / (2 * n + 1);
		n++;
	} while (abs(terme) > precision);

	return resultat / sqrt(2.*3.141592653589793)+0.5;
}



CallVanille::CallVanille(double S0, double K, double r, double sigma, double T, GenerateurAleatoire* pU) : S0(S0), K(K), r(r), sigma(sigma), T(T), pU(pU)
{}

// Renvoie un pay-off actualisé
double CallVanille::payoff()
{
	double St = S0*exp((r - sigma*sigma / 2)*T + sqrt(T)*sigma*(pU -> norm()));
	return (St > K ? St - K : 0)*exp(-r*T);
}

// Renvoie la moyenne de deux prix par la méthode antithétique
double CallVanille::payoffAT()
{
	double W = pU->norm();

	double St = S0*exp((r - sigma*sigma / 2)*T);
	double expW = exp(sqrt(T)*sigma*(W));

	double St1 = St*expW;
	double St2 = St / expW;
	return ((St1 > K ? St1 - K : 0) + (St2 > K ? St2 - K : 0))/2*exp(-r*T);
}

double CallVanille::prixBS()
{
	double d1 = (log(S0 / K) + (r + sigma*sigma / 2)*T) / (sigma*sqrt(T));
	double d2 = d1 - sigma*sqrt(T);
	return (S0*F(d1) - K*exp(-r*T)*F(d2));
}