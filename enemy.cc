#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "enemy.h"
#include "user.h"
using namespace std;

Enemy::Enemy(int hp, int att, int def, double gold, int crit): Character{hp, att, def, gold, crit} {
    srand(time(0));
}

void Enemy::toggleHostile() {
	if (hostile) {
		hostile = false;
	} else {
		hostile = true;
	}
}

void Enemy::hostileOn() {
    hostile = true;
}

void Enemy::hostileOff() {
    hostile = false;
}

bool Enemy::getHostile() const {
	return hostile;
}

int Enemy::getMove() const {
	return moves;
}

void Enemy::addMove() {
	++moves;
}

void Enemy::beingAttack(shared_ptr <Character> c) {
    if (!hostile) {
        hostile = true;
    }
    if (getRace() == "M") {
        if (!dynamic_pointer_cast<User>(c)->getMerDeath()){
            dynamic_pointer_cast<User>(c)->setMerDeath();
        }
    }
	int enAtt = c->getAtt();
    int crit = c->getCrit();
	int Damage = ceil((100 / static_cast<double>(100 + def)) * enAtt);
    if (crit != 0) {
        int critChance = rand() % ((100 / crit) + 1);
        if (critChance == 0) {
            Damage *= 1.5;
        }
    }
    if (c->getRace() == "Saber") {
        int excalibur = rand() % 10;
        if (excalibur == 0) {
            Damage = hp;
        }
    }
    hp -= Damage;
    if (hp <= 0) {
        hp = 0;
        death = true;
        c->reMoney(gold);
    }
}

ObjType Enemy::getType() const {
	return ObjType::Enemy;
}
