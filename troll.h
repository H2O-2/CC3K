#ifndef _TROLL_H_
#define _TROLL_H_
#include <string>
#include "enemy.h"

class Troll: public Enemy {
public:
	Troll();
	std::string getRace() const override;
};

#endif
