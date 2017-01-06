#ifndef _NORMHORDE_H_
#define _NORMHORDE_H_
#include <string>
#include "object.h"
#include "treasure.h"

class NormHorde: public Treasure {
public:
	NormHorde();
	std::string getRace() const override;
};

#endif
