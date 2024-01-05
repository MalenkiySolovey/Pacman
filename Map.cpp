#include "Headers/Map.h"


void scanMap(std::vector<std::vector<_i64>>& _Map, std::string FileName) {
	std::fstream _File("Maps/Map_" + FileName + ".txt");
	std::vector<std::vector<_i64>> Map;
	for (_ui32 i = 0; i < _Settings::__Height; i++) {
		std::vector<_i64> v;
		for (_ui32 j = 0; j < _Settings::__Width; j++) {
			_i64 cell; _File >> cell;
			v.push_back(cell);
		}
		Map.push_back(v);
	}
	_File.close();
	_Map = Map;
}

void copyMap(std::vector<std::vector<_i64>>& From, std::vector<std::vector<_i64>>& To) {
	std::vector<std::vector<_i64>> _v;
	for (auto i : From) { 
		std::vector<_i64> v;
		for (auto j : i) v.push_back(j);
		_v.push_back(v);
	}
	To = _v;
}

void saveMap(std::vector<std::vector<_i64>>& _Map, std::string FileName) {
	_Settings::__MapNames.push_back(FileName);
	_Settings::__MapNumber = _Settings::__MapNames.size() - 1;
	std::fstream _File("Maps/Map_" + FileName + ".txt", std::ios::out);
	for (_ui32 i = 0; i < _Settings::__Height; i++) {
		std::vector<_i64> v;
		for (_ui32 j = 0; j < _Settings::__Width; j++) {
			if (j == _Settings::__Width - 1) _File << _Map[i][j];
			else _File << _Map[i][j] << ' ';
		}
		if (i != _Settings::__Height - 1) _File << '\n';
	}
	_File.close();
}

void scanHighscore(std::string name) {
	std::fstream File("Highscores/Score_" + name + ".txt");
	std::vector<_i64> v;
	while (!File.eof()) {
		_i64 i; File >> i;
		v.push_back(i);
	}
	File.close();
	_Settings::__MapScores = v;
}

void saveHighscore(_i64 score, std::string name, _bool create) {
	if (create) {
		std::vector<_i64> v;
		v.push_back(score);
		_Settings::__MapScores = v;
	} else _Settings::__MapScores.push_back(score);
	std::sort(_Settings::__MapScores.rbegin(), _Settings::__MapScores.rend());
	if (_Settings::__MapScores.size() > 10)
		for (_ui64 i = 10; i < _Settings::__MapScores.size(); i++)
			_Settings::__MapScores.erase(_Settings::__MapScores.begin() + i);
	std::fstream File("Highscores/Score_" + name + ".txt", std::ios::out);
	for (_ui64 i = 0; i < _Settings::__MapScores.size(); i++)
		if (i == _Settings::__MapScores.size() - 1) File << _Settings::__MapScores[i];
		else File << _Settings::__MapScores[i] << ' ';
	File.close();
}

void deleteMap(_ui64 number) {
	remove(("Maps/Map_" + _Settings::__MapNames[number] + ".txt").c_str());
	remove(("Highscores/Score_" + _Settings::__MapNames[number] + ".txt").c_str());
	for (_ui64 i = 0; i < _Settings::__MapScores.size(); i++)
		_Settings::__MapScores.erase(_Settings::__MapScores.begin() + i);
	_Settings::__MapNames.erase(_Settings::__MapNames.begin() + number);
	_Settings::__MapNumber = 0;
}

