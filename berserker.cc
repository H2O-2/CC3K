#include "berserker.h"
#include <cmath>
using namespace std;

Berserker::Berserker(): User{100, 15, 50} {}

void Berserker::clearBuff() {
    if (revived) {
        att = 40;
        def = 10;
        crit = 0;
    } else {
        att = 10;
        def = 40;
        crit = 10;
    }
}

string Berserker::getRace() const {
	return "Berserker";
}

void Berserker::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
        INeverDie();
	} else if (hp > 200) {
		hp = 200;
	}
}

void Berserker::INeverDie() {
    if (!revived) {
        hp = 150;
        att = 40;
        def = 10;
        crit = 10;
        revived = true;
    } else {
        hp = 0;
        death = true;
    }
}

void Berserker::beingAttack(shared_ptr<Character> c) {
    int enAtt = c->getAtt();
    int Damage = ceil((100 / static_cast<double>(100 + def)) * enAtt);
    hp -= Damage;
    if (hp <= 0) {
        INeverDie();
    } else if (hp > 150) {
        hp = 150;
    }
}
