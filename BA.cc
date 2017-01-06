#include <string>
#include "BA.h"
#include "user.h"
using namespace std;

BA::BA() : Potion{5} {}

void BA::getEffect(std::shared_ptr<User> pc) {
	pc->setAtt(effect);
}

string BA::getRace() const {
	return "BA";
}
