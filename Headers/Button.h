#pragma once
#include <SFML/Graphics.hpp>     
#include "Global.h"
#include "Text.h"
#include "Rectangle.h"
#include "Area.h"

class Button {
     sf::RenderWindow* _Window                                         ;
     sf::Mouse::Button _MouseClickButton    { sf::Mouse::Button::Left };
         _bool         _PrevClick        :1 { false }                  ;
         _bool         _NewClick         :1 { false }                  ;
         _bool         _Active_Flag      :1 { true }                   ;
         _bool         _Show_Flag        :1 { true }                   ;
         _bool         _Switch_Flag      :1 { false }                  ;
         _bool         _Switch           :1 { false }                  ;
         _bool         _Flag             :1 { false }                  ;
         _bool         _Off              :1 { false }                  ;
         _bool         _Off_return       :1 { false }                  ;
    enum IfClick{
        No_press,
        Press,
        Release,
        Hold,
    }                  _Condition        { Release }                , 
                       _WhatNow          { No_press }               ;
public:
         Rectangle     RCT                                          ;                                       
         Text          TXT                                          ;                                                                       
    Button     operator = (Button btn);
               Button             ();
               Button             (sf::RenderWindow* Window);
    _bool      boolManyToOne      (_bool flag);
    _bool      boolManyToTwo      (_bool flag);
    void       setMouseClick      (sf::Mouse::Button click);
    void       turnOffMouseClick  (_bool ret = false);
    void       turnOnMouseClick   ();
    void       setRectangle       (Rectangle rct);
    Rectangle  getRectangle       ();
    void       setText            (Text txt);
    Text       getText            ();
    void       setButtonStandart  ();
    void       setButtonSwitch    ();
    void       turnOnSwitch       ();
    void       turnOffSwitch      ();
    void       setButtonNoPress   ();
    void       setButtonHold      ();
    _bool      isActive           ();
    void       activate           ();
    void       disable            ();
    _bool      isShown            ();
    void       show               ();
    void       hide               ();
    _bool      draw               ();
};