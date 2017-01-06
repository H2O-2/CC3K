#ifndef _HUMAN_H_
#define _HUMAN_H_
#include <string>
#include "user.h"

class Human: public User {
public:
	Human();
	void clearBuff() override;
	void setHp(int effect) override;
	std::string getRace() const override;
};

#endif
