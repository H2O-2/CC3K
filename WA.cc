#include <string>
#include "WA.h"
#include "user.h"
using namespace std;

WA::WA(): Potion {-5} {}

void WA::getEffect(shared_ptr<User> pc) {
	pc->setAtt(effect);
}

string WA::getRace() const {
	return "WA";
}
