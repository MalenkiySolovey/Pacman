#include "Headers/VectorFF.h"

             VectorFF::VectorFF       () {}
             VectorFF::VectorFF       (_f32 X, _f32 Y) : x(X), y(Y) {}
             VectorFF::VectorFF       (sf::Vector2f Vect) : x(Vect.x), y(Vect.y) {}
             VectorFF::VectorFF       (sf::Vector2i Vect) : x((_f32)Vect.x), y((_f32)Vect.y) {}
    _f32     VectorFF::xF             () { return _Settings::__ScreenCoef * x; }
    _f32     VectorFF::yF             () { return _Settings::__ScreenCoef * y; }
sf::Vector2f VectorFF::vect2f         () { return _Settings::__ScreenCoef * sf::Vector2f(x, y); }						   
    VectorFF VectorFF::operator +     (_f32 V) { return VectorFF(x + V, y + V); }
    VectorFF VectorFF::operator -     (_f32 V) { return VectorFF(x - V, y - V); }
    VectorFF VectorFF::operator *     (_f32 V) { return VectorFF(x * V, y * V); }
    VectorFF VectorFF::operator /     (_f32 V) { return VectorFF(x / V, y / V); }
    VectorFF VectorFF::operator +     (VectorFF Vect) { return VectorFF(x + Vect.x, y + Vect.y); }											 
    VectorFF VectorFF::operator -     (VectorFF Vect) { return VectorFF(x - Vect.x, y - Vect.y); }											 
    VectorFF VectorFF::operator =     (VectorFF Vect) { x = Vect.x; y = Vect.y; return *this; }
    VectorFF VectorFF::operator =     (sf::Vector2f Vect) { x = Vect.x; y = Vect.y; return *this; }
    VectorFF VectorFF::operator =     (sf::Vector2i Vect) { x = (_f32)Vect.x; y = (_f32)Vect.y; return *this; }
             VectorFF::operator sf::Vector2f() { return _Settings::__ScreenCoef * sf::Vector2f(x, y);}
             VectorFF::operator sf::Vector2i() { return sf::Vector2i((_i32)round(_Settings::__ScreenCoef * x), (_i32)round(_Settings::__ScreenCoef * y)); }