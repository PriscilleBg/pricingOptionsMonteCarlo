#pragma once


// Classe g�n�rale pour tous les g�n�rateurs de nombres pseudo-al�atoires
class GenerateurAleatoire
{
public:
	// Fonction virtuelle g�n�ratrice de nombres pseudo-aleatoires
	virtual double unif() = 0;
	// Fonction g�n�ratrice de gaussiennes centr�es r�duites
	double norm();
};