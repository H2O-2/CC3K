#include "BD.h"
#include "user.h"
using namespace std;

BD::BD(): Potion{5} {}

void BD::getEffect(std::shared_ptr<User> pc) {
	pc->setDef(effect);
}

string BD::getRace() const {
	return "BD";
}
