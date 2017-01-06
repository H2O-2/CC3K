#include "saber.h"
using namespace std;

Saber::Saber(): User{120, 20, 30} {}

void Saber::clearBuff() {
	att = 20;
	def = 30;
    crit = 0;
}

string Saber::getRace() const {
	return "Saber";
}

void Saber::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 120) {
		hp = 120;
	}
}
