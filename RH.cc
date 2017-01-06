#include "RH.h"
#include "user.h"
using namespace std;

RH::RH():Potion{10} {}

void RH::getEffect(shared_ptr<User> pc) {
	pc->setHp(effect);
}

string RH::getRace() const {
	return "RH";
}
