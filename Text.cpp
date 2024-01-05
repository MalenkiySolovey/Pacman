#include "Headers\Text.h"

Text        Text::operator =(Text txt) {
    _Window              = txt._Window              ;
    _Position            = txt._Position            ;
    _Size                = txt._Size                ;
    _d                   = txt._d                   ;
    _Pos_Other           = txt._Pos_Other           ;
    _Size_Other          = txt._Size_Other          ;
    _On_Flag             = txt._On_Flag             ;
    _Text                = txt._Text                ;
    _Font                = txt._Font                ;
    _Color               = txt._Color               ;
    _Color_On            = txt._Color_On            ;
    _Color_Turn          = txt._Color_Turn          ;
    _Color_Turn_On       = txt._Color_Turn_On       ;
    _Border              = txt._Border              ;
    _BorderColor         = txt._BorderColor         ;
    _BorderColor_On      = txt._BorderColor_On      ;
    _BorderColor_Turn    = txt._BorderColor_Turn    ;
    _BorderColor_Turn_On = txt._BorderColor_Turn_On ;
    _On                  = txt._On                  ;
    _Turn                = txt._Turn                ;
    return *this;
}
            Text::Text() { _Font.loadFromFile("Materials/StandartFont1.ttf"); _Text.setFont(_Font); }
            Text::Text(sf::RenderWindow* win) { _Window = win; _Font.loadFromFile("Materials/StandartFont1.ttf"); _Text.setFont(_Font); }
void        Text::setString(std::string str) { 
    _Text.setString(str);
    _Size.x = (_f32)str.length() * (_f32)3.0 / (_f32)4.0 * _Size.y;
}
std::string Text::getString() { return _Text.getString().toAnsiString(); }
void        Text::setSize(_ui32 size) { 
    _Size.y = (_f32)size; 
    _Size.x = (_f32)_Text.getString().toAnsiString().length() * (_f32)3.0 / (_f32)4.0 * _Size.y;
}
_ui32       Text::getCharacterSize() { return (_ui32)_Size.x; }
void        Text::setColor(sf::Color col) { _Color = col; _Color_On = col; }
void        Text::setColor(sf::Color col, sf::Color colOn) { _Color = col; _Color_On = colOn; }
void        Text::setColorTurn(sf::Color col) { _Color_Turn = col; _Color_Turn_On = col; }
void        Text::setColorTurn(sf::Color col, sf::Color colOn) { _Color_Turn = col; _Color_Turn_On = colOn; }
void        Text::setBorder(_f32 dx) { 
    if (dx < -3) _Border = -3;
    if (dx > 3) _Border = 3;
    _Border = dx;
}
void        Text::setBorderColor(sf::Color col) { _BorderColor = col; _BorderColor_On = col; }
void        Text::setBorderColor(sf::Color col, sf::Color colOn) { _BorderColor = col; _BorderColor_On = colOn; }
void        Text::setBorderColorTurn(sf::Color col) { _BorderColor_Turn = col; _BorderColor_Turn_On = col; }
void        Text::setBorderColorTurn(sf::Color col, sf::Color colOn) { _BorderColor_Turn = col; _BorderColor_Turn_On = colOn; }
void        Text::setTurn(_bool _Switch) { _Turn = _Switch; }
void        Text::draw() {
    _Size.x = (_f32)_Text.getString().toAnsiString().length() * (_f32)3.0 / (_f32)4.0 * _Size.y;
    if (_Centre_Flag) _setPosCentre();
    if (_Central) _setCentral();
    _Text.setPosition(_Position.vect2f());
    _Text.setCharacterSize((_ui32)_Size.yF());
    sf::Text border = _Text;
    border.setPosition(_Position.xF() + _Border * _Settings::__ScreenCoef, _Position.yF());
    if (_On_Flag) _isMouseOnArea();
    if (_On) {
        if (_Turn) {
            _Text.setFillColor(_Color_Turn_On);
            border.setFillColor(_BorderColor_Turn_On);
        } 
        else {
            _Text.setFillColor(_Color_On);
            border.setFillColor(_BorderColor_On);
        }
    }
    else {
        if (_Turn) {
            _Text.setFillColor(_Color_Turn);
            border.setFillColor(_BorderColor_Turn);
        }
        else {
            _Text.setFillColor(_Color);
            border.setFillColor(_BorderColor);
        }
    }
    if (_Size.y != 0) _Window->draw(border);
    _Window->draw(_Text); 
}
sf::Text    Text::getText() {
    return _Text;
}