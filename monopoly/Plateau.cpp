#include "Plateau.hpp"
#include "Carte.hpp"
#include <vector>
#include <algorithm>


Plateau::Plateau() : piocheCommune()
{

    // Stands gratuits (2 de chaque couleur sauf violet)
    piocheCommune.push_back(new CarteStandGratuit(Color::ORANGE));
    piocheCommune.push_back(new CarteStandGratuit(Color::ORANGE));
    piocheCommune.push_back(new CarteStandGratuit(Color::ROUGE));
    piocheCommune.push_back(new CarteStandGratuit(Color::ROUGE));
    piocheCommune.push_back(new CarteStandGratuit(Color::ROSE));
    piocheCommune.push_back(new CarteStandGratuit(Color::ROSE));
    piocheCommune.push_back(new CarteStandGratuit(Color::BLEUE));
    piocheCommune.push_back(new CarteStandGratuit(Color::BLEUE));
    piocheCommune.push_back(new CarteStandGratuit(Color::VERT));
    piocheCommune.push_back(new CarteStandGratuit(Color::VERT));
    piocheCommune.push_back(new CarteStandGratuit(Color::JAUNE));
    piocheCommune.push_back(new CarteStandGratuit(Color::JAUNE));
    piocheCommune.push_back(new CarteStandGratuit(Color::BLANC));
    piocheCommune.push_back(new CarteStandGratuit(Color::BLANC));
    piocheCommune.push_back(new CarteStandGratuit(Color::VIOLET));





    // Cartes speciales
    piocheCommune.push_back(new CarteAllerCase(14, "Toboggan aquatique"));
    piocheCommune.push_back(new CarteAllerCase(20, "Grand Huit"));
    piocheCommune.push_back(new CarteAllerCase(10, "bus pour le cafe", 3));
    piocheCommune.push_back(new CarteAllerCase(0, "depart"));
    piocheCommune.push_back(new CarteAllerCase(24, "Ballet des dauphins"));
    piocheCommune.push_back(new CarteAllerCase(8, "Feu d'artifice"));
    piocheCommune.push_back(new CartePrendsTrain("BLEU"));
    piocheCommune.push_back(new CartePrendsTrain("ROUGE"));
    piocheCommune.push_back(new CartePrendsTrain("JAUNE"));
    piocheCommune.push_back(new CartePrendsTrain("VERT"));



	std::vector<Carte*> tmp(piocheCommune.begin(), piocheCommune.end());
    std::random_shuffle(tmp.begin(), tmp.end());
	piocheCommune.assign(tmp.begin(), tmp.end());


    Case* c[32] = {
        new CaseDepart(2),
        new CaseChance(piocheCommune),
        new CasePropriete("Jeu de ballons", 1, Color::VIOLET),
        new CasePropriete("Barbe a papa", 1, Color::VIOLET),
        new CaseChance(piocheCommune),
		new CaseTrain("JAUNE"),
        new CasePropriete("Theatre de marionnette", 2, Color::BLANC),
        new CasePropriete("Spectacle de magie", 2, Color::BLANC),
        new CaseSpectacle("Feu d'artifice"),
        new CaseChance(piocheCommune),
        new CaseCafe("Cafe"),
        new CasePropriete("Manege", 2, Color::ROSE),
        new CasePropriete("Pedalos", 2, Color::ROSE),
        new CaseTrain("VERT"),
        new CasePropriete("Toboggan aquatique", 3, Color::ORANGE),
        new CasePropriete("Mini golf", 3, Color::ORANGE),
        new CaseFortune(),
        new CaseChance(piocheCommune),
        new CasePropriete("Jeux videos", 3, Color::ROUGE),
        new CasePropriete("Maison hantee", 3, Color::ROUGE),
        new CaseChance(piocheCommune),
		new CaseTrain("BLEU"),
        new CasePropriete("Promenade en helicoptere", 4, Color::JAUNE),
        new CasePropriete("Promenade a poney", 4, Color::JAUNE),
        new CaseSpectacle("Ballet des dauphins"),
        new CaseChance(piocheCommune),
        new CaseAllerAuCafe(),
        new CasePropriete("Autos tamponneuses", 4, Color::VERT),
        new CasePropriete("Grande roue", 4, Color::VERT),
		new CaseTrain("ROUGE"),
        new CasePropriete("Grand huit", 5, Color::BLEUE),
        new CasePropriete("Montagnes russes", 5, Color::BLEUE)
    };

	for (int i = 0; i < 32; ++i) {
		this->cases[i] = c[i];
	}
}