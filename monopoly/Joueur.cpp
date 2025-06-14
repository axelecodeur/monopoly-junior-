#include <iostream>

#include "Joueur.hpp"



void Joueur::deplacer(int pas)
{
	if (position + pas > 31) {
		std::cout << nom << " passe par la case Depart et reçoit un bonus de 2.\n";
		argent += 2;
	}
	position = (position + pas) % 32;
}
