#ifndef _WD_H_
#define _WD_H_
#include <string>
#include "potion.h"

class User;

class WD: public Potion {
public:
	WD();
	void getEffect(std::shared_ptr<User> pc) override;
	std::string getRace() const override;
};

#endif
