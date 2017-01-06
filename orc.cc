#include "orc.h"
using namespace std;

Orc::Orc(): User{180, 30, 25} {}

void Orc::clearBuff() {
	att = 30;
	def = 25;
}

void Orc::reMoney(double money) {
	gold += money / 2;
}

string Orc::getRace() const {
	return "Orc";
}

void Orc::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 180) {
		hp = 180;
	}
}
