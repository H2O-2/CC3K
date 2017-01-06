#ifndef _PHOENIX_H_
#define _PHOENIX_H_
#include <string>
#include "enemy.h"

class Phoenix: public Enemy {
public:
	Phoenix();
	std::string getRace() const override;
};

#endif
