#ifndef _SABER_H_
#define _SABER_H_
#include <string>
#include "user.h"

class Saber: public User {
public:
	Saber();
	void clearBuff() override;
	void setHp(int effect) override;
    std::string getRace() const override;
};

#endif
