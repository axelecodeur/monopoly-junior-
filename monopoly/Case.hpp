#pragma once
#include <string>
#include <list>
#include "Color.hpp"

class Joueur;
class Carte;
class Plateau;



class Case
{
protected:
	std::string nom;

public:
	Case(const std::string& nom) : nom(nom) {}
	const std::string& getNom() const { return nom; }
	virtual void action(Joueur&, Plateau&) = 0;
};




class CaseCafe : public Case
{
public:
	CaseCafe(const std::string& nom = "Cafe") : Case(nom) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CaseChance : public Case
{
private:
	std::list<Carte*>& pioche;
public:
	CaseChance(std::list<Carte*>& pioche, const std::string& nom = "CHANCE") : pioche(pioche), Case(nom) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CaseDepart : public Case
{
private:
	int bonus;
public:
	CaseDepart(int bonus = 2) : Case("DEPART"), bonus(bonus) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CasePropriete : public Case
{
private:
	Color color;
	int prixAchat;
	int loyer;
	Joueur* proprio = nullptr;
	bool estpossede() { return proprio != nullptr; }
	Color getColor() const { return color; }
public:
	CasePropriete(const std::string& nom, int prixAchat, Color color) : color(color), Case(nom), prixAchat(prixAchat), loyer(prixAchat) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};



class CaseAllerAuCafe : public Case
{
public:
	CaseAllerAuCafe() : Case("ALLER AU CAFE") {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CaseTrain : public Case
{
private:
	std::string couleur;
public:
	CaseTrain(const std::string& couleur) : Case("TRAIN " + couleur), couleur(couleur) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CaseFortune : public Case
{
public:
	CaseFortune() : Case("FORTUNE") {}
	void action(Joueur& joueur, Plateau& plateau) override;
};


class CaseSpectacle : public Case
{
public:
	CaseSpectacle(const std::string& nom) : Case(nom) {}
	void action(Joueur& joueur, Plateau& plateau) override;
};