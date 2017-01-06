#ifndef _RH_H_
#define _RH_H_
#include <string>
#include <memory>
#include "potion.h"

class RH: public Potion {
public:
	RH();
    void getEffect(std::shared_ptr<User> pc) override;
    std::string getRace() const override;
};

#endif
