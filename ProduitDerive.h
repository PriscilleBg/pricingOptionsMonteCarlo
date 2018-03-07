#pragma once
#include "GenerateurAleatoire.h"
#include <cmath>


class ProduitDerive
{
public:
	virtual double payoff() = 0;
	virtual double payoffAT() = 0;
};