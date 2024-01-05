#pragma once
#include "Global.h"
#include "Pacman.h"
#include <queue>

class Ghost{
protected:
	 sf::RenderWindow*        _Window                                             ;
	     _bool                _Exists      :1  { false }                          ;
	     Cell                 _Kind            { Cell::_Ghost1 }                  ;
		 _ui32                _Lock            { 0 }                              ;
	 sf::Color                _Color           { sf::Color::White }               ;
	     CellPosition         _StartCellPos                                       ;
	     CellPosition         _CellPos                                            ;
	     CellPosition         _CellLook                                           ;
	     VectorFF             _Position                                           ;
	     VectorFF             _CentrePosition                                     ;
	     _bool                _Change      :1  { false }                          ;
	     _bool                _ChangeFlag  :1  { false }                          ;
		 _bool                _NewPath     :1  { false }                          ;
	std::vector<CellPosition> _Path            {}                                 ;
	     _ui64                _Ipath           { 0 }                              ;
	     _i32                 _Distance        { 0 }                              ;
	     _f32                 _PrevSpeed       { 0.9f *_Settings::__PacmanSpeed } ;
	     _f32                 _Speed           { 0.9f *_Settings::__PacmanSpeed } ;
	     _bool                _Free        :1  { false }                          ;
	     _bool                _Moving      :1  { true }                           ;
		 _bool                _LookMove    :1  { false }                          ;
	     _bool                _Up          :1  { false }                          ;
	     _bool                _Down        :1  { false }                          ;
	     _bool                _Left        :1  { false }                          ;
	     _bool                _Right       :1  { false }                          ;
	     _bool                _Fear        :1  { false }                          ;
	     _bool                _EndFear     :1  { false }                          ;
		 _bool                _Scatter     :1  { true }                           ;
	     _bool                _Dead        :1  { false }                          ;
	     _bool                _AfterDead   :1  { false }                          ;
	     _bool                _Return      :1  { false }                          ;
	     _bool                _Defeat      :1  { false }                          ;
	     _f32                 _Timer           { 0.f }                            ;
	     _f32                 _SearchTimer     { 0.f }                            ;
		 _i32                 _Phase           { 0 }                              ;
		 _f32                 _PhaseTimer      { 0.f }                            ;
	enum Quarter {
		Right,
		Left,
		Up,
		Down,
		UpRight,
		UpLeft,
		DownLeft,
		DownRight
	};
	_bool _changeMove();
	_i64 _heuristic(CellPosition& start, CellPosition& goal);
	void _aStar(const std::vector<std::vector<_i64>>& grid, CellPosition goal, _bool throuth = false);
	void _move(const std::vector<std::vector<_i64>>& Map);
	Quarter _whatQuarter(const CellPosition& cp);
	Quarter _whatQuarter(const VectorFF& cp);
	virtual void _search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) = 0;
public:
	void setPosition(std::vector<std::vector<_i64>>& Map);
	void stop();
	void go();
	void reset(std::vector<std::vector<_i64>>& Map);
	void nextGame();
	void search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn);
	void draw();
};