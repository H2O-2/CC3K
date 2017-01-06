#ifndef _BD_H_
#define _BD_H_
#include <string>
#include <memory>
#include "potion.h"
#include "object.h"

class User;

class BD: public Potion {
public:
	BD();
	void getEffect(std::shared_ptr<User> pc) override;
	std::string getRace() const override;
};

#endif
