#include "meHorde.h"
using namespace std;

meHorde::meHorde() : Treasure{4} {}

string meHorde::getRace() const {
	return "Merchant Horde";
}
