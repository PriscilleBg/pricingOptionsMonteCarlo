#include "GenerateurAleatoire.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>


double GenerateurAleatoire::norm()
{
	double u, v;
	u = unif();
	u = sqrt(-2. * log(u ? u : 1.));
	v = 6.28318530718*unif();
	return u * cos(v);
}