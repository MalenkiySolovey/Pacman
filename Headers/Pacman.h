#pragma once
#include "Global.h"
#include "VectorFF.h"
#include <SFML/Graphics.hpp>    

class Pacman {
	sf::RenderWindow* _Window                                        ;
	    VectorFF      _Position                                      ;
	    VectorFF      _CentrePosition                                ;
	    VectorFF      _LookPosition                                  ;
		VectorFF      _ColisionPos                                   ;
		CellPosition  _CellPos                                       ;
	    _bool         _Pause         :1  { false }                   ;
	    _bool         _Moving        :1  { true }                    ;
	    _f32          _PrevSpeed         { 60.f }                    ;
	    _f32          _Speed             { _Settings::__PacmanSpeed };
	    _bool         _Up            :1  { false }                   ;
	    _bool         _Down          :1  { false }                   ;
	    _bool         _Right         :1  { false }                   ;
	    _bool         _Left          :1  { false }                   ;
	    _bool         _OutMapUD      :1  { false }                   ;
	    VectorFF      _OutPositionUD                                 ; 
	    _bool         _OutMapLR      :1  { false }                   ;
	    VectorFF      _OutPositionLR                                 ; 
	    _bool         _OutMapUp      :1  { false }                   ;
	    _bool         _OutMapDown    :1  { false }                   ;
	    _bool         _OutMapRight   :1  { false }                   ;
	    _bool         _OutMapLeft    :1  { false }                   ;
	    _i32          _Dots              { 441 }                     ;
	    _i64          _Score             { 600 }                     ;
	    _bool         _Dead          :1  { false }                   ;
	    _f32          _Timer             { 0.f   }                   ;
	    _f32          _PeletTime         { -0.1f }                   ;
	    _f32          _EnergizerTime     { -0.1f }                   ;
	void         moveUp           ();
	void         moveDown         ();
	void         moveRight        ();
	void         moveLeft         ();
	void         _move            ();
public:
	             Pacman           (sf::RenderWindow* win);
	void         die              ();
	_bool        isDead           ();
	_f32	     getEnergizerTime ();
	_i64         getDirection();
	void         setScore         (_i64 score);
	_i64         getScore         ();
	void         addScore         (_i64 add);
	CellPosition getCellPos       ();
	VectorFF     getCentrePos     ();
	_bool        pressKeyPlease   ();
	void         reset            (std::vector<std::vector<_i64>>& Map);
	void         nextGame         (std::vector<std::vector<_i64>>& Map);
	void         setPosition      (std::vector<std::vector<_i64>>& Map);
	void         control          ();
	void         stop             ();
	void         go               ();
	void         mapCollision     (std::vector<std::vector<_i64>>& Map);
	void         draw             ();
};