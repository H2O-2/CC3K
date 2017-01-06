#ifndef _DRAGON_H_
#define _DRAGON_H_
#include <string>
#include <memory>
#include "enemy.h"

class DraHorde;

class Dragon: public Enemy {
	std::shared_ptr<DraHorde> dh;
public:
	Dragon();
	Dragon(std::shared_ptr<DraHorde> dh);
	std::shared_ptr<DraHorde> getHorde(); // get dh
    void setHorde(std::shared_ptr<DraHorde> horde); // set dh
	void notifyHord(); // notify dh if dragon is killed
	std::string getRace() const override;
};

#endif
