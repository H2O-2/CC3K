#include "normHorde.h"
using namespace std;

NormHorde::NormHorde(): Treasure{1} {}

string NormHorde::getRace() const {
	return "Normal Horde";
}
