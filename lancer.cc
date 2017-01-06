#include <ctime>
#include <cstdlib>
#include <cmath>
#include "lancer.h"
using namespace std;

Lancer::Lancer(): User{120, 35, 10, 0, 20} {
    srand(time(0));
}

void Lancer::clearBuff() {
	att = 35;
	def = 10;
    crit = 20;
}

string Lancer::getRace() const {
	return "Lancer";
}

void Lancer::setHp(int effect) {
	hp += effect;
	if (hp <= 0) {
		hp = 0;
		death = true;
	} else if (hp > 120) {
		hp = 120;
	}
}

void Lancer::reMoney(double money) {
    int luckyE = rand() % 2;
    if (!luckyE) {
        gold += money;
    }
}

void Lancer::beingAttack(shared_ptr<Character> c) {
    int enAtt = c->getAtt();
    int Damage = ceil((100 / static_cast<double>(100 + def)) * enAtt);
    int hit = rand() % 2;
    if (hit == 0) {
        Damage = 0;
    }
    hp -= Damage;
    if (hp <= 0) {
        hp = 0;
        death = true;
    }
}
