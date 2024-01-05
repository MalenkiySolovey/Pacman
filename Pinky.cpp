#include "Headers/Pinky.h"

Pinky::Pinky(sf::RenderWindow* win) { 
    _Window = win; 
    _Kind = Cell::_Ghost3; 
    _Lock = 3; 
    _Color = RGB(239, 136, 190);
}
void Pinky::_search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) {
    if (_Scatter) {
        if (_whatQuarter(_CentrePosition) == Quarter::Left) _aStar(Map, { 10, 0 }, true);
        if (_whatQuarter(_CentrePosition) == Quarter::Up) _aStar(Map, { 20, 10 }, true);
        if (_whatQuarter(_CentrePosition) == Quarter::Right) _aStar(Map, { 10, 20 }, true);
        if (_whatQuarter(_CentrePosition) == Quarter::Down) _aStar(Map, { 0, 10 }, true);
    }
    else {
        CellPosition cp = pcmn.getCellPos();
        switch (pcmn.getDirection()) {
        case Quarter::Right: cp.x += 4; break;
        case Quarter::Left:  cp.x -= 4; break;
        case Quarter::Up:    cp.y -= 4; break;
        case Quarter::Down:  cp.y += 4; break;
        }
        if (cp.x > _Settings::__Width - 1) {
            if (Map[cp.y][0] != Cell::Wall &&
                Map[cp.y][0] != Cell::Door &&
                Map[cp.y][_Settings::__Width - 1] != Cell::Wall &&
                Map[cp.y][_Settings::__Width - 1] != Cell::Door) cp.x -= _Settings::__Width;
            else cp.x = _Settings::__Width - 1;
        }
        if (cp.x < 0) {
            if (Map[cp.y][0] != Cell::Wall &&
                Map[cp.y][0] != Cell::Door &&
                Map[cp.y][_Settings::__Width - 1] != Cell::Wall &&
                Map[cp.y][_Settings::__Width - 1] != Cell::Door) cp.x += _Settings::__Width;
            else cp.x = 0;
        }
        if (cp.y > _Settings::__Height - 1) {
            if (Map[0][cp.x] != Cell::Wall &&
                Map[0][cp.x] != Cell::Door &&
                Map[_Settings::__Height - 1][cp.x] != Cell::Wall &&
                Map[_Settings::__Height - 1][cp.x] != Cell::Door) cp.x -= _Settings::__Width;
            else cp.x = _Settings::__Height - 1;
        }
        if (cp.y < 0) {
            if (Map[0][cp.x] != Cell::Wall &&
                Map[0][cp.x] != Cell::Door &&
                Map[_Settings::__Height - 1][cp.x] != Cell::Wall &&
                Map[_Settings::__Height - 1][cp.x] != Cell::Door) cp.x += _Settings::__Width;
            else cp.x = 0;
        }
        _aStar(Map, cp, true);
    }
}