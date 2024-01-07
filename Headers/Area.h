#pragma once
#include "VectorFF.h"

class Area {
protected:
	sf::RenderWindow* _Window                   ;
		VectorFF      _Position       {0, 0}    ;
		VectorFF      _Size           {0, 0}    ;
		_bool         _Centre_Flag :1 { false } ;
		VectorFF      _d              { 0, 0 }  ;
		_bool         _Central     :1 { false } ;
		VectorFF      _Pos_Other      { 0, 0 }  ;
		VectorFF      _Size_Other     { 0, 0 }  ;
		_bool         _On_Flag     :1 { false } ;
		_bool         _On          :1 { false } ;
	_bool    _isMouseOnArea   ();
	void     _setPosCentre   ();
	void     _setCentral     ();
public:
	void     scanMousePosOn  ();
	void     scanMousePosOff ();
	         Area          ();
	         Area          (sf::RenderWindow* win);
	_bool    isOnArea      ();
	void     setOn         (_bool ptr = true);
	void     setWindow     (sf::RenderWindow* win);
	void     setSize       (VectorFF size);
	void     setSize       (_f32 x, _f32 y);
	VectorFF getSize       ();
	void     setPosition   (VectorFF pos);
	void     setPosition   (_f32 x, _f32 y);
	void     setPosCentre  (_f32 dx, _f32 dy);
	void     setPosCentre  (VectorFF dPos);
	void     setPosCentreOn  ();
	void     setPosCentreOff  ();
	void     setCentral(VectorFF Pos, VectorFF Size);
	void     setCentralOn();
	void     setCentralOff();
	VectorFF getPosition   ();
};