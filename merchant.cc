#include "merchant.h"
#include "meHorde.h"
using namespace std;

Merchant::Merchant(): Enemy{30, 70, 5} {
    mh = make_shared<meHorde>();
}
	
string Merchant::getRace() const {
	return "M";
}

shared_ptr<meHorde> Merchant::getHorde() {
	return mh;
}
