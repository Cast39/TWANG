#include "Arduino.h"

class Enemy
{
  public:
    void Spawn(int pos, int dir, int sp, int wobble, int offset);
    void Tick();
    void Kill();
    void bringToLive();
    bool Alive();
    int _pos;
    int _wobble;
    int playerSide;
  private:
    int _dir;
    int _sp;
    int _alive;
    int _origin;
    int _offset;
    long _spawntime;
};

void Enemy::Spawn(int pos, int dir, int sp, int wobble, int offset){
    _pos = pos;
    _dir = dir;          // 0 = left, 1 = right
    _wobble = wobble;    // 0 = no, >0 = yes, value is width of wobble
    _origin = pos;
    _sp = sp;
    _alive = -1; // -1:  Spawed, but deactivated 0: Dead 1: Alive
    _offset = offset;
    _spawntime = millis();
}

void Enemy::Tick(){
    if(_alive == 1){
        if(_wobble > 0){
            _pos = _origin + (sin((millis()/3000.0)*_sp)*_wobble);
        }else{
            if(_dir == 0){
                _pos -= _sp;
            }else{
                _pos += _sp;
            }
            if(_pos > 1000) {
                Kill();
            }
            if(_pos <= 0) {
                Kill();
            }
        }
    } else if (_alive == -1){
      if (millis() - _spawntime >= _offset) {
        _alive = 1;
      }
    }
}

bool Enemy::Alive(){
    return _alive;
}

void Enemy::Kill(){
    _alive = 0;
}
