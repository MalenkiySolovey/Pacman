#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Button.h"

void scanMap(std::vector<std::vector<_i64>>& _Map, std::string FileName);

void copyMap(std::vector<std::vector<_i64>>& From, std::vector<std::vector<_i64>>& To);

void saveMap(std::vector<std::vector<_i64>>& _Map, std::string FileName);

void scanHighscore(std::string name);

void saveHighscore(_i64 score, std::string name, _bool create = false);

void deleteMap(_ui64 number);

void drawMap(std::vector<std::vector<_i64>>& _Map, sf::RenderWindow& _Window, _bool Demonstration = false);

void changeMap(std::vector<std::vector<_i64>>& Map, std::vector<std::vector<Button>>& ButtonMap);

Error_list changedMapIsCorrect(std::vector<std::vector<_i64>>& Map);

_bool isMapExist(std::string Name);

void createButtonsMap(std::vector<std::vector<Button>>& Map, sf::RenderWindow& _Window);