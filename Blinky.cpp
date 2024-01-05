#include "Headers/Blinky.h"

Blinky::Blinky(sf::RenderWindow* win) { 
    _Window = win; 
    _Kind = Cell::_Ghost1; 
    _Lock = 0; 
    _Color = RGB(235, 51, 36);
}
void Blinky::_search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) {
    if (_Scatter) {
        if (_whatQuarter(_CellPos) == Quarter::UpLeft) _aStar(Map, { 20, 0 }, true);
        if (_whatQuarter(_CellPos) == Quarter::UpRight) _aStar(Map, { 20, 20 }, true);
        if (_whatQuarter(_CellPos) == Quarter::DownRight) _aStar(Map, { 0, 20 }, true);
        if (_whatQuarter(_CellPos) == Quarter::DownLeft) _aStar(Map, { 0, 0 }, true);
    }
    else _aStar(Map, pcmn.getCellPos(), true);
}