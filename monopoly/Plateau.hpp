#pragma once

#include "Banque.hpp"
#include "Case.hpp"
#include <list>




class Plateau
{
private:
	Case* cases[32];
	std::list<Carte*> piocheCommune;
	Banque banque;
public:
	Plateau();
	Case* getCase(int position) const {
		return cases[position];
	}
	Banque& getBanque() {
		return banque;
	}
};