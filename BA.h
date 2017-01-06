#ifndef _BA_H_
#define _BA_H_
#include <string>
#include <memory>
#include "potion.h"

class User;
class Potion;

class BA : public Potion {
public:
	BA();
	void getEffect(std::shared_ptr<User> pc) override;
	std::string getRace() const override;
};

#endif
