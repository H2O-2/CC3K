#include <string>
#include "object.h"
using namespace std;

//void attack(std::shared_ptr<Object> obj) {}

bool Object::dead() {
	return death;
}

Object::~Object() {}
