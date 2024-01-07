#include "Headers/Pacman.h"

     Pacman::Pacman(sf::RenderWindow* win) : _Window(win) {}
_bool Pacman::isDead() { return _Dead; }
void Pacman::die() { _Dead = true; }
_f32 Pacman::getEnergizerTime() { return _EnergizerTime; }
enum Direction {
	Right,
	Left,
	Up,
	Down
};
_i64 Pacman::getDirection() {
	if (_Right) return Direction::Right;
	if (_Left ) return Direction::Left;
	if (_Up   ) return Direction::Up;
	if (_Down ) return Direction::Down;
	return -1;
}
void Pacman::setScore(_i64 score) { _Score = score; }
_i64 Pacman::getScore() { return _Score; }
void Pacman::addScore(_i64 add) { _Score += add; }
CellPosition Pacman::getCellPos() { return _CellPos; }
VectorFF Pacman::getCentrePos() { return _CentrePosition; }
_bool Pacman::pressKeyPlease() { return !(_Left || _Right || _Up || _Down); }
void Pacman::reset(std::vector<std::vector<_i64>>& Map) {
	setPosition(Map);
	_OutPositionLR = _Position;
	_OutMapLR = false;
	_OutPositionUD = _Position;
	_OutMapUD = false;
	_CentrePosition = _Position + (_f32)8;
	_LookPosition = _CentrePosition;
	_Settings::__Victory     = false;
	_Settings::__Death       = false;
	_PrevSpeed               = _Settings::__PacmanSpeed;
	_Speed                   = _Settings::__PacmanSpeed;
	_Moving                  = true;
	_Up                      = false;
	_Down                    = false;
	_Right                   = false;
	_Left                    = false;
	_Score                   = 600;
	_Dots = _Settings::__DotsNumber;
	_Dead = false;
	_Timer = 0.f;
	_PeletTime = -0.1f;
	_EnergizerTime = -0.1f;
}
void Pacman::nextGame(std::vector<std::vector<_i64>>& Map) {
	setPosition(Map);
	_OutPositionLR = _Position;
	_OutMapLR = false;
	_OutPositionUD = _Position;
	_OutMapUD = false;
	_CentrePosition = _Position + (_f32)8;
	_LookPosition = _CentrePosition;
	_Settings::__Victory      = false;
	_Settings::__Death        = false;
	_Up                       = false;
	_Down                     = false;
	_Right                    = false;
	_Left                     = false;
	_Settings::__Level++;
	if (_Settings::__Level < 10) _Speed = _Settings::__PacmanSpeed + 2.f * _Settings::__Level;
	else _Speed = _Settings::__PacmanSpeed + 20.f;
	_PrevSpeed                 = _Speed;
	_Dots = _Settings::__DotsNumber;
	_Dead = false;
	_Timer         = 0.f;
	_PeletTime     = -0.1f;
	_EnergizerTime = -0.1f;
}
void Pacman::setPosition(std::vector<std::vector<_i64>>& Map) {
	_Settings::__DotsNumber = 0;
	for (_ui32 i = 0; i < _Settings::__Height; i++) {
		for (_ui32 j = 0; j < _Settings::__Width; j++) {
			if (Map[j][i] == Cell::_Pacman) {
				Map[j][i] = Cell::Empty;
				_CellPos.x = i; _CellPos.y = j;
				_Position.x = (_f32)(i * 16);
				_Position.y = (_f32)(j * 16);
			}
			if (Map[j][i] == Cell::Energizer || Map[j][i] == Cell::Pellet) _Settings::__DotsNumber++;
		}
	}
	_Dots = _Settings::__DotsNumber;
}
void Pacman::control() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))    moveUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))  moveDown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))  moveLeft();
}
void Pacman::moveUp() { 
	_Up    = true;
	_Down  = false;
	_Right = false;
	_Left  = false;
}
void Pacman::moveDown() { 
	_Up    = false;
	_Down  = true;
	_Right = false;
	_Left  = false;
}
void Pacman::moveRight() { 
	_Up    = false;
	_Down  = false;
	_Right = true;
	_Left  = false;
}
void Pacman::moveLeft() {
	_Up    = false;
	_Down  = false;
	_Right = false;
	_Left  = true;
}
void Pacman::stop() { _Moving = false; _Pause = true; }
void Pacman::go() { _Moving = true; _Pause = false; }
void Pacman::_move() {
	if (!_Settings::__Victory && !_Settings::__Death && !_Dead) {
		if (_EnergizerTime >= -0.0001f) { if (!_Pause) _EnergizerTime -= _Settings::__ElapsedTime; }
		else if (_PeletTime >= 0.f) { if (!_Pause) _PeletTime -= _Settings::__ElapsedTime; }
			 else _Speed = _PrevSpeed;
		if (_Moving) {
			if (_Up)    _Position.y -= _Speed * _Settings::__ElapsedTime;
			if (_Down)  _Position.y += _Speed * _Settings::__ElapsedTime;
			if (_Right) _Position.x += _Speed * _Settings::__ElapsedTime;
			if (_Left)  _Position.x -= _Speed * _Settings::__ElapsedTime;
		}
		_OutPositionUD = _Position;
		_OutPositionLR = _Position;
		if (_Position.x <= 0.f) {
			_OutPositionLR.x += (_f32)_Settings::__Width * 16.f;
			_OutMapLR = true;
		}
		if (_Position.x + 16.f >= (_f32)_Settings::__Width * 16.f) {
			_OutPositionLR.x -= (_f32)_Settings::__Width * 16.f;
			_OutMapLR = true;
		}
		if (_Position.y <= 0.f) {
			_OutPositionUD.y += (_f32)_Settings::__Height * 16.f;
			_OutMapUD = true;
		}
		if (_Position.y + 16.f >= (_f32)_Settings::__Height * 16.f) {
			_OutPositionUD.y -= (_f32)_Settings::__Width * 16.f;
			_OutMapUD = true;
		}
		if (_Position.x <= -16.f)                                  //left
			_Position.x += (_f32)_Settings::__Width * 16.f;
		if (_Position.x >= (_f32)(_Settings::__Width + 1) * 16.f)  //right
			_Position.x -= (_f32)_Settings::__Width * 16.f;
		if (_Position.y <= -16.f)                                  //up
			_Position.y += (_f32)_Settings::__Height * 16.f;
		if (_Position.y >= (_f32)(_Settings::__Height + 1) * 16.f) //down
			_Position.y -= (_f32)_Settings::__Height * 16.f;
		_CentrePosition = _Position + 8.f;
		if (_CentrePosition.x <= 0)                                //left
			_CentrePosition.x += (_f32)_Settings::__Width * 16.f;
		if (_CentrePosition.x >= (_f32)_Settings::__Width * 16.f)  //right
			_CentrePosition.x -= (_f32)_Settings::__Width * 16.f;
		if (_CentrePosition.y <= 0)                                //up
			_CentrePosition.y += (_f32)_Settings::__Height * 16.f;
		if (_CentrePosition.y >= (_f32)_Settings::__Height * 16.f) //down
			_CentrePosition.y -= (_f32)_Settings::__Height * 16.f;
		_LookPosition = _CentrePosition;
		if (_Right) _LookPosition.x += 16.f;
		if (_Left)  _LookPosition.x -= 16.f;
		if (_Down)  _LookPosition.y += 16.f;
		if (_Up)    _LookPosition.y -= 16.f;
		if (_LookPosition.x <= 0)                                //left
			_LookPosition.x += (_f32)_Settings::__Width * 16.f;
		if (_LookPosition.x >= (_f32)_Settings::__Width * 16.f)  //right
			_LookPosition.x -= (_f32)_Settings::__Width * 16.f;
		if (_LookPosition.y <= 0)                                //up
			_LookPosition.y += (_f32)_Settings::__Height * 16.f;
		if (_LookPosition.y >= (_f32)_Settings::__Height * 16.f) //down
			_LookPosition.y -= (_f32)_Settings::__Height * 16.f;
		_ColisionPos = _LookPosition;
		if (_Right) _ColisionPos.x -= 8.f;
		if (_Left)  _ColisionPos.x += 8.f;
		if (_Down)  _ColisionPos.y -= 8.f;
		if (_Up)    _ColisionPos.y += 8.f;
		if (_ColisionPos.x <= 0)                                //left
			_ColisionPos.x += (_f32)_Settings::__Width * 16.f;
		if (_ColisionPos.x >= (_f32)_Settings::__Width * 16.f)  //right
			_ColisionPos.x -= (_f32)_Settings::__Width * 16.f;
		if (_ColisionPos.y <= 0)                                //up
			_ColisionPos.y += (_f32)_Settings::__Height * 16.f;
		if (_ColisionPos.y >= (_f32)_Settings::__Height * 16.f) //down
			_ColisionPos.y -= (_f32)_Settings::__Height * 16.f;
	}
}
void Pacman::mapCollision(std::vector<std::vector<_i64>>& Map) {
	if (!_Settings::__Victory && !_Settings::__Death && !_Dead) {
		_Moving = true;
		_Pause = false;
		_CellPos.x = (_i64)round(_CentrePosition.x) / 16;
		_CellPos.y = (_i64)round(_CentrePosition.y) / 16;
		if (_CellPos.x >= _Settings::__Width)  _CellPos.x = 0; if (_CellPos.x <= -1) _CellPos.x = _Settings::__Width - 1;
		if (_CellPos.y >= _Settings::__Height) _CellPos.y = 0; if (_CellPos.y <= -1) _CellPos.y = _Settings::__Height - 1;
		switch (Map[_CellPos.y][_CellPos.x]) {
			case Cell::Energizer: { 
				_Dots--; _Score += 10; Map[_CellPos.y][_CellPos.x] = Cell::Empty;
				_PeletTime = 0.f;
				if (_Settings::__Level <= 40) {
					_Speed = 1.15f * _PrevSpeed;
					_EnergizerTime = 7.f;
				} break; 
			}
			case Cell::Pellet:    { 
				_Dots--; _Score += 5;  Map[_CellPos.y][_CellPos.x] = Cell::Empty;
				if (_EnergizerTime <= 0.f)
					if (_Settings::__Level <= 20) {
						_Speed = 0.95f * _PrevSpeed;
						_PeletTime = 0.8f;
					}
					else {
						_Speed = 0.91f * _PrevSpeed;
						_PeletTime = 1.f;
					} break; 
			}
		}
		_i64 xLook = (_i64)round(_LookPosition.x) / 16,
			 yLook = (_i64)round(_LookPosition.y) / 16;
		if (xLook >= _Settings::__Width)  xLook = 0; if (xLook <= -1) xLook = _Settings::__Width - 1;
		if (yLook >= _Settings::__Height) yLook = 0; if (yLook <= -1) yLook = _Settings::__Height - 1;
		if (Map[yLook][xLook] == Cell::Wall || Map[yLook][xLook] == Cell::Door) {
			if (_ColisionPos.y <= (yLook + 1) * 16.f &&
				_ColisionPos.x <= (xLook + 1) * 16.f &&
				_ColisionPos.y >= yLook * 16.f       &&
				_ColisionPos.x >= xLook * 16.f         ) _Moving = false;
 		}		
		_i64 xRight = (_i64)round(_CentrePosition.x + 7.f) / 16, 
			 xLeft  = (_i64)round(_CentrePosition.x - 7.f < 0.f ? _CentrePosition.x - 7.f + _Settings::__Height * 16 : _CentrePosition.x - 7.f) / 16,
			 yDown  = (_i64)round(_CentrePosition.y + 7.f) / 16,
			 yUp    = (_i64)round(_CentrePosition.y - 7.f < 0.f ? _CentrePosition.y - 7.f + _Settings::__Height * 16 : _CentrePosition.y - 7.f) / 16;
		if (xRight >= _Settings::__Width)  xRight = 0; if (xRight <= -1) xRight = _Settings::__Width - 1;
		if (xLeft  >= _Settings::__Width)  xLeft  = 0; if (xLeft  <= -1)  xLeft = _Settings::__Width - 1;
		if (yDown  >= _Settings::__Height) yDown  = 0; if (yDown  <= -1)  yDown = _Settings::__Height - 1;
		if (yUp    >= _Settings::__Height) yUp    = 0; if (yUp    <= -1)    yUp = _Settings::__Height - 1;
		if (Map[_CellPos.y][xRight] == Cell::Wall || Map[_CellPos.y][xRight] == Cell::Door) _Position.x -= _Speed * _Settings::__ElapsedTime;
		if (Map[_CellPos.y][xLeft]  == Cell::Wall || Map[_CellPos.y][xLeft]  == Cell::Door) _Position.x += _Speed * _Settings::__ElapsedTime;
		if (Map[yDown][_CellPos.x]  == Cell::Wall || Map[yDown][_CellPos.x]  == Cell::Door) _Position.y -= _Speed * _Settings::__ElapsedTime;
		if (Map[yUp][_CellPos.x]    == Cell::Wall || Map[yUp][_CellPos.x]    == Cell::Door) _Position.y += _Speed * _Settings::__ElapsedTime;
	}
}
void Pacman::draw() {
	_Timer += _Settings::__ElapsedTime;
	if (_Settings::__Death || _Settings::__Victory) _Timer = 0.f;
	if (_Dots == 0) _Settings::__Victory = true;
	_ui32 frame = 0;
	sf::Texture texture;
	if (_Settings::__Victory) stop();
	if (!_Settings::__Death && _Dead) {
		stop();
		frame = (_ui32)(_Timer / 0.25);
		if (_Timer > 3   ) _Settings::__Death = true;
		texture.loadFromFile("Materials/PacmanDeath" + std::to_string(_Settings::__CellSize) + ".png");
		sf::Sprite sprite(texture);
		sprite.setTextureRect(sf::IntRect(_Settings::__CellSize * frame, 0, _Settings::__CellSize, _Settings::__CellSize));
		if (_Right) {
			sprite.setOrigin(0.f, (_f32)_Settings::__CellSize);
			sprite.setRotation(90);
		}
		if (_Left) {
			sprite.setOrigin((_f32)_Settings::__CellSize, 0.f);
			sprite.setRotation(-90);
		}
		if (_Down) {
			sprite.setOrigin((_f32)_Settings::__CellSize, (_f32)_Settings::__CellSize);
			sprite.setRotation(180);
		}
		sprite.setPosition(_Position.vect2f());
		_Window->draw(sprite);
	}	
	if (!_Settings::__Death && !_Settings::__Victory && !_Dead) {
		frame = _Settings::__CellSize * (_ui32)(_Timer / 0.1);
		if (_Timer > 0.6) { _Timer = 0.f; frame = 0; }	
		_i32 spr;
		if (_Right) spr = _Settings::__CellSize * 0;
		if (_Up)    spr = _Settings::__CellSize * 1;
		if (_Left)  spr = _Settings::__CellSize * 2;
		if (_Down)  spr = _Settings::__CellSize * 3;
		if (!_Up && !_Down && !_Right && !_Left) spr = 1;
		texture.loadFromFile("Materials/Pacman" + std::to_string(_Settings::__CellSize) + ".png");
		sf::Sprite sprite(texture);
		sprite.setTextureRect(sf::IntRect(frame, spr, _Settings::__CellSize, _Settings::__CellSize));
		sprite.setPosition(_Position.vect2f());
		_move();
		_Window->draw(sprite);
		if (_OutMapLR) {
			sprite.setPosition(_OutPositionLR.vect2f());
			_Window->draw(sprite);
		}
		if (_OutMapUD) {
			sprite.setPosition(_OutPositionUD.vect2f());
			_Window->draw(sprite);
		}
		if (_OutMapLR && _OutMapUD) {
			sprite.setPosition(_OutPositionLR.xF(), _OutPositionUD.yF());
			_Window->draw(sprite);
		}
		_OutMapLR = false;
		_OutMapUD = false;
	}
}