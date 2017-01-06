#include <string>
#include "vampire.h"
using namespace std;

Vampire::Vampire(): Enemy{50, 25, 25, 1} {}
	
string Vampire::getRace() const {
	return "V";
}
