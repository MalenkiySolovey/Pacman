#pragma once
#include <SFML/Graphics.hpp>    
#include "Global.h"  
#include "VectorFF.h"
#include "Area.h"

class Rectangle : public Area {              
     sf::Color         _Color                  { sf::Color::Black } ;
     sf::Color         _Color_On               { sf::Color::Black } ;
     sf::Color         _Color_Turn             { sf::Color::Black } ;
     sf::Color         _Color_Turn_On          { sf::Color::Black } ;
         VectorFF      _Border                 { 0, 0 }             ;                                                                 
     sf::Color         _BorderColor            { sf::Color::Black } ;
     sf::Color         _BorderColor_On         { sf::Color::Black } ;
     sf::Color         _BorderColor_Turn       { sf::Color::Black } ;
     sf::Color         _BorderColor_Turn_On    { sf::Color::Black } ;                                                                 
         _bool         _Turn                :1 { false }            ;
     using Area::Area;
public:
    Rectangle operator =         (Rectangle rct);
              Rectangle          ();
              Rectangle          (sf::RenderWindow* win);
    void      setColor           (sf::Color col);
    void      setColor           (sf::Color col, sf::Color colOn);
    void      setColorTurn       (sf::Color col);
    void      setColorTurn       (sf::Color col, sf::Color colOn);
    void      setBorder          (_f32 dx);
    void      setBorderColor     (sf::Color col);
    void      setBorderColor     (sf::Color col, sf::Color colOn);
    void      setBorderColorTurn (sf::Color col);
    void      setBorderColorTurn (sf::Color col, sf::Color colOn);
    void      setTurn            (_bool _Switch = true);
    void      draw               ();
};