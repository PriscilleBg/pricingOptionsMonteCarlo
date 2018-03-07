#include "GenerateurMT.h"
#include <vector>
#include <iostream>

using namespace std;


double GenerateurMT::unif()
{
	unsigned long long xnp1, y;
	int i;

	// Calcul de x_(n+1)
	xnp1 = suiteX[m] ^ (((suiteX[0]>>sep)<<sep) | (suiteX[1] % 1<<sep));
	if (xnp1 % 2)
		xnp1 = xnp1 >> 1;
	else
		xnp1 = (xnp1 >> 1) ^ a;

	// Mise à jour de la suite xn
	for (i = 0; i < (longRecurrence - 1); i++)
		suiteX[i] = suiteX[i + 1];

	suiteX[longRecurrence - 1] = xnp1;


	// Calcul de la sortie
	y = xnp1 ^ ((xnp1 >> u)&d);
	y = y ^ ((y << s)&b);
	y = y ^ ((y << t)&c);
	y = y ^ (y >> l);

	y = y ? y - 1 : y;

	// Le format double contient 52 bits de précision
	// Mais diviser par 1<<52 en une fois engendre une erreur...
	return ((y>>12)/(double)(1<<26))/(double)(1<<26);
}


GenerateurMT::GenerateurMT(unsigned long long x0) : suiteX(vector<unsigned long long>(312))
{
	// Les paramètres choisis correspondent au MT19937-64
	longRecurrence = 312;
	sep = 31;
	m = 156;
	s = 17;
	t = 37;
	u = 29;
	l = 43;

	a = 0x9908B0DFULL;
	b = 0x71D67FFFEDA60000ULL;
	c = 0xFFF7EEE000000000ULL;
	d = 0x5555555555555555ULL;

	unsigned long long f = 6364136223846793005;

	suiteX[0] = x0;
	for (int i = 1; i < longRecurrence; i++)
		suiteX[i] = f * (suiteX[i - 1] ^ (suiteX[i - 1] >> 62)) + a;

}

GenerateurMT::GenerateurMT() : suiteX(vector<unsigned long long>(312))
{
	int x0 = 0;

	// Les paramètres choisis correspondent au MT19937-64
	longRecurrence = 312;
	sep = 31;
	m = 156;
	s = 17;
	t = 37;
	u = 29;
	l = 43;

	a = 0x9908B0DFULL;
	b = 0x71D67FFFEDA60000ULL;
	c = 0xFFF7EEE000000000ULL;
	d = 0x5555555555555555ULL;

	unsigned long long f = 6364136223846793005;

	suiteX[0] = x0;
	for (int i = 1; i < longRecurrence; i++)
		suiteX[i] = f * (suiteX[i - 1] ^ (suiteX[i - 1] >> 62)) + a;
}