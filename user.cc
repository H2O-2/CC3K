#include <cmath>
//debug
#include <iostream>

#include "user.h"
using namespace std;

User::User(int hp, int att, int def, double gold, int crit): Character{hp, att, def, gold, crit} {}

State User::getState() const {
	return curState;
}

void User::setState(State s) {
	curState = s;
}

double User::getGold() const {
	return gold;
}

void User::setAtt(int effect) {
	att += effect;
	if (att < 0) {
		att = 0;
	}
}

void User::setDef(int effect) {
	def += effect;
	if (def < 0) {
		def = 0;
	}
}

void User::setCrit(int effect) {
    crit += effect;
    if (crit > 100) {
        crit = 100;
    }
}

void User::beingAttack(shared_ptr<Character> c) {
	int enAtt = c->getAtt();
	int Damage = ceil((100 / static_cast<double>(100 + def)) * enAtt);
	hp -= Damage;
	if (hp <= 0) {
        hp = 0;
		death = true;
	}
}

int User::getDef() const {
	return def;
}

void User::addPotion(string p) {
	bool exist = false;
	for (unsigned int i = 0; i < usedP.size(); ++i) {
		if (p == usedP[i]) {
			exist = true;
		}
	}
	if (!exist) {
		usedP.emplace_back(p);
	}
}

bool User::checkPotion(string p) {
	for (unsigned int i = 0; i < usedP.size(); ++i) {
		if (p == usedP[i]) {
			return true;
		}
	}
    return false;
}

int User::getX() const {
    return x;
}

int User::getY() const {
    return y;
}

void User::setPosn(const int x_x, const int y_y) {
    x = x_x;
    y = y_y;
}

void User::setMerDeath () {
    killedMerchant = true;
}

bool User::getMerDeath() {
    return killedMerchant;
}

void User::toggleCP() {
    chaosPotion = !chaosPotion;
}

bool User::getCP() {
    return chaosPotion;
}

ObjType User::getType() const {
    return ObjType::User;
}

User::~User() {}
