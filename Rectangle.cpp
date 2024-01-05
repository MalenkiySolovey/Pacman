#include "Headers/Rectangle.h"

Rectangle Rectangle::operator =(Rectangle rct) {
    _Window              = rct._Window              ;  
    _Position            = rct._Position            ;
    _Size                = rct._Size                ;
    _d                   = rct._d                   ;
    _Pos_Other           = rct._Pos_Other           ;
    _Size_Other          = rct._Size_Other          ;
    _On_Flag             = rct._On_Flag             ;
    _Color               = rct._Color               ;
    _Color_On            = rct._Color_On            ;
    _Color_Turn          = rct._Color_Turn          ;
    _Color_Turn_On       = rct._Color_Turn_On       ;
    _Border              = rct._Border              ;
    _BorderColor         = rct._BorderColor         ;
    _BorderColor_On      = rct._BorderColor_On      ;
    _BorderColor_Turn    = rct._BorderColor_Turn    ;
    _BorderColor_Turn_On = rct._BorderColor_Turn_On ;
    _On                  = rct._On                  ;
    _Turn                = rct._Turn                ; 
    return *this;
}
          Rectangle::Rectangle() {}
          Rectangle::Rectangle(sf::RenderWindow* win) { _Window = win; }
void      Rectangle::setColor(sf::Color col) { _Color = col; _Color_On = col; }
void      Rectangle::setColor(sf::Color col, sf::Color colOn) { _Color = col; _Color_On = colOn; }
void      Rectangle::setColorTurn(sf::Color col) { _Color_Turn = col; _Color_Turn_On = col; }
void      Rectangle::setColorTurn(sf::Color col, sf::Color colOn) { _Color_Turn = col; _Color_Turn_On = colOn; }
void      Rectangle::setBorder(_f32 dx) { _Border.x = dx; _Border.y = dx; }
void      Rectangle::setBorderColor(sf::Color col) { _BorderColor = col; _BorderColor_On = col; }
void      Rectangle::setBorderColor(sf::Color col, sf::Color colOn) { _BorderColor = col; _BorderColor_On = colOn; }
void      Rectangle::setBorderColorTurn(sf::Color col) { _BorderColor_Turn = col; _BorderColor_Turn_On = col; }
void      Rectangle::setBorderColorTurn(sf::Color col, sf::Color colOn) { _BorderColor_Turn = col; _BorderColor_Turn_On = colOn; }
void      Rectangle::setTurn(_bool _Switch) { _Turn = _Switch; }
void      Rectangle::draw() {
    if (_Centre_Flag) _setPosCentre();
    if (_Central) _setCentral();
    sf::RectangleShape rect((_Size - _Border).vect2f());
    rect.setPosition((_Position + _Border / (_f32)2.0).vect2f());
    sf::RectangleShape border(_Size.vect2f());
    border.setPosition(_Position.vect2f());
    if (_On_Flag) _isMouseOnArea();
    if (_On) {
        if (_Turn) {
            rect.setFillColor(_Color_Turn_On);
            border.setFillColor(_BorderColor_Turn_On);
        }
        else {
            rect.setFillColor(_Color_On);
            border.setFillColor(_BorderColor_On);
        }
    }
    else {
        if (_Turn) {
            rect.setFillColor(_Color_Turn);
            border.setFillColor(_BorderColor_Turn);
        }
        else {
            rect.setFillColor(_Color);
            border.setFillColor(_BorderColor);
        }
    }
    if (_Border.x != 0) _Window->draw(border);
    _Window->draw(rect);
}