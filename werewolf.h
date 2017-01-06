#ifndef _WEREWOLF_H_
#define _WEREWOLF_H_
#include <string>
#include "enemy.h"

class Werewolf: public Enemy {
public:
	Werewolf();
	std::string getRace() const override;
};

#endif
