#include "troll.h"
using namespace std;

Troll::Troll(): Enemy{120, 25, 15, 1} {}
	
string Troll::getRace() const {
	return "T";
}
