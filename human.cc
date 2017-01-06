#include "human.h"
using namespace std;

Human::Human(): User{140, 20, 20} {}

void Human::clearBuff() {
	att = 20;
	def = 20;
}

string Human::getRace() const {
	return "Human";
}

void Human::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 140) {
		hp = 140;
	}
}
