#include "GenerateurXS.h"


// Constructeur avec tous les param�tres
GenerateurXS::GenerateurXS(unsigned long long x0, int a1, int a2, int a3) : xn(x0), a1(a1), a2(a2), a3(a3)
{
}

// Constructeur sans param�tre
GenerateurXS::GenerateurXS() : xn(1e16), a1(21), a2(35), a3(4)
{
}

double GenerateurXS::unif()
{
	xn = xn ^ (xn >> a1);
	xn = xn ^ (xn << a2);
	xn = xn ^ (xn >> a3);
	return (xn % (1 << 16)) / ((double)(1 << 16));
}