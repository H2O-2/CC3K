#include "PH.h"
#include "user.h"
using namespace std;

PH::PH(): Potion{-10} {}

void PH::getEffect(shared_ptr<User> pc) {
	pc->setHp(effect);
}

string PH::getRace() const {
	return "PH";
}
