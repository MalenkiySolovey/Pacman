#include "Headers/Inky.h"

Inky::Inky(sf::RenderWindow* win) { 
    _Window = win; 
    _Kind = Cell::_Ghost4; 
    _Lock = 4; 
    _Color = RGB(98, 244, 242);
}
void Inky::_search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) {
    if (_Scatter) {                                                                         
        if (_whatQuarter(_CentrePosition) == Quarter::Left) _aStar(Map, { 10, 20 }, true);  
        if (_whatQuarter(_CentrePosition) == Quarter::Up) _aStar(Map, { 0, 10 }, true);     
        if (_whatQuarter(_CentrePosition) == Quarter::Right) _aStar(Map, { 10, 0 }, true);  
        if (_whatQuarter(_CentrePosition) == Quarter::Down) _aStar(Map, { 20, 10 }, true);  
    }                                                                                       
    else {                                                                                  
        CellPosition cp = pcmn.getCellPos();                                                
        if (_CellPos.x < cp.x) cp.x += std::abs(cp.x - _CellPos.x);                         
        if (_CellPos.x > cp.x) cp.x -= std::abs(cp.x - _CellPos.x);                         
        if (_CellPos.y < cp.y) cp.y += std::abs(cp.y - _CellPos.y);                         
        if (_CellPos.y > cp.y) cp.y -= std::abs(cp.y - _CellPos.y);                         
        if (cp.x >= _Settings::__Widht) cp.x -= _Settings::__Widht;                         
        if (cp.x < 0) cp.x += _Settings::__Widht;                                           
        if (cp.y >= _Settings::__Height) cp.y -= _Settings::__Height;                       
        if (cp.y < 0) cp.y += _Settings::__Widht;                                           
        _aStar(Map, cp, true);                                                              
    }                                                                                       
}