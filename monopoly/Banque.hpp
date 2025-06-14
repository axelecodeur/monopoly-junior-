#pragma once


class Joueur;


class Banque
{
private:
	int fortune = 0;

public:
	void setFortune(int montant) { fortune = montant; }
	int getFortune() const { return fortune; }
	Banque() {}
};