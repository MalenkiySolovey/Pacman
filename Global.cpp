#include "Headers\Global.h"  

Error_list::Error_list(_bool Entity, _bool Pacman, _bool Pellet) : _Entity(Entity), _Pacman(Pacman), _Pellet(Pellet) {}

sf::Color RGB(_ui8 red, _ui8 green, _ui8 blue, _ui8 alpha) { return sf::Color(red, green, blue, alpha); }

_f32 _centering(_f32 x, _f32 y) { return (x - y) / (_f32)2.0; }

_bool isAllowedSymbol(_i8 chr) {
	switch (chr)
	{
	case '/':  return false;
	case '|':  return false;
	case ':':  return false;
	case '?':  return false;
	case '*':  return false;
	case '"':  return false;
	case '<':  return false;
	case '>':  return false;
	case ' ':  return false;
	case '\\': return false;
	case '\b': return false;
	case '\n': return false;
	case '\t': return false;
	case '\r': return false;
	case '\v': return false;
	case '\f': return false;
	case (_i8)27: return false;
	}
	return true;
}

void reloadWindow(sf::RenderWindow& Win) { Win.setView(sf::View(sf::FloatRect(0, 0, (_f32)((_Settings::__Width + _Settings::__ExtraWidth) * _Settings::__CellSize),
																					(_f32)((_Settings::__Height + _Settings::__ExtraHeight)* _Settings::__CellSize)))); }

void loadSettings() {
	std::fstream File("Settings/Settings.txt");
	File >> _Settings::__CellSize;
	switch (_Settings::__CellSize)
	{
	case 16: {
		_Settings::__ScreenResize = 4;
		_Settings::__ScreenCoef = 1.f;
	} break;
	case 32: {
		_Settings::__ScreenResize = 2;
		_Settings::__ScreenCoef = 2.f;
	} break;
	case 64: {
		_Settings::__ScreenResize = 1;
		_Settings::__ScreenCoef = 4.f;
	} break;
	default: {
		_Settings::__CellSize = 16;
		_Settings::__ScreenResize = 4;
		_Settings::__ScreenCoef = 1.0;
	} break;
	}
	File >> _Settings::__MapNumber;
	File >> _Settings::__SkinNumber;
	File.close();
	File.open("Settings/Maps.txt");
	_ui64 _i = 0;
	while (!File.eof()) {
		std::string str;
		File >> str;
		_Settings::__MapNames.push_back(str);
		_i++;
	}
	File.close();
	_i = 0;
	File.open("Settings/LevelColors.txt");
	while (!File.eof()) {
		std::string str;
		File >> str;
		_Settings::__SkinNames.push_back(str);
		_i++;
	}
	File.close();
}

void unloadSettings() {
	std::fstream File("Settings/Settings.txt", std::ios::out);
	File << _Settings::__CellSize << '\n';
	File << _Settings::__MapNumber << '\n';
	File << _Settings::__SkinNumber;
	File.close();
	File.open("Settings/Maps.txt", std::ios::out);
	for (_ui64 i = 0; i < _Settings::__MapNames.size(); i++)
		if (i != _Settings::__MapNames.size() - 1) File << _Settings::__MapNames[i] << '\n';
		else File << _Settings::__MapNames[i];
	File.close();
	File.open("Settings/LevelColors.txt", std::ios::out);
	for (_ui64 i = 0; i < _Settings::__SkinNames.size(); i++)
		if (i != _Settings::__SkinNames.size() - 1) File << _Settings::__SkinNames[i] << '\n';
		else File << _Settings::__SkinNames[i];
	File.close();
}

void reloadLogo(sf::Texture& LogoTexture, sf::Sprite& LogoSprite) {
	LogoTexture.loadFromFile("Materials/logo" + std::to_string(_Settings::__CellSize) + ".png");
	LogoSprite.setTexture(LogoTexture, true);
	LogoSprite.setPosition((_f32)(((_Settings::__Width + _Settings::__ExtraWidth) * _Settings::__CellSize - LogoTexture.getSize().x) / 2.f), 25.f * _Settings::__ScreenCoef);
}

void reloadBackground(sf::Texture& BackgroundTexture, sf::Sprite& BackgroundSprite) {
	BackgroundTexture.loadFromFile("Materials/background" + std::to_string(_Settings::__CellSize) + ".png");
	BackgroundSprite.setTexture(BackgroundTexture, true);
}

