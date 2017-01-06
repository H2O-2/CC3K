#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <string>
#include <vector>
#include "user.h"

class Floor;
class Tile;

class TextDisplay {
	std::vector <std::vector<char>> display;
	std::shared_ptr<User> PC;
public:
	TextDisplay(); // construct whole map
    void notify(int x, int y, char type); // get type string and change corresponding Tile
    void setUser(std::shared_ptr<User> user);
    
    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td); 
};

#endif
