#pragma once
#include <SFML/Graphics.hpp>    
#include <fstream>

typedef bool              _bool;    //bool													 

typedef __int8            _i8;      //char													 
typedef __int16           _i16;     //short													 
typedef __int32           _i32;     //int												 
typedef __int64           _i64;     //long long												 
typedef unsigned __int8   _ui8;     //unsigned char									 
typedef unsigned __int16  _ui16;    //unsigned short											 
typedef unsigned __int32  _ui32;    //unsigned int										 
typedef unsigned __int64  _ui64;    //unsigned long long										 

typedef float             _f32;     //float										 
typedef double            _f64;     //double													 
typedef long double       _lf64;    //long double		

typedef signed char       _sc8;     //signed char
typedef char8_t           _uc8;     //char8_t												 
typedef char16_t          _uc16;    //char16_t												 
typedef char32_t          _uc32;    //char32_t												 
typedef __wchar_t         _wc;      //__wchar_t	

struct _Settings {
	static inline _ui32                    __CellSize     { 16 };
	static inline _ui32                    __ScreenResize { 4 };
	static inline _f32                     __ScreenCoef   { 1.f };

	static inline _ui32                    __Height       { 21 };
	static inline _ui32                    __ExtraHeight  { 1 };
	static inline _ui32                    __Widht        { 21 };
	static inline _ui32                    __ExtraWidht   { 0 };
														  
	static inline _ui64                    __MapNumber    { 0 };
	static inline std::vector<std::string> __MapNames;	  
														  
	static inline _ui64                    __SkinNumber   { 0 };
	static inline std::vector<std::string> __SkinNames;	

	static inline std::vector<_i64>        __MapScores;	  
														  
	static inline _f32                     __ElapsedTime  { 1.f };
														  
	static inline _ui32                    __Level        { 1 };
	static inline _ui32                    __DotsNumber   { 0 };
	static inline _bool                    __Victory      { false };
	static inline _bool                    __Death        { false };
														  
	static inline _f32                     __PacmanSpeed  { 60.f };
};

struct CellPosition {
	_i64 x { 0 };
	_i64 y { 0 };
	CellPosition(){}
	CellPosition(_i64 _x, _i64 _y): x(_x), y(_y) {}
	_bool operator ==(CellPosition cp) { return x == cp.x && y == cp.y; }
};

struct Error_list {
	_bool _Entity{ false };
	_bool _Pacman{ false };
	_bool _Pellet{ false };
	Error_list(_bool Entity = false, _bool Pacman = false, _bool Pellet = false);
};

enum Cell {
	Door,
	Empty,
	Energizer,
	Pellet,
	Wall,
	_Pacman,
	_Ghost1,
	_Ghost2,
	_Ghost3,
	_Ghost4
};

// Colors
// But: RGB(234, 122, 8) , RGB(20, 201, 20)
// TurnBut: RGB(5, 129, 193), RGB(23, 160, 110)
// Bord: RGB(217, 65, 25), RGB(31, 110, 21)
// TurnBord: RGB(23, 103, 139), RGB(19, 98, 69)
sf::Color RGB(_ui8 red, _ui8 green, _ui8 blue, _ui8 alpha = 255U);

_f32 _centering(_f32 x, _f32 y);

_bool isAllowedSymbol(_i8 chr);

void reloadWindow(sf::RenderWindow& Win);

void loadSettings();

void unloadSettings();

void reloadLogo(sf::Texture& LogoTexture, sf::Sprite& LogoSprite);

void reloadBackground(sf::Texture& BackgroundTexture, sf::Sprite& BackgroundSprite);