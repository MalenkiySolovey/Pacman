#include "Headers/Ghost.h"

_bool Ghost::_changeMove() {
    if (_Change == true && _ChangeFlag == true) return false;
    if (_Change == false && _ChangeFlag == false) return false;
    _ChangeFlag ^= true;
    return true;
}
_i64 Ghost::_heuristic(CellPosition& start, CellPosition& goal) {
    if (_Fear) return -(std::abs(goal.x - start.x) + std::abs(goal.y - start.y));
    return std::abs(goal.x - start.x) + std::abs(goal.y - start.y);
}
struct Node {
    CellPosition _Coords;
    _i64 _Cost; 
    _i64 _Heuristic;
    Node* _Parent;
    Node(CellPosition coords, _i64 cost, _i64 _heuristic, Node* parent)
        : _Coords(coords), _Cost(cost), _Heuristic(_heuristic), _Parent(parent) {}
    _i64 getTotalCost() const { return _Cost + _Heuristic; }
};
struct CompareNodes {
    bool operator ()(const Node* a, const Node* b) {
        return a->getTotalCost() > b->getTotalCost();
    }
};
void Ghost::_aStar(const std::vector<std::vector<_i64>>& grid, CellPosition goal, _bool throuth) { 
    _NewPath = true;
    _i64 condition = Cell::Door;
    if (_Free) condition = -1;
    _Ipath = 1;
    _Distance = 0;
    const _i64 numRows = grid.size();
    const _i64 numCols = grid[0].size();
    std::vector<std::vector<bool>> visited(numRows, std::vector<bool>(numCols, false));
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openSet;
    Node* startNode;
    if (!_Fear) startNode = new Node(_CellPos, 1, _heuristic(_CellPos, goal), nullptr);
    else startNode = new Node(_CellPos, -1, _heuristic(_CellPos, goal), nullptr);
    openSet.push(startNode);
    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();
        if (currentNode->_Coords.x == goal.x && currentNode->_Coords.y == goal.y) {
            std::vector<CellPosition> path;
            while (currentNode != nullptr) {
                path.emplace_back(currentNode->_Coords);
                Node* temp = currentNode->_Parent;
                delete currentNode;
                currentNode = temp;
                _Distance++;
            }
            std::reverse(path.begin(), path.end());
            path.push_back(goal);
            _Path = path;
            return;
        }
        visited[currentNode->_Coords.x][currentNode->_Coords.y] = true;
        const static std::vector<CellPosition> neighbors = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (const auto& neighborOffset : neighbors) {
            CellPosition neighbor(currentNode->_Coords.x + neighborOffset.x, 
                                  currentNode->_Coords.y + neighborOffset.y);
            if (neighbor.x >= 0 && neighbor.x < numRows &&
                neighbor.y >= 0 && neighbor.y < numCols &&
                !visited[neighbor.x][neighbor.y]          ) {
                if (!throuth) {
                    if (grid[neighbor.y][neighbor.x] != Cell::Wall &&
                        grid[neighbor.y][neighbor.x] != condition    ) {
                        _i64 newCost;
                        if (!_Fear) newCost = currentNode->_Cost + 1;
                        else newCost = currentNode->_Cost - 1;
                        Node* neighborNode = new Node(neighbor, newCost, _heuristic(neighbor, goal),
                            currentNode);
                        openSet.push(neighborNode);
                    }
                } else {
                    _i64 newCost;
                    if (grid[neighbor.y][neighbor.x] != Cell::Wall &&
                        grid[neighbor.y][neighbor.x] != condition    ) newCost = currentNode->_Cost + 1;
                    else newCost = currentNode->_Cost + 99999;
                    Node* neighborNode = new Node(neighbor, newCost, _heuristic(neighbor, goal),
                        currentNode);
                    openSet.push(neighborNode);
                }
            }
        }
    }
    _Path = {};
}
Ghost::Quarter Ghost::_whatQuarter(const CellPosition& cp) {
    if (cp.x <= 9)
        if (cp.y <= 9) return Quarter::UpLeft;
        else return Quarter::DownLeft;
    else 
        if (cp.y <= 9) return Quarter::UpRight;
        else return Quarter::DownRight;
}
Ghost::Quarter Ghost::_whatQuarter(const VectorFF& cp) {
    if (cp.y <= cp.x)
        if (cp.y >= -cp.x + _Settings::__Width * 16.f) return Quarter::Right;
        else return Quarter::Up;
    else
        if (cp.y >= -cp.x + _Settings::__Width * 16.f) return Quarter::Down;
        else return Quarter::Left;
}
void Ghost::search(const std::vector<std::vector<_i64>>& Map, Pacman& pcmn) {
    if (_Exists) {
        _SearchTimer += _Settings::__ElapsedTime;
        if (!_Fear && !_Dead && _Phase < 7) _PhaseTimer += _Settings::__ElapsedTime;
        _f32 DistanceTime = 4.f * _Distance / _Speed;
        if (DistanceTime <= 0.1f) DistanceTime = 0.1f;
        if (_PhaseTimer >= 10.f && _Phase % 2 == 0 && _Phase < 7) {
            _PhaseTimer = 0.f;
            _Phase++;
            _Scatter = false;
            _SearchTimer += DistanceTime;
        }
        if (_PhaseTimer >= 20.f && _Phase % 2 == 1 && _Phase < 6) {
            _PhaseTimer = 0.f;
            _Phase++;
            _Scatter = true;
            _SearchTimer += DistanceTime;
        }
        if (_Scatter) DistanceTime = 12.f * _Distance / _Speed;
        if (_changeMove()) _SearchTimer += DistanceTime;
        if (!_Dead) {
            if (!_Fear && _SearchTimer >= DistanceTime && !_LookMove) {
                _search(Map, pcmn);
                _SearchTimer = 0.f;
            }
            if (_Fear && _SearchTimer >= DistanceTime && !_LookMove) {
                _aStar(Map, pcmn.getCellPos());
                _SearchTimer = 0.f;
                _Change = true;
            } else _Change = false;
        }
        else {
            if (!_Return) _aStar(Map, _StartCellPos);
            _Return = true;
            _Speed = _Distance * 6.4f;
            _SearchTimer = 0.f;
        }
        _Fear = false;
        _EndFear = false;
        if (!_Dead) {
            if (pcmn.getEnergizerTime() >= 0.0001f) {
                if (!_AfterDead) { _Fear = true; _Speed = 0.7f * _PrevSpeed; _Distance = 0; _Change = true; }
            }
            else { _AfterDead = false; _Speed = _PrevSpeed; _Change = false; }
            if (pcmn.getEnergizerTime() <= 2.0001f && _Fear)
                for (_i32 i = 1; i < 10; i++)
                    if (pcmn.getEnergizerTime() > 0.2f * i) _EndFear ^= true;
                    else break;
        }
        if (_Fear && !_Dead)
            if (powf(pcmn.getCentrePos().x - _CentrePosition.x, 2) +
                powf(pcmn.getCentrePos().y - _CentrePosition.y, 2) <= 256) {
                _Fear = false;
                _Dead = true;
                _AfterDead = true;
                pcmn.addScore(100);
            }
        if (!_Fear && !_Dead)
            if (powf(pcmn.getCentrePos().x - _CentrePosition.x, 2) +
                powf(pcmn.getCentrePos().y - _CentrePosition.y, 2) <= 256) {
                _Defeat = true;
                pcmn.die();
            }
        _move(Map);
    }
}
void Ghost::_move(const std::vector<std::vector<_i64>>& Map) {
    if (!_Settings::__Victory && !_Settings::__Death) {
        _Up = false;
        _Down = false;
        _Right = false;
        _Left = false;
        _i64 condition = Cell::Door;
        if (_Free) condition = -1;
        if (Map[_CellLook.y][_CellLook.x] == Cell::Wall ||
            Map[_CellLook.y][_CellLook.x] == condition    ) {
            _Moving = false;
            _LookMove = false;
            _Change = true;
            if (_NewPath && _Path.size() != 0) _CellLook = _Path[_Ipath];
        } else _Change = false;
        if (_Path.size() == 0 || _Ipath == _Path.size()) _Moving = false;
        if (_Moving) {
            _NewPath = false;
            if (_CellPos == _CellLook || (_CellLook.x == 0 && _CellLook.y == 0)) {
                _CellLook = _Path[_Ipath];
                _Ipath++; 
            }
            if (_CellLook.x > _CellPos.x) { _Right = true; _LookMove = true; }
            if (_CellLook.x < _CellPos.x) { _Left  = true; _LookMove = true; }
            if (_CellLook.y > _CellPos.y) { _Down  = true; _LookMove = true; }
            if (_CellLook.y < _CellPos.y) { _Up    = true; _LookMove = true; }
            if (_Down)  _Position.y += _Speed * _Settings::__ElapsedTime;
            if (_Up)    _Position.y -= _Speed * _Settings::__ElapsedTime;
            if (_Right) _Position.x += _Speed * _Settings::__ElapsedTime;
            if (_Left)  _Position.x -= _Speed * _Settings::__ElapsedTime;
            _CentrePosition = _Position + (_f32)8;
            if (_Down)
                if (_Position.y >= _CellLook.y * 16.f) { _CellPos = _CellLook; _LookMove = false; }
            if (_Up)
                if (_Position.y <= _CellLook.y * 16.f) { _CellPos = _CellLook; _LookMove = false; }
            if (_Right)
                if (_Position.x >= _CellLook.x * 16.f) { _CellPos = _CellLook; _LookMove = false; }
            if (_Left)
                if (_Position.x <= _CellLook.x * 16.f) { _CellPos = _CellLook; _LookMove = false; }
        }
    }
}
void Ghost::setPosition(std::vector<std::vector<_i64>>& Map) {
    _Exists = false;
    for (_ui32 i = 0; i < _Settings::__Height; i++) {
        for (_ui32 j = 0; j < _Settings::__Width; j++) {
            if (Map[j][i] == _Kind) {
                _Exists = true;
                Map[j][i] = Cell::Empty;
                _CellPos.x = i; _CellPos.y = j;
                _StartCellPos = _CellPos;
                _CellLook = _CellPos;
                _Position.x = (_f32)(i * 16);
                _Position.y = (_f32)(j * 16);
                _CentrePosition = _Position + 8.f;
                break;
            }
        }
        if (_Exists) break;
    }
}
void Ghost::reset(std::vector<std::vector<_i64>>& Map) {
    setPosition(Map);
    _Change = false;
    _ChangeFlag = false;
    _NewPath = false;
    _Path = {};
    _Ipath = 0;
    _Distance = 0;
    _Up = false;
    _Down = false;
    _Right = false;
    _Left = false;
    _Speed = 0.9f * _Settings::__PacmanSpeed;
    _PrevSpeed = _Speed;
    _LookMove = false;
    _Fear = false;
    _EndFear = false;
    _Scatter = true;
    _Dead = false;
    _AfterDead = false;
    _Return = false;
    _Defeat = false;
    _Timer = 0.f;
    _SearchTimer = 0.f;
    _Phase      = 0;
    _PhaseTimer = 0.f;
    if (_Lock >= 0) _Free = false;
    else _Free = true;
}
void Ghost::nextGame() {
    _Change     = false;
    _ChangeFlag = false;
    _NewPath = false;
    _Path = {};
    _Ipath = 0;
    _Distance = 0;
    _CellPos = _StartCellPos;
    _CellLook = _CellPos;
    _Position = VectorFF(_StartCellPos.x * 16.f, _StartCellPos.y * 16.f);
    _CentrePosition = _Position + 8.f;
    _Free = false;
    _Up = false;
    _Down = false;
    _Left = false;
    _Right = false;
    if (_Settings::__Level < 10) _Speed = 0.9f * (_Settings::__PacmanSpeed + 2.f * _Settings::__Level);
    else _Speed = 0.9f * (_Settings::__PacmanSpeed + 20.f);
    if (_Settings::__Level >= 30) _Speed = 0.9f * (_Settings::__PacmanSpeed + 21.5f);
    _PrevSpeed = _Speed;
    _LookMove = false;
    _Fear = false;
    _EndFear = false;
    _Scatter = true;
    _Dead = false;
    _AfterDead = false;
    _Return = false;
    _Defeat = false;
    _Timer = 0.f;
    _SearchTimer = 0.f;
    _Phase = 0;
    _PhaseTimer = 0.f;
    if (_Settings::__Level >= _Lock) _Free = true;
}
void Ghost::stop() { _Moving = false; }
void Ghost::go() { _Moving = true; }
void Ghost::draw() {
    if (_Exists) {
        sf::Texture texture;
        texture.loadFromFile("Materials/Ghost" + std::to_string(_Settings::__CellSize) + '_' + _Settings::__SkinNames[_Settings::__SkinNumber] + ".png");
        if (!_Settings::__Death && !_Settings::__Victory && !_Defeat) {
            _Timer += _Settings::__ElapsedTime;
            if (_Dead) {
                if (_Timer > 5.f) {
                    _Timer = 0.f;
                    _Dead = false;
                    _Return = false;
                    _Speed = _PrevSpeed;
                }
            }
            sf::Sprite sprite(texture);
            sprite.setPosition(_Position.vect2f());
            if (!_Dead) {
                _i32 frame = _i32(_Timer / 0.2);
                if (_Timer > 1.2) { _Timer = 0.f; frame = 0; }
                sprite.setTextureRect(sf::IntRect(_Settings::__CellSize * frame, 0, _Settings::__CellSize, _Settings::__CellSize));
                if (!_Fear) sprite.setColor(_Color);
                else if (!_EndFear) sprite.setColor(RGB(103, 71, 234));
                       else sprite.setColor(RGB(82, 86, 114));
                _Window->draw(sprite);
            }
            _i32 sprL = 0;
            if (_Right) sprL = _Settings::__CellSize * 0;
            if (_Up)    sprL = _Settings::__CellSize * 1;
            if (_Left)  sprL = _Settings::__CellSize * 2;
            if (_Down)  sprL = _Settings::__CellSize * 3;
            if (_Dead)  sprL = _Settings::__CellSize * 4;
            _i32 sprT = _Settings::__CellSize * 1;
            if (_Fear && !_Dead) sprT = _Settings::__CellSize * 2;
            sprite.setTextureRect(sf::IntRect(sprL, sprT, _Settings::__CellSize, _Settings::__CellSize));
            sprite.setColor(RGB(255, 255, 255));
            _Window->draw(sprite);
        }
    }
}