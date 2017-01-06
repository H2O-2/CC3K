#ifndef _GOBLIN_H_
#define _GOBLIN_H_
#include <string>
#include "enemy.h"

class Goblin: public Enemy {
public:
	Goblin();
	std::string getRace() const override;
};

#endif
