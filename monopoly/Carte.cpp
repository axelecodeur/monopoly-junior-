#include <iostream>

#include "Carte.hpp"
#include "Joueur.hpp"
#include "Plateau.hpp"


void CarteStandGratuit::action(Joueur& joueur, Plateau& plateau)
{
	if (joueur.getColor() == color)
	{
		std::cout << joueur.getNom() << " a tire une carte Stand Gratuit de couleur " << colorToString(color) << ".\n";
		std::cout << "Il peut construire 2 stand gratuit de couleur " << colorToString(color) << ".\n";
		joueur.addStandsGratuits(2);
	}
	else
	{
		std::cout << joueur.getNom() << " a tire une carte Stand Gratuit de couleur " << colorToString(color) << ", mais il ne peut pas construire de stand de cette couleur.\n";
	}
}


void CarteAllerCase::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << "Il avance a la case " << position << " pour la raison suivante: " << raison << ".\n";

	if (price != 0) {
		std::cout << joueur.getNom() << " doit payer " << price << " pour aller a cette case.\n";
		joueur.setArgent(joueur.getArgent() - price);
		plateau.getBanque().setFortune(plateau.getBanque().getFortune() + price);
	}

	if (position < joueur.getPosition()) {
		std::cout << joueur.getNom() << " passe par la case Depart et reçoit un bonus de 2.\n";
		joueur.setArgent(joueur.getArgent() + 2);
	}

	joueur.setPosition(position);
	plateau.getCase(position)->action(joueur, plateau);
}


void CartePrendsTrain::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " relance le de " << getNom() << ".\n";

	int de = std::rand() % 6 + 1; // Lancer un de a 6 faces
	std::cout << joueur.getNom() << " a lance un de et a obtenu: " << de << ".\n";
	joueur.deplacer(de);
	Case* c = plateau.getCase(joueur.getPosition());
	std::cout << joueur.getNom() << " est sur la case: " << c->getNom() << ".\n";

	c->action(joueur, plateau);

}