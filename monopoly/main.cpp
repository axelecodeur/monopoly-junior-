#include <iostream>
#include <string>
#include <random>
#include <time.h>

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Banque.hpp"
#include "Joueur.hpp"

int main()
{
	std::srand((unsigned)std::time(nullptr));


	std::vector<Joueur*> joueurs;


	int numJoueurs = 0;

	std::cout << "Entrez le nombre de joueurs (2-4): ";
	std::cin >> numJoueurs;

	while (numJoueurs < 2 || numJoueurs > 4) {
		std::cout << "Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et 4: ";
		std::cin >> numJoueurs;
	}


	bool color_used[(int)Color::NOMBRE_COULEUR] = { false, false, false, false, false, false, false, false };

	for (int i = 0; i < numJoueurs; ++i) {
		std::string nomJoueur;
		std::cout << "Entrez le nom du joueur " << (i + 1) << ": ";
		std::cin >> nomJoueur;
		std::cin.ignore();

		// assign a random color to each player (one player = one color)
		Color col;
		do {
			col = (Color)(std::rand() % (int)Color::NOMBRE_COULEUR);
		} while (color_used[(int)col]);

		joueurs.push_back(new Joueur(nomJoueur, col));
	}	

	std::vector<int> lancer_de(numJoueurs);
	int index = 0;
	bool player_start = false;

	while (!player_start)
	{
		index = 0;

		for (int i = 0; i < numJoueurs; ++i) {
			// de pour savoir qui joue en premier
			int r = std::rand() % 6 + 1;
			lancer_de[i] = r;
			std::cout << "Joueur " << joueurs[i]->getNom() << " a lance le de et obtenu: " << lancer_de[i] << ".\n";
		}
		// Trouver le joueur avec le plus grand lancer de de
		int max_lancer = lancer_de[0];
		for (int i = 1; i < numJoueurs; ++i) {
			if (lancer_de[i] > max_lancer) {
				max_lancer = lancer_de[i];
				index = i;
			}
		}

		// gerer les egalite
		bool tie = false;
		for (int i = 0; i < numJoueurs; ++i) {
			if (i != index && lancer_de[i] == max_lancer) {
				tie = true;
				std::cout << "Il y a une egalite entre " << joueurs[index]->getNom() << " et " << joueurs[i]->getNom() << ".\n";
			}
		}
		if (!tie) {
			player_start = true;
			std::cout << joueurs[index]->getNom() << " commence le jeu avec un lancer de " << max_lancer << ".\n";
		}
		else {
			std::cout << "Relancez les des pour departager les joueurs.\n";
		}
	}



	Plateau plateau;
	Joueur* gagnant = nullptr;

	std::cout << "\nBienvenue dans le jeu de Monopoly !\n\n";

	while (joueurs.size() != (numJoueurs - 1))
	{
		// j = ref to a ptr du joueur qui doit jouer
		Joueur*& j = joueurs[index % joueurs.size()];

		// nom du joueur
		const std::string& n = j->getNom();



		std::cout << "C'est le tour de " << n << ".\n";
		std::cout << "Appuyez sur Entree pour lancer le de...\n";
		std::cin.get();
		
		int de = std::rand() % 6 + 1; // Lancer un de a 6 faces
		std::cout << n << " a lance un de et a obtenu: " << de << ".\n";


		// Si le joueur passe par la case Depart, il reçoit un bonus de 2 euros
		if (j->getPosition() + de > 31) {
			std::cout << n << " passe par la case Depart et reçoit un bonus de 2.\n";
			j->setArgent(j->getArgent() + 2);
		}


		j->deplacer(de);

		Case* c = plateau.getCase(j->getPosition());

		std::cout << n << " est sur la case: " << c->getNom() << ".\n";
		c->action(*j, plateau);

		if (j->getArgent() <= 0) {
			std::cout << n << " n'a plus d'argent et est elimine du jeu.\n\n";
			delete j; // Liberer la memoire du joueur
			joueurs.erase(joueurs.begin() + index % joueurs.size()); // Supprimer le joueur de la liste
			index--; // Ajuster l'index pour ne pas sauter le prochain joueur
		}
		else {
			std::cout << n << " a maintenant " << j->getArgent() << " euros.\n\n";
		}

		index++;
	}


	// Le jeu est termine, calculer le gagnant (celui qui a le plus d'argent)
	int maxArgent = joueurs[0]->getArgent();
	for (size_t i = 1; i < joueurs.size(); ++i) {
		if (joueurs[i]->getArgent() > maxArgent) {
			maxArgent = joueurs[i]->getArgent();
			gagnant = joueurs[i];
		}
	}

	// Afficher le gagnant
	std::cout << "\n\n\nLe jeu est termine !\n\n\n";
	if (gagnant)
		std::cout << "Le gagnant est " << gagnant->getNom() << " avec " << maxArgent << " euros.\n";
	else 
		std::cout << "bizarre, il n'y a pas de gagnant.\n";


	// Nettoyer la memoire
	for (Joueur* joueur : joueurs) {
		delete joueur;
	}


	std::string t;
	std::cin >> t;
	while (t != "quit")
	{
		std::cout << "Tapez 'quit' pour quitter le jeu.\n";
		std::cin >> t;
	}
}
