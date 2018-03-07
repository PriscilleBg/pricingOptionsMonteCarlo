#include "GenerateurSQRT.h"
#include <cmath>

// Constructeur imposant les nombres premiers
GenerateurSQRT::GenerateurSQRT(int p1, int p2) : sqrtP1(sqrt(p1)), sqrtP2(sqrt(p2)), x1n(0.), x2n(0.), P1ouP2(true)
{
}

// Constructeur de flemmard
GenerateurSQRT::GenerateurSQRT() : sqrtP1(sqrt(431)), sqrtP2(sqrt(311)), x1n(0.), x2n(0.), P1ouP2(true)
{
}

// Générateur
double GenerateurSQRT::unif()
{
	P1ouP2 = !P1ouP2;

	if (P1ouP2)
	{
		x1n += sqrtP1;
		x1n -= (int)x1n;
		return x1n;
	}
	else
	{
		x2n += sqrtP2;
		x2n -= (int)x2n;
		return x2n;
	}
}