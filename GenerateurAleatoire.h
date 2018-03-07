#pragma once


// Classe générale pour tous les générateurs de nombres pseudo-aléatoires
class GenerateurAleatoire
{
public:
	// Fonction virtuelle génératrice de nombres pseudo-aleatoires
	virtual double unif() = 0;
	// Fonction génératrice de gaussiennes centrées réduites
	double norm();
};