#include "user.h"
#include "potion.h"
#include "object.h"
#include <iostream>
using namespace std;

Potion::Potion(int effect): effect{effect} {}

void Potion::attack(shared_ptr<Object> obj) {}

void Potion::beingAttack(shared_ptr<Character> c) {
	getEffect(dynamic_pointer_cast<User> (c));
    death = true;
}

ObjType Potion::getType() const {
    return ObjType::Potion;
}
