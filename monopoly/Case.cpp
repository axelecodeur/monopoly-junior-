#include <iostream>

#include "Case.hpp"
#include "Joueur.hpp"
#include "Carte.hpp"
#include "Plateau.hpp"


void CaseAllerAuCafe::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " Paye 3 pour aller au cafe.\n";
}

void CaseCafe::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " Prends son cafe et ne fait rien \n";
}



void CaseChance::action(Joueur& joueur, Plateau& plateau)
{
	if (pioche.size() == 0) {
		std::cout << "La pioche est vide. Pas d'action possible.\n";
		return;
	}

	Carte* carte = pioche.front();

	// put the card at the end of the pile
	pioche.pop_front();
	pioche.push_back(carte);

	std::cout << joueur.getNom() << " a tire une carte " << carte->getNom() << ".\n";
	carte->action(joueur, plateau);

}



void CaseDepart::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " est sur la case Depart et reçoit un bonus de " << bonus << ".\n";
	joueur.setArgent(joueur.getArgent() + bonus);
}

void CasePropriete::action(Joueur& joueur, Plateau& plateau)
{
	if (estpossede() && &joueur != proprio) {
		int multiplieur = 1;

		std::cout << joueur.getNom() << " est sur la case " << getNom() << " qui est deja possedee par " << proprio->getNom() << "\n";

		for (const auto* prop : proprio->getProprietes()) {
			if (prop->getColor() == color && prop != this) {
				multiplieur = 2; // Double le loyer si le proprio possede les deux cases de la meme couleur
				std::cout << "Le proprietaire " << proprio->getNom() << " possede egalement une autre propriete de la meme couleur.\n";
				std::cout << "Le loyer est double! \n";
				break;
			}
		}

		std::cout << "Il doit payer un loyer de " << loyer * multiplieur << ".\n";
		joueur.setArgent(joueur.getArgent() - loyer * multiplieur);
		proprio->setArgent(proprio->getArgent() + loyer * multiplieur);
	}
	else if (&joueur == proprio) {
		std::cout << joueur.getNom() << " est sur sa propre case " << getNom() << ".\n";
		std::cout << "Il ne doit rien payer.\n";
	}
	else {
		if (joueur.getNombreStands() == 0)
		{
			std::cout << joueur.getNom() << " n'a pas de stand et ne peut pas acheter cette propriete.\n";
			return;
		}


		std::cout << joueur.getNom() << " est sur la case " << getNom() << ".\n";
		std::cout << "Il peut acheter cette propriete pour " << prixAchat << ".\n";

		std::string reponse;

		std::cout << "Voulez-vous acheter cette propriete ? (oui/non) : ";
		std::cin >> reponse;
		std::cin.ignore();

		while (reponse != "oui" && reponse != "non") {
			std::cout << "Reponse invalide. Veuillez repondre par 'oui' ou 'non': ";
			std::cin >> reponse;
			std::cin.ignore();
		}

		if (reponse == "non") {
			std::cout << joueur.getNom() << " a choisi de ne pas acheter la propriete.\n";
			return;
		}

		std::cout << "Le prix d'achat est de " << prixAchat << ".\n";

		if (joueur.getStandsGratuits() > 0) {
			std::string reponse2;

			std::cout << "Voulez-vous utiliser un stand gratuit ? (oui/non) : ";
			std::cin >> reponse2;
			std::cin.ignore();

			while (reponse2 != "oui" && reponse2 != "non") {
				std::cout << "Reponse invalide. Veuillez repondre par 'oui' ou 'non': ";
				std::cin >> reponse2;
				std::cin.ignore();
			}

			if (reponse2 == "oui") {
				std::cout << joueur.getNom() << " a choisi d'utiliser un stand gratuit.\n";

				joueur.retirerStandsGratuits(1);
				// on ajoute au joueur le prix d'achat qui sera retirer après
				// pour ne pas que le joueur perde de l'argent
				joueur.setArgent(joueur.getArgent() + prixAchat);
			}
			else {
				std::cout << joueur.getNom() << " a choisi de ne pas utiliser de stand gratuit.\n";
			}
		}



		if (joueur.getArgent() >= prixAchat) {
			joueur.setArgent(joueur.getArgent() - prixAchat);
			proprio = &joueur;
			joueur.ajouterPropriete(this);
			std::cout << joueur.getNom() << " a achete la propriete.\n";
			std::cout << "Il lui reste " << joueur.getArgent() << " euros.\n";
			joueur.retirerStands(1);
		}
		else {
			std::cout << joueur.getNom() << " n'a pas assez d'argent pour acheter cette propriete.\n";
		}
	}
}


void CaseTrain::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " relance le de.\n";

	int de = std::rand() % 6 + 1; // Lancer un de a 6 faces
	std::cout << joueur.getNom() << " a lance un de et a obtenu: " << de << ".\n";
	joueur.deplacer(de);
	Case* c = plateau.getCase(joueur.getPosition());
	std::cout << joueur.getNom() << " est sur la case: " << c->getNom() << ".\n";

	c->action(joueur, plateau);

}


void CaseFortune::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " est sur la case Fortune.\n";
	std::cout << "Il reçoit un bonus de " << plateau.getBanque().getFortune() << ".\n";
	joueur.setArgent(joueur.getArgent() + plateau.getBanque().getFortune());
}


void CaseSpectacle::action(Joueur& joueur, Plateau& plateau)
{
	std::cout << joueur.getNom() << " assiste au spectacle " << getNom() << " pour 2" << ".\n";
	joueur.setArgent(joueur.getArgent() - 2);
}