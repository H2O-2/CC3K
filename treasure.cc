#include "treasure.h"
#include "character.h"

using namespace std;

Treasure::Treasure(int gold, bool open) :gold{gold}, canBeOpened{open} {}

void Treasure::attack(shared_ptr<Object> obj) {}

int Treasure::goldValue() {
	return gold;
}

void Treasure::beingAttack(shared_ptr<Character> obj) {
    if (canBeOpened) {
        obj->reMoney(goldValue());
    }
}

ObjType Treasure::getType() const {
    return ObjType::Treasure;
}

bool Treasure::open() {
    return canBeOpened;
}
