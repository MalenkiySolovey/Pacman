#include "Headers\Button.h"

Button     Button::operator =                 (Button btn) {
    _Window           = btn._Window           ;
    _MouseClickButton = btn._MouseClickButton ;
    _Active_Flag      = btn._Active_Flag      ;
    _Show_Flag        = btn._Show_Flag        ;
    _Switch_Flag      = btn._Switch_Flag      ;
    _Switch           = btn._Switch           ;
    _Flag             = btn._Flag             ;
    _Off              = btn._Off              ;
    _Off_return       = btn._Off_return       ;
    RCT               = btn.RCT;              ;
    TXT               = btn.TXT               ;
    return *this;
}
           Button::Button                               (){}
           Button::Button       (sf::RenderWindow* Window) : _Window(Window) { TXT.setWindow(Window); RCT.setWindow(Window); }
_bool      Button::boolManyToOne              (_bool flag) {
    if (_Flag == true  && flag == true ) return false;
    if (_Flag == false && flag == false) return false;
    if (_Flag == true && flag == false) {
        _Flag ^= true;
        return false;
    }
    _Flag ^= true;
    return true;
}
_bool      Button::boolManyToTwo              (_bool flag) {
    if (_Flag == true  && flag == true ) return false;
    if (_Flag == false && flag == false) return false;
    _Flag ^= true;
    return true;
}
void       Button::setMouseClick (sf::Mouse::Button click) { _MouseClickButton = click; }
void       Button::turnOffMouseClick           (_bool ret) { _Off = true; _Off_return = ret; }
void       Button::turnOnMouseClick                     () { _Off = false; _Off_return = false; }
void       Button::setRectangle            (Rectangle rct) {  RCT = rct; }
Rectangle  Button::getRectangle                         () { return RCT; }
void       Button::setText                      (Text txt) { TXT = txt; }
Text       Button::getText                              () { return TXT; }
void       Button::setButtonStandart                    () { 
    _Condition = Release; 
    _Switch = false;
    _Switch_Flag = false;
}
void       Button::setButtonSwitch                      () {
    _Condition = Release;
    _Switch = false;
    _Switch_Flag = true;
}
void       Button::turnOnSwitch                         () { _Switch = true; }
void       Button::turnOffSwitch                        () { _Switch = false; }
void       Button::setButtonNoPress                     () { 
    _Condition = No_press; 
    _Switch = false;
    _Switch_Flag = false;
}
void       Button::setButtonHold                        () { 
    _Condition = Hold; 
    _Switch = false;
    _Switch_Flag = false;
}
_bool      Button::isActive                             () { return _Active_Flag; }
void       Button::activate                             () { _Active_Flag = true; }
void       Button::disable                              () { _Active_Flag = false; }
_bool      Button::isShown                              () { return _Active_Flag; }
void       Button::show                                 () { _Show_Flag = true; }
void       Button::hide                                 () { _Show_Flag = false; }
_bool      Button::draw                                 () {
    if (!_Active_Flag) return false;
    _PrevClick = _NewClick;
    _NewClick = sf::Mouse::isButtonPressed(_MouseClickButton);
    _WhatNow = static_cast<IfClick>((_PrevClick * 2) + _NewClick);
    if (_Show_Flag) {
        if (RCT.getSize().x != 0 && RCT.getSize().y != 0) {
            RCT.setWindow(_Window);
            RCT.setTurn(_Switch);
            RCT.scanMousePosOn();
            RCT.draw();
            if (TXT.getString() != "") {
                TXT.setWindow(_Window);
                TXT.setCentral(RCT.getPosition(), RCT.getSize());
                TXT.setTurn(_Switch);
                TXT.setOn(RCT.isOnArea());
                TXT.draw();
            }
        }
        else {
            if (TXT.getString() != "") {
                TXT.setWindow(_Window);
                TXT.setTurn(_Switch);
                TXT.scanMousePosOn();
                TXT.draw();
            }
        }
    }  
    if (_Off) return _Off_return;
    if (_WhatNow == _Condition && (RCT.isOnArea() || TXT.isOnArea())) {
        if (_Switch_Flag) { 
            _Switch ^= true; 
            return _Switch;
        }
        return true; 
    }
    return _Switch;


}