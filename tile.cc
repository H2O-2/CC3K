#include "object.h"
#include "tile.h"
#include "dragon.h"
#include "merchant.h"
using namespace std;

Tile::Tile() : x{0}, y{0}, td{nullptr} {}

Tile::Tile(int x, int y,shared_ptr<TextDisplay> td):x{x}, y{y}, td{td} {}

bool Tile::checkOccupy() {
	return occupied;
}

void Tile::toggleOccupy() {
	if (occupied) {
		occupied = false;
	} else {
		occupied = true;
	}
}

void Tile::offOccupy() {
    occupied = false;
}

TileType Tile::getType() {
	return curType;
}

void Tile::setType(TileType p) {
	curType = p;
}

void Tile::attachObj(shared_ptr<Object> o) {
	obj = o;
}

int Tile::getX() {
	return x;
}

int Tile::getY() {
	return y;
}

shared_ptr<Object> Tile::getObj() {
	return obj;
}

void Tile::notify() {
    if (obj) {
        if (obj->getType() == ObjType::User) {
		td->notify(x, y, '@');
        } else if (obj->getType() == ObjType::Enemy) {
            string s = obj->getRace();
            td->notify(x, y, s[0]);
        } else if (obj->getType() == ObjType::Potion) {
            td->notify(x, y, 'P');
        } else if (obj->getType() == ObjType::Treasure) {
        td->notify(x, y, 'G');
        }
    } else {
        if (curType == TileType::Gate) {
            td->notify(x, y, '\\');
        } else if (curType == TileType::FloorTile) {
            td->notify(x, y, '.');
        } else if (curType == TileType::DoorWay) {
            td->notify(x, y, '+');
        } else if (curType == TileType::Stair) {
            td->notify(x, y, '#');
        }
    }
}

void Tile::attack(shared_ptr<Tile> t) {
    shared_ptr<Object> enm = t->getObj();
    dynamic_pointer_cast<Character> (obj)->attack(enm, obj);
	if (enm->dead()) {
        if(enm->getRace() == "D") {
            dynamic_pointer_cast<Dragon> (enm)->notifyHord();
            t->attachObj(nullptr);
            t->toggleOccupy();
        } else if (enm->getRace() == "M") {
            t->attachObj(dynamic_pointer_cast<Merchant> (enm)->getHorde());
        }  else {
            t->attachObj(nullptr);
            t->toggleOccupy();
        }
        t->notify();
	}
}
