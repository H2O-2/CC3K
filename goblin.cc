#include "goblin.h"
using namespace std;

Goblin::Goblin(): Enemy{70, 5, 10, 1} {}
	
string Goblin::getRace() const {
	return "N";
}
