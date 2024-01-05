#include "Headers/Clyde.h"

Clyde::Clyde(sf::RenderWindow* win) { 
    _Window = win; 
    _Kind = Cell::_Ghost2; 
    _Lock = 2;
    _Color = RGB(240, 134, 80);
}
void Clyde::_search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) {
    if (_Scatter) {                                                                             
        if (_whatQuarter(_CellPos) == Quarter::UpLeft) _aStar(Map, { 0, 20 }, true);            
        if (_whatQuarter(_CellPos) == Quarter::DownLeft) _aStar(Map, { 20, 20 }, true);         
        if (_whatQuarter(_CellPos) == Quarter::DownRight) _aStar(Map, { 20, 0 }, true);         
        if (_whatQuarter(_CellPos) == Quarter::UpRight) _aStar(Map, { 0, 0 }, true);            
    }                                                                                           
    else {                                                                                      
        _aStar(Map, pcmn.getCellPos(), true);                                                   
        if (_Distance < 8) {                                                                    
            if (_whatQuarter(_CellPos) == Quarter::UpLeft) _aStar(Map, { 0, 20 }, true);        
            if (_whatQuarter(_CellPos) == Quarter::DownLeft) _aStar(Map, { 20, 20 }, true);     
            if (_whatQuarter(_CellPos) == Quarter::DownRight) _aStar(Map, { 20, 0 }, true);     
            if (_whatQuarter(_CellPos) == Quarter::UpRight) _aStar(Map, { 0, 0 }, true);        
        }
        else _aStar(Map, pcmn.getCellPos(), true); 
    }
}