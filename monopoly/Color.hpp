#pragma once
#include <string>



enum struct Color {
	VIOLET,
	BLANC,
	ROSE,
	ORANGE,
	ROUGE,
	JAUNE,
	VERT,
	BLEUE,

	NOMBRE_COULEUR
};


inline std::string colorToString(Color color) {
	switch (color) {
	case Color::VIOLET: return "Violet";
	case Color::BLANC: return "Blanc";
	case Color::ROSE: return "Rose";
	case Color::ORANGE: return "Orange";
	case Color::ROUGE: return "Rouge";
	case Color::JAUNE: return "Jaune";
	case Color::VERT: return "Vert";
	case Color::BLEUE: return "Bleu";
	default: return "Inconnu";
	}
}
