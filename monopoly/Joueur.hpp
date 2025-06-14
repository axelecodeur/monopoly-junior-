#pragma once

#include <string>
#include <vector>
#include "Color.hpp"

class CasePropriete;

class Joueur
{
private:
	int nombreStands;
	Color color;
	std::string nom;
	int argent;
	int position;
	std::vector<CasePropriete*> proprietes;
	int standsGratuits = 0;
public:
	Joueur(const std::string& nom, Color color, int nbStands = 10, int argentInitial = 31)
		: nom(nom), argent(argentInitial), position(0), color(color), nombreStands(nbStands) {}

	void deplacer(int pas);
	const std::string& getNom() const { return nom; }
	int getArgent() const { return argent; }
	void setArgent(int montant) { argent = montant; }

	const std::vector<CasePropriete*>& getProprietes() const { return proprietes; }
	void ajouterPropriete(CasePropriete* propriete) {
		proprietes.push_back(propriete);
	}

	int getPosition() const {
		return position;
	}

	void setPosition(int pos) {
		position = pos;
	}

	Color getColor() const {
		return color;
	}

	void addStandsGratuits(int nb) {
		standsGratuits += nb;
	}

	int getNombreStands() const {
		return nombreStands;
	}

	int getStandsGratuits() const {
		return standsGratuits;
	}

	void retirerStands(int nb) {
		if (nombreStands >= nb) {
			nombreStands -= nb;
		}
		else {
			nombreStands = 0;
		}
	}

	void retirerStandsGratuits(int nb) {
		if (standsGratuits >= nb) {
			standsGratuits -= nb;
		}
		else {
			standsGratuits = 0;
		}
	}

};