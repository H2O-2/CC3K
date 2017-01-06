#include "phoenix.h"
using namespace std;

Phoenix::Phoenix(): Enemy{50, 35, 20, 1} {}
	
string Phoenix::getRace() const {
	return "X";
}