void drawMap(std::vector<std::vector<_i64>>& Map, sf::RenderWindow& _Window, _bool Demonstration) {
	sf::Texture texturemap, texturePacman, texturemapGhost;
	sf::Sprite spritemap, spritePacman, spriteGhost;
	texturemap.loadFromFile("Materials/Map" + std::to_string(_Settings::__CellSize) + '_' + _Settings::__SkinNames[_Settings::__SkinNumber] + ".png");
	spritemap.setTexture(texturemap);
	texturePacman.loadFromFile("Materials/Pacman" + std::to_string(_Settings::__CellSize) + ".png");
	spritePacman.setTexture(texturePacman);
	texturemapGhost.loadFromFile("Materials/Ghost" + std::to_string(_Settings::__CellSize) + '_' + _Settings::__SkinNames[_Settings::__SkinNumber] + ".png");
	spriteGhost.setTexture(texturemapGhost);
	for (_ui64 i = 0; i < Map.size(); i++) {
		for (_ui64 j = 0; j < Map[0].size(); j++) {
			spritemap.setPosition((_f32)(_Settings::__CellSize * i), (_f32)(_Settings::__CellSize * j));
			spritePacman.setPosition((_f32)(_Settings::__CellSize * i), (_f32)(_Settings::__CellSize * j));
			spriteGhost.setPosition((_f32)(_Settings::__CellSize * i), (_f32)(_Settings::__CellSize * j));
			switch (Map[j][i]) {
				case Cell::Door: {
					spritemap.setTextureRect(sf::IntRect(2 * _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
					_Window.draw(spritemap);
					break;
				}
				case Cell::Energizer: {
					spritemap.setTextureRect(sf::IntRect(_Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
					_Window.draw(spritemap);
					break;
				}
				case Cell::Pellet: {
					spritemap.setTextureRect(sf::IntRect(0, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
					_Window.draw(spritemap);
					break;
				}
				case Cell::Wall: {
					_bool up    { false };
					_bool down  { false };
					_bool left  { false };
					_bool right { false };
					if (0 < i)
						if (Map[j][i - 1] == Cell::Wall) left = true;
					if (i < Map.size() - 1)
						if (Map[j][i + 1] == Cell::Wall) right = true;
					if (0 < j)
						if (Map[j - 1][i] == Cell::Wall) up = true;
					if (j < Map[j].size() - 1)
						if (Map[1 + j][i] == Cell::Wall) down = true;
					spritemap.setTextureRect(sf::IntRect(_Settings::__CellSize * (down + 2 * (left + 2 * (right + 2 * up))), 0, _Settings::__CellSize, _Settings::__CellSize));
					_Window.draw(spritemap);
					break;
				}
				case Cell::_Pacman: {
					if (Demonstration) {
						spritePacman.setTextureRect(sf::IntRect(3 * _Settings::__CellSize, 0, _Settings::__CellSize, _Settings::__CellSize));
						_Window.draw(spritePacman);
					}
					break;
				}
				case Cell::_Ghost1: {
					if (Demonstration) {
						spriteGhost.setTextureRect(sf::IntRect(0, 0, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(RGB(235, 51, 36));
						_Window.draw(spriteGhost);
						spriteGhost.setTextureRect(sf::IntRect(0, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(sf::Color::White);
						_Window.draw(spriteGhost);
					}
					break;
				}
				case Cell::_Ghost2: {
					if (Demonstration) {
						spriteGhost.setTextureRect(sf::IntRect(0, 0, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(RGB(240, 134, 80));
						_Window.draw(spriteGhost);
						spriteGhost.setTextureRect(sf::IntRect(0, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(sf::Color::White);
						_Window.draw(spriteGhost);
					}
					break;
				}
				case Cell::_Ghost3: {
					if (Demonstration) {
						spriteGhost.setTextureRect(sf::IntRect(0, 0, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(RGB(239, 136, 190));
						_Window.draw(spriteGhost);
						spriteGhost.setTextureRect(sf::IntRect(0, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(sf::Color::White);
						_Window.draw(spriteGhost);
					}
					break;
				}
				case Cell::_Ghost4: {
					if (Demonstration) {
						spriteGhost.setTextureRect(sf::IntRect(0, 0, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(RGB(98, 244, 242));
						_Window.draw(spriteGhost);
						spriteGhost.setTextureRect(sf::IntRect(0, _Settings::__CellSize, _Settings::__CellSize, _Settings::__CellSize));
						spriteGhost.setColor(sf::Color::White);
						_Window.draw(spriteGhost);
					}
					break;
			    }
			}
		}
	}
}

void changeMap(std::vector<std::vector<_i64>>& Map, std::vector<std::vector<Button>>& ButtonMap) {
	for (_ui64 i = 0; i < Map.size(); i++) {
		for (_ui64 j = 0; j < Map[0].size(); j++) {
			_i64 k = Map[j][i];
			if (ButtonMap[j][i].draw()) Map[j][i] = ((++k) % 10);
		}
	}
}

Error_list changedMapIsCorrect(std::vector<std::vector<_i64>>& Map) {
	std::vector<_i64> v(6, 0);
	Error_list t;
	for (_ui64 i = 0; i < Map.size(); i++) {
		for (_ui64 j = 0; j < Map[0].size(); j++) {
			switch (Map[j][i]) {
				case Cell::_Pacman: v[0]++; if (v[0] > 1) t._Entity = true; break;
				case Cell::_Ghost1: v[1]++; if (v[1] > 1) t._Entity = true; break;
				case Cell::_Ghost2: v[2]++; if (v[2] > 1) t._Entity = true; break;
				case Cell::_Ghost3: v[3]++; if (v[3] > 1) t._Entity = true; break;
				case Cell::_Ghost4: v[4]++; if (v[4] > 1) t._Entity = true; break;
				case Cell::Pellet: v[5]++; break;
				case Cell::Energizer: v[5]++; break;
			}
		}
	}
	if (v[0] < 1) t._Pacman = true;
	return t;
}

void createButtonsMap(std::vector<std::vector<Button>>& Map, sf::RenderWindow& _Window) {
	std::vector<std::vector<Button>> _Map;
	for (_ui64 i = 0; i < _Settings::__Height; i++) {
		std::vector<Button> v;
		for (_ui64 j = 0; j < _Settings::__Width; j++) {
			Button btnChangeCell(&_Window);
			btnChangeCell.setMouseClick(sf::Mouse::Button::Left);
			btnChangeCell.RCT.setSize(15, 15);
			btnChangeCell.RCT.setColor(RGB(0, 0, 0, 0), RGB(20, 201, 20, 50));
			btnChangeCell.RCT.setPosition((_f32)(j * 16 + 1), (_f32)(i * 16 + 1));
			v.push_back(btnChangeCell);
		}
		_Map.push_back(v);
	}
	Map = _Map;
}

_bool isMapExist(std::string Name) {
	for (auto u : _Settings::__MapNames)
		if (u == Name) return true;
	return false;
}



