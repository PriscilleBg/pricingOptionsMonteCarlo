#include "GenerateurHalton.h"


GenerateurHalton::GenerateurHalton() : p1(431), p2(311), n(0), P1ouP2(true)
{
}

GenerateurHalton::GenerateurHalton(int p1, int p2) : p1(p1), p2(p2), n(0), P1ouP2(true)
{
}

double GenerateurHalton::unif()
{
	int p = P1ouP2 ? p1 : p2;
	// pk représente p^k
	int m = n, pk = p;
	P1ouP2 = !P1ouP2;
	double x = 0.;

	while (m > 0)
	{
		x += (m%p) / (double)pk;
		pk *= p;
		m /= p;
	}
	n += 1;
	return x;
}