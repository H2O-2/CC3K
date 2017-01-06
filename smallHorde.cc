#include "smallHorde.h"
using namespace std;

SmallHorde::SmallHorde(): Treasure {1} {}

string SmallHorde::getRace() const {
	return "Small Horde";
}
