#include "elves.h"
using namespace std;

Elves::Elves(): User{140, 30, 10} {}

void Elves::clearBuff() {
	att = 30;
	def = 10;
}

void Elves::setAtt(int effect) {
	if (effect < 0) {
		effect *= -1;
	}
	att += effect;
}

void Elves::setDef(int effect) {
	if (effect < 0) {
		effect *= -1;
	}
	def += effect;
}

void Elves::setHp(int effect) {
	if (effect < 0) {
		effect *= -1;
	}
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 140) {
		hp = 140;
	}
}

string Elves::getRace() const {
	return "Elves";
}
