#pragma once
#include "Ghost.h"

class Pinky: public Ghost {
	void _search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) override;
public:
	Pinky(sf::RenderWindow* win);
};