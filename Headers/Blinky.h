#pragma once 
#include "Ghost.h"

class Blinky: public Ghost {
	void _search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) override;
public:
	Blinky(sf::RenderWindow* win);
};