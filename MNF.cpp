#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GenerateurRL.h"
#include "GenerateurXS.h"
#include "GenerateurSQRT.h"
#include "GenerateurHalton.h"
#include "GenerateurMT.h"
#include "GenerateurBBS.h"
#include "Asiatique.h"
#include "CallVanille.h"
#include "MonteCarlo.h"
#include <vector>
#include <cmath>

using namespace std;


// Arbre : Propagation du sous-jacent
vector <double> Arbre(double S0, int nombrePas, double u, double d)
{
	int i;
	vector<double> St(nombrePas + 1, 0.);
	St[0] = S0;

	for (i = 0; i < nombrePas; i++)
		St[0] *= u;

	for (i = 1; i <= nombrePas; i++)
		St[i] = St[i - 1] * d / u;

	return St;
}

// Arbre : Rétropropagation du call eur
double C_eur(double S0, double K, double r, double sigma, double T, int nombrePas)
{
	int i, j;
	double dt = T / nombrePas;
	double u = exp(sigma*sqrt(dt)), d = exp(-sigma*sqrt(dt));
	double p = (exp(r*dt) - d) / (u - d);
	vector<double> C = Arbre(S0, nombrePas, u, d);

	for (i = 0; i<nombrePas; i++)
		C[i] = C[i] > K ? C[i] - K : 0;

	for (i = 1; i <= nombrePas; i++)
	{
		for (j = 0; j <= nombrePas - i; j++)
			C[j] = (p*C[j] + (1 - p)*C[j + 1]) / exp(r*dt);
	}

	return C[0];
}

// Arbre : Rétropropagation du put eur
double P_eur(double S0, double K, double r, double sigma, double T, int nombrePas)
{
	int i, j;
	double dt = T / nombrePas;
	double u = exp(sigma*sqrt(dt)), d = exp(-sigma*sqrt(dt));
	double p = (exp(r*dt) - d) / (u - d);
	vector<double> C = Arbre(S0, nombrePas, u, d);

	for (i = 0; i<nombrePas; i++)
		C[i] = C[i] < K ? K-C[i] : 0;

	for (i = 1; i <= nombrePas; i++)
	{
		for (j = 0; j <= nombrePas - i; j++)
			C[j] = (p*C[j] + (1 - p)*C[j + 1]) / exp(r*dt);
	}

	return C[0];
}

// Arbre : Rétropropagation du call américain
double C_am(double S0, double K, double r, double sigma, double T, int nombrePas)
{
	int i, j;
	double dt = T / nombrePas;
	double u = exp(sigma*sqrt(dt));
	double d = exp(-sigma*sqrt(dt));
	double p = (exp(r*dt) - d) / (u - d);

	vector<double> C = Arbre(S0, nombrePas, u, d);
	vector<double> Ct;

	for (i = 0; i<=nombrePas; i++)
		C[i] = C[i] > K ? C[i] - K : 0;


	for (i = 1; i <= nombrePas; i++)
	{
		// Valeur de (St - K)+
		Ct = Arbre(S0, nombrePas - i, u, d);
		for (j = 0; j<=nombrePas - i; j++)
			Ct[j] = Ct[j]>K ? Ct[j] - K : 0.;
		
		for (j = 0; j <= nombrePas - i; j++)

		// Valeur du call à cette date
		for (j = 0; j <= nombrePas - i; j++)
		{
			C[j] = (p*C[j] + (1 - p)*C[j + 1]) / exp(r*dt);
			if (C[j] >= Ct[j])
				C[j] = C[j];
			else
				C[j] = Ct[j];
		}
	}

	return C[0];
}

// Arbre : Rétropropagation du put américain
double P_am(double S0, double K, double r, double sigma, double T, int nombrePas)
{
	int i, j;
	double dt = T / nombrePas;
	double u = exp(sigma*sqrt(dt));
	double d = exp(-sigma*sqrt(dt));
	double p = (exp(r*dt) - d) / (u - d);

	vector<double> C = Arbre(S0, nombrePas, u, d);
	vector<double> Ct;

	for (i = 0; i <= nombrePas; i++)
		C[i] = C[i] < K ? K - C[i] : 0;


	for (i = 1; i <= nombrePas; i++)
	{
		// Valeur de (St - K)+
		Ct = Arbre(S0, nombrePas - i, u, d);
		for (j = 0; j <= nombrePas - i; j++)
			Ct[j] = Ct[j] < K ? K - Ct[j] : 0.;

		for (j = 0; j <= nombrePas - i; j++)

			// Valeur du call à cette date
		for (j = 0; j <= nombrePas - i; j++)
		{
			C[j] = (p*C[j] + (1 - p)*C[j + 1]) / exp(r*dt);
			if (C[j] >= Ct[j])
				C[j] = C[j];
			else
				C[j] = Ct[j];
		}
	}

	return C[0];
}


int main()
{
	int i, N;

	// Générateurs pseudo-aléatoires
	GenerateurBBS BBS;
	GenerateurMT MT;
	GenerateurRL RL;
	GenerateurXS XS;

	// Générateur pour pseudo Monte-Carlo
	GenerateurSQRT SQRT;
	GenerateurHalton HA;

	// Fichiers de sortie
	ofstream generateursUnif, generateursNorm, logVariancesCall;
	generateursUnif.open("generateursUnif.csv");
	generateursNorm.open("generateursNorm.csv");
	logVariancesCall.open("logVariancesCall.csv");

	// Tests des générateurs
	N = 10000;
	generateursUnif << "BBS;MT;RL;XS;SQRT;HA" << endl;
	generateursNorm << "BBS;MT;RL;XS;SQRT;HA" << endl;

	for (i = 0; i < N; i++)
	{
		generateursUnif << BBS.unif() << ";" << MT.unif() << ";" << RL.unif() << ";" << XS.unif() << ";" << SQRT.unif() << ";" << HA.unif() << endl;
		generateursNorm << BBS.norm() << ";" << MT.norm() << ";" << RL.norm() << ";" << XS.norm() << ";" << SQRT.norm() << ";" << HA.norm() << endl;
	}


	// Calcul de la variance selon le nombre d'itération et selon le générateur
	CallVanille CallMT(100., 100., 0.01, 0.2, 1., &RL);
	CallVanille CallSQRT(100., 100., 0.01, 0.2, 1., &SQRT);
	CallVanille CallHA(100., 100., 0.01, 0.2, 1., &HA);

	int nombreSim = 100;

	logVariancesCall << "log(N);MT;SQRT;HA;MT+Anti;SQRT+Anti" << endl;
	for (i = 4; i < 18; i++)
	{
		cout << (1 << i) << endl;
		logVariancesCall << log(1 << i) << ";"
			<< stdMC(&CallMT, 1 << i, nombreSim, false) << ";"
			<< stdMC(&CallSQRT, 1 << i, nombreSim, false) << ";"
			<< stdMC(&CallHA, 1 << i, nombreSim, false) << ";"
			<< stdMC(&CallMT, 1 << i, nombreSim, true) << ";"
			<< stdMC(&CallSQRT, 1 << i, nombreSim, true) << endl;
	}

	generateursUnif.close();
	generateursNorm.close();
	logVariancesCall.close();
	 
	return 0;
}