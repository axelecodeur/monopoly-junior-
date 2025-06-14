#pragma once
#include "Color.hpp"
#include <string>

class Joueur;
class Plateau;


class Carte
{
private:
	std::string nom;

public:
	Carte(const std::string& nom) : nom(nom) {}
	const std::string& getNom() const { return nom; }
	virtual void action(Joueur&, Plateau&) = 0;
};



class CarteStandGratuit : public Carte
{
private:
	const Color color;
public:
	CarteStandGratuit(Color color) : Carte("STAND GRATUIT " + colorToString(color)), color(color) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CarteAllerCase : public Carte
{
private:
	int position;
	const std::string raison;
	int price;
public:
	CarteAllerCase(int position, const std::string& raison, int price = 0)
		: Carte("ALLER À LA CASE " + std::to_string(position) + " (" + raison + ")"), position(position), raison(raison), price(price) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};



class CartePrendsTrain : public Carte
{
private:
	const std::string color;
public:
	CartePrendsTrain(const std::string& color) : Carte("PRENDS LE TRAIN " + color), color(color) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};