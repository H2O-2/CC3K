#include "draHorde.h"
using namespace std;

DraHorde::DraHorde(): Treasure{6, false} {}

void DraHorde::dragDeath() {
	canBeOpened = true;
}

string DraHorde::getRace() const {
	return "Dragon Horde";
}

void DraHorde::attachDragon (shared_ptr<Dragon> dra) {
	d = dra;
}

bool DraHorde::notifyDra(string dir) {
    if (dir == "No User") {
        return false;
    } else {
        d->hostileOn();
        return true;
    }
}

shared_ptr<Dragon> DraHorde::getDragon() {
	return d;
}

shared_ptr<Tile> DraHorde::getTile() const {
    return draHordeTile;
}

void DraHorde::setTile(shared_ptr<Tile> t) {
    draHordeTile = t;
}
