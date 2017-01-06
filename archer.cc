#include "archer.h"
using namespace std;

Archer::Archer(): User{90, 20, 25, 0, 40} {}

void Archer::clearBuff() {
	att = 20;
	def = 25;
    crit = 40;
}

string Archer::getRace() const {
	return "Archer";
}

void Archer::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 90) {
		hp = 90;
	}
}
