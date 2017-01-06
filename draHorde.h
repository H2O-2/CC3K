#ifndef _DRAHORDE_H_
#define _DRAHORDE_H_
#include <string>
#include <memory>
#include "dragon.h"
#include "treasure.h"
#include "tile.h"

class DraHorde: public Treasure {
    std::shared_ptr<Dragon> d;
    std::shared_ptr<Tile> draHordeTile;
public:
	DraHorde();
	void dragDeath(); // turn can be opened to true since dragon died.
	std::string getRace() const override; // return the type of the treasure.
	bool notifyDra(std::string dir); // notifyDra if user appears in the radius.
	void attachDragon(std::shared_ptr<Dragon> dra); // attach dragon to d.
    std::shared_ptr<Tile> getTile() const; // get draHordeTile
    void setTile(std::shared_ptr<Tile> t); // set tile for draHordeTile
    std::shared_ptr<Dragon> getDragon(); // return the pointer to the dragon.
};

#endif
