#include "GenerateurBBS.h"


GenerateurBBS::GenerateurBBS(long long x0) : xn(x0), M(10001443 * 13000303)
{
}

GenerateurBBS::GenerateurBBS() : xn(1234567), M(10001443 * 13000303)
{
}


double GenerateurBBS::unif()
{
	xn = (xn*xn) % M;
	return (xn % (1 << 16)) / (double)(1 << 16);
}