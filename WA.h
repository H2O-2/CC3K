#ifndef _WA_H_
#define _WA_H_
#include "potion.h"

class User;

class WA: public Potion {
public:
	WA();
	void getEffect(std::shared_ptr<User> pc) override;
	std::string getRace() const override;
};

#endif
