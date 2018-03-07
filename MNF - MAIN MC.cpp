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
#include "LookbackBarriere.h"
#include "lookback.h"
#include "MonteCarlo.h"
#include "VariableControle.h"
#include <vector>
#include <cmath>

using namespace std;


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
	ofstream generateursUnif, generateursNorm, logVariancesCallVC, convergence, prixEtDates, seriePrixMC;
	
	//generateursUnif.open("generateursUnif.csv");
	//generateursNorm.open("generateursNorm.csv");
	logVariancesCallVC.open("logVariancesCallVC2.csv");
	//convergence.open("convergence.csv");
	//prixEtDates.open("datesAsiatique3.csv");
	//seriePrixMC.open("seriePrixMC.csv");

	cout << "Debut\n";


	// Tests des générateurs
	
	N = 10000;
	generateursUnif << "BBS;MT;RL;XS;SQRT;HA" << endl;
	generateursNorm << "BBS;MT;RL;XS;SQRT;HA" << endl;

	for (i = 0; i < N; i++)
	{
		generateursUnif << BBS.unif() << ";" << MT.unif() << ";" << RL.unif() << ";" << XS.unif() << ";" << SQRT.unif() << ";" << HA.unif() << endl;
		generateursNorm << BBS.norm() << ";" << MT.norm() << ";" << RL.norm() << ";" << XS.norm() << ";" << SQRT.norm() << ";" << HA.norm() << endl;
	}

	cout << "Tests generateurs termines - trajectoires..." << endl;
	

	// Trajectoires de convergence vers le prix (Black & Scholes)
	CallVanille CallMT(100., 100., 0.01, 0.2, 1., &MT);
	Asiatique Asiat(100., 100., 0.01, 0.2, 1., 12, &MT);
	Lookback LookB(100., 100., 0.01, 0.2, 1., 12, &MT);
	LookbackBarriere LookBBar(100., 100., 0.01, 0.2, 1., 1.5, 12, &MT);
	
	int pasTrajectoires = 1e4;
	int maxIterTrajectoires = 1e6;
	vector<double> trajCall1 = Trajectoire(&CallMT, pasTrajectoires, maxIterTrajectoires);
	cout << "Call1 OK";
	vector<double> trajCall2 = Trajectoire(&CallMT, pasTrajectoires, maxIterTrajectoires);
	cout << "\rCall2 OK";
	vector<double> trajCall3 = Trajectoire(&CallMT, pasTrajectoires, maxIterTrajectoires);
	cout << "\rCall3 OK";
	vector<double> trajAsiat = Trajectoire(&CallMT, pasTrajectoires, maxIterTrajectoires);
	cout << "\rAsiatique OK";
	vector<double> trajLookB = Trajectoire(&LookB, pasTrajectoires, maxIterTrajectoires);
	cout << "\rLookback OK";
	vector<double> trajLookBBar = Trajectoire(&LookBBar, pasTrajectoires, maxIterTrajectoires);
	cout << "\rLookback barriere OK" << endl;

	convergence << "Nombre Iterations;Prix BS;Call1;Call2;Call3;Asiat;Lookback;Lookback Barriere" << endl;
	for (i = 0; i < maxIterTrajectoires / pasTrajectoires; i++)
	{
		convergence << i*pasTrajectoires << ";"
			<< CallMT.prixBS() << ";"
			<< trajCall1[i] << ";"
			<< trajCall2[i] << ";"
			<< trajCall3[i] << ";"
			<< trajAsiat[i] << ";"
			<< trajLookB[i] << ";"
			<< trajLookBBar[i] << endl;
	}

	cout << "Trajectoires terminees - Series de prix..." << endl;
	

	// Série de prix MC avec différents nombres de simulations, à rendre en histogrammes
	seriePrixMC << "N;1e3;1e4;1e5;1e6" << endl;
	cout << "Serie de prix 0% effectues";
	for (i = 0; i < 100; i++)
	{
		cout << "\rSerie de prix " << i << "% effectues";
		seriePrixMC << i << ";"
			<< prixMC(&CallMT, 1e3) << "; "
			<< prixMC(&CallMT, 1e4) << ";"
			<< prixMC(&CallMT, 1e5) << ";"
			<< prixMC(&CallMT, 1e6) << endl;
	}

	cout << "\rSeries de prix OK - Nombre de dates pour asiat et LB..." << endl;
	

	// Prix de l'asiatique et des lookback en fonction du nombre de dates
	
	int NIter = 1e5;

	prixEtDates << "Nombre Dates;Asiatique;Lookback;Lookback Barriere" << endl;
	cout << "Prix et dates 0% effectues";
	for (i = 21; i < 25; i++)
	{
		cout << "\rPrix et dates "<< i*4 <<"% effectues";
		Asiatique Asiat(100., 100., 0.01, 0.2, 1., i, &MT);
		Lookback LookB(100., 100., 0.01, 0.2, 1., i, &MT);
		LookbackBarriere LookBBar(100., 100., 0.01, 0.2, 1., 1.5, i, &MT);
		prixEtDates << i << ";"
			<< prixMC(&Asiat, NIter) << ";"
			<< prixMC(&LookB, NIter) << ";"
			<< prixMC(&LookBBar, NIter) << endl;
	}
	
	cout << "\rDates OK - variance..." << endl;
	

	// Calcul de la variance selon le nombre d'itérations et la méthode de réduction de la variance
	CallVanille CallSQRT(100., 100., 0.01, 0.2, 1., &SQRT);
	CallVanille CallHA(100., 100., 0.01, 0.2, 1., &HA);
	VariableControle VarCon(100., 100., 0.01, 0.2, 1., 12, &MT, &CallMT);

	int nombreSim = 100;

	logVariancesCallVC << "log(N);VC" << endl;
	cout << "Nombre d'iterations :";
	for (i = 15; i < 18; i++)
	{
		cout << "\rNombre d'iterations : " << (1 << i);
		logVariancesCallVC << log(1 << i) << ";"
			<< stdMC(&VarCon, 1 << i, nombreSim, false) << endl;
	}

	cout << "\rFIN\n";

	generateursUnif.close();
	generateursNorm.close();
	logVariancesCallVC.close();
	convergence.close();
	prixEtDates.close();
	return 0;
}