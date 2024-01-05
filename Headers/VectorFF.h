#pragma once
#include <SFML/Graphics.hpp>    
#include "Global.h"  

struct VectorFF {
	_f32 x { 0 };
	_f32 y { 0 };
	             VectorFF       ();
	             VectorFF       (_f32 X, _f32 Y);
				 VectorFF       (sf::Vector2f Vect);
				 VectorFF       (sf::Vector2i Vect);
	    _f32     xF             ();
	    _f32     yF             ();
	sf::Vector2f vect2f         ();
	    VectorFF operator +     (_f32 V);
	    VectorFF operator -     (_f32 V);
	    VectorFF operator *     (_f32 V);
	    VectorFF operator /     (_f32 V);
	    VectorFF operator +     (VectorFF Vect);
	    VectorFF operator -     (VectorFF Vect);
	    VectorFF operator =     (VectorFF Vect);
		VectorFF operator =     (sf::Vector2f Vect);
		VectorFF operator =     (sf::Vector2i Vect);
		         operator sf::Vector2f();
		         operator sf::Vector2i();
};