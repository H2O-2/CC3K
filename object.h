#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <string>
#include <memory>

enum class ObjType {User, Enemy, Treasure, Potion};

class Character;

class Object {
protected:
	bool death = false;
public:
	virtual ObjType getType() const = 0; // get the ObjType for the object
	virtual std::string getRace() const = 0; 
	bool dead(); // get death
	//virtual void attack(std::shared_ptr<Object> obj);
	virtual void beingAttack(std::shared_ptr<Character> c) = 0;
    virtual ~Object();
};

#endif
