#include "character.h"
#include <iostream>
using namespace std;

Character::Character(int hp, int att, int def, double gold, int crit) : hp{hp}, att{att}, def{def}, gold{gold}, crit{crit} {}

int Character::getAtt() {
	return att;
}
void Character::attack(shared_ptr<Object> obj, shared_ptr<Object> mySelf) {
    obj->beingAttack(dynamic_pointer_cast<Character>(mySelf));
}

double Character::getGold() {
	return gold;
}

void Character::reMoney(double money) {
    gold += money;
}

int Character::getHp () const {
    return hp;
}

int Character::getCrit () const {
    return crit;
}
