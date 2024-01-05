#pragma once
#include "Ghost.h"

class Clyde: public Ghost {
	void _search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) override;
public:
	Clyde(sf::RenderWindow* win);
};