#ifndef _ORC_H_
#define _ORC_H_
#include "user.h"

class Orc: public User {
public:
	Orc();
	void clearBuff() override;
	void reMoney(double gold) override;
	void setHp(int effect) override;
	std::string getRace() const override;
};

#endif
