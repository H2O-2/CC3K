#ifndef _meHORDE_H_
#define _meHORDE_H_
#include <string>
#include "treasure.h"

class meHorde: public Treasure {
public:
	meHorde();
	std::string getRace() const override;
};

#endif
