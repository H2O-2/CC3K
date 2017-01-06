#include <string>
#include "dragon.h"
#include "draHorde.h"
using namespace std;

Dragon::Dragon(shared_ptr<DraHorde> dh): Enemy{150, 20, 20}, dh{dh} {}
Dragon::Dragon() : Enemy{150, 20, 20} {}

string Dragon::getRace() const {
	return "D";
}

void Dragon::notifyHord() {
	dh->dragDeath();
}

shared_ptr<DraHorde> Dragon::getHorde() {
	return dh;
}

void Dragon::setHorde(std::shared_ptr<DraHorde> horde) {
    dh = horde;
}
