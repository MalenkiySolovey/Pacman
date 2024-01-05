#pragma once
#include "Ghost.h"

class Inky: public Ghost {
	void _search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) override;
public:
	Inky(sf::RenderWindow* win);
};