#ifndef _ARCHER_H_
#define _ARCHER_H_
#include <string>
#include "user.h"

class Archer: public User {
public:
	Archer();
	void clearBuff() override;
	void setHp(int effect) override;
    std::string getRace() const override;
};

#endif
