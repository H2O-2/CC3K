#ifndef _DWARF_H_
#define _DWARF_H_
#include <string>
#include "user.h"

class Dwarf: public User {
public:
	Dwarf();
	void clearBuff() override;
	void reMoney(double gold) override;
	void setHp(int effect) override;
	std::string getRace() const override;
};

#endif
