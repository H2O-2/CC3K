#include "werewolf.h"
using namespace std;

Werewolf::Werewolf(): Enemy{120, 30, 5, 1} {}
	
string Werewolf::getRace() const {
	return "W";
}
