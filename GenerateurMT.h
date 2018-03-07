#pragma once
#include "GenerateurAleatoire.h"
#include <vector>
using namespace std;

class GenerateurMT :
	public GenerateurAleatoire
{
private:
	int longRecurrence, sep, m, s, t, u, l;
	unsigned long long a, b, c, d;
	vector<unsigned long long> suiteX;
public:
	GenerateurMT(unsigned long long x0);
	GenerateurMT();
	double unif();
};