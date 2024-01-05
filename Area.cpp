#include "Headers/Area.h"

Area::Area() {};
Area::Area(sf::RenderWindow* win) { _Window = win; }
void     Area::scanMousePosOn  () { _On_Flag = true; }
void     Area::scanMousePosOff () { _On_Flag = false; }
_bool    Area::isOnArea        () { return _On; }
_bool    Area::_isMouseOnArea   () {
    sf::Vector2i _MPos = sf::Mouse::getPosition(*_Window);
    _MPos = (sf::Vector2i)_Window->mapPixelToCoords(_MPos);
    _On = (_MPos.y <= (_Position + _Size).yF() &&
           _MPos.x <= (_Position + _Size).xF() &&
           _MPos.y >= (_Position        ).yF() &&
           _MPos.x >= (_Position        ).xF()   );
    return _On;
}
void     Area::setOn           (_bool ptr) { _On = ptr; }
void     Area::setWindow       (sf::RenderWindow* win) { _Window = win; }
void     Area::setPosition     (VectorFF pos)   { _Position = pos; }
void     Area::setPosition     (_f32 x, _f32 y) { _Position.x = x; _Position.y = y; }
VectorFF Area::getPosition     ()               { return _Position; }
void     Area::setSize         (VectorFF size)  { _Size = size; }
void     Area::setSize         (_f32 x, _f32 y) { _Size.x = x; _Size.y = y; }
VectorFF Area::getSize         ()               { return _Size; }
void     Area::_setPosCentre   () {
    _Position.x = _centering((_f32)((_Settings::__Width + _Settings::__ExtraWidth) * _Settings::__CellSize) / _Settings::__ScreenCoef, _Size.x) + _d.x;
    _Position.y = _centering((_f32)((_Settings::__Height + _Settings::__ExtraHeight) * _Settings::__CellSize) / _Settings::__ScreenCoef, _Size.y) + _d.y;
}
void     Area::setPosCentre    (_f32 dx, _f32 dy) {
    _Centre_Flag = true;
    _d.x = dx;
    _d.y = dy;
    _setPosCentre();
}
void     Area::setPosCentre(VectorFF dPos) {
    _Centre_Flag = true;
    _d = dPos;
    _setPosCentre();
}
void     Area::setPosCentreOn() { _Centre_Flag = true; }
void     Area::setPosCentreOff() { _Centre_Flag = false; }
void     Area::_setCentral() {
    _Position.x = _Pos_Other.x + _centering(_Size_Other.x, _Size.x);
    _Position.y = _Pos_Other.y + _centering(_Size_Other.y, _Size.y);
}
void     Area::setCentral(VectorFF Pos, VectorFF Size) {
    _Central = true;
    _Pos_Other = Pos;
    _Size_Other = Size;
    _setCentral();
}
void     Area::setCentralOn() { _Central = true; }
void     Area::setCentralOff() { _Central = false; }

