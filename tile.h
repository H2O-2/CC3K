#ifndef _TILE_H_
#define _TILE_H_
#include <string>
#include <vector>
#include "object.h"
#include "textdisplay.h"

enum class TileType {Gate, DoorWay, Wall, Stair, FloorTile, Blank};

class Tile {
	const int x;
	const int y;
    int chamberNum = 0;
	std::shared_ptr<TextDisplay> td;
	bool occupied = false;
	std::shared_ptr<Object> obj;
	TileType curType = TileType::Blank;
public:
    Tile();
	Tile(int x, int y, std::shared_ptr<TextDisplay> td); // constructor for tile
	void toggleOccupy(); // toggle occupied
    void offOccupy(); // expicitly turn occupied off
	bool checkOccupy(); // return the status of occupied
	void move(); // move the obj on the tile
	TileType getType(); // return the type of the tile
	void setType(TileType p); // set curType to p
	void attachObj(std::shared_ptr<Object> o); // the object on the tile, null if it is structure or blank.
	int getX();	// get the x posn of the tile.
	int getY(); // get the y posn of the tile.
	std::shared_ptr<Object> getObj(); // get the object on the tile.
	void notify(); // notify the textdisplay if changed.
	void attack(std::shared_ptr<Tile> t); // attack at the object on tile t.
};

#endif
