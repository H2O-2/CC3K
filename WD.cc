#include <string>
#include "WD.h"
#include "user.h"
using namespace std;

WD::WD(): Potion{-5} {}

void WD::getEffect(shared_ptr<User> pc) {
	pc->setDef(effect);
}

string WD::getRace() const {
	return "WD";
}
