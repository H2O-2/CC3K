#ifndef _ELVES_H_
#define _ELVES_H_
#include <string>
#include "user.h"

class Elves: public User {
public:
	Elves();
	void clearBuff() override;
	void setAtt(int effect) override;
	void setDef(int effect) override;
	void setHp(int effect) override;
	std::string getRace() const override;
};

#endif
