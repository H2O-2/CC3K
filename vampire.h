#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_
#include <string>
#include "enemy.h"

class Vampire: public Enemy {
public:
	Vampire();
	std::string getRace() const override;
};

#endif
