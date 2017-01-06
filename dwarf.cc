#include "dwarf.h"
using namespace std;

Dwarf::Dwarf(): User{100, 20, 30} {}

void Dwarf::clearBuff() {
	att = 20;
	def = 30;
}

void Dwarf::reMoney(double money) {
	gold += money * 2;
}

string Dwarf::getRace() const {
	return "Dwarf";
}

void Dwarf::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 100) {
		hp = 100;
	}
}
