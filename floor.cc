#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "floor.h"
#include "tile.h"
#include "potion.h"
#include "treasure.h"
#include "enemy.h"
#include "user.h"
#include "human.h"

using namespace std;

const int COL = 79; // number of columns of tiles
const int ROW = 25; // number of rows of tiles
const int C_NUM = 5; // number of chambers
const int E_NUM = 20; // number of enemy
const int I_NUM = 10; // number of potion and gold
const string NO = "no";
const string SO = "so";
const string EA = "ea";
const string WE = "we";
const string NE = "ne";
const string NW = "nw";
const string SE = "se";
const string SW = "sw";

shared_ptr<Tile> Floor::dirConver(shared_ptr<Tile> t, string dir) {
    int x = t->getX();
    int y = t->getY();
    if (dir == NO) {
        return grid[y - 1][x];
    } else if (dir == SO) {
        return grid[y + 1][x];
    } else if (dir == EA) {
        return grid[y][x + 1];
    } else if (dir == WE) {
        return grid[y][x - 1];
    } else if (dir == NE) {
        return grid[y - 1][x + 1];
    } else if (dir == NW) {
        return grid[y - 1][x - 1];
    } else if (dir == SE) {
        return grid[y + 1][x + 1];
    } else {
        return grid[y + 1][x - 1];
    }
}

void Floor::floorCtor() {
    f = shared_ptr<Factory> (new Factory);
    td = shared_ptr<TextDisplay> (new TextDisplay);
    for(int r = 0; r < ROW; ++r) {
        vector <shared_ptr<Tile>> tempRow;
        for(int c = 0; c < COL; ++c) {
            shared_ptr<Tile> tempTile (new Tile(c, r, td));
            tempRow.emplace_back(tempTile);
        }
        grid.emplace_back(tempRow);
    }
}

Floor::Floor() {
    floorCtor();
}

Floor::Floor(string fileName):file{fileName} {
    inventByFile = true;
    floorCtor();
}

Floor::~Floor() {}

void chamber_init(vector <vector <shared_ptr<Tile>>> grid, shared_ptr<Chamber> cham, int chamcol, int chamrow, int startcol, int startrow) {
    // chamcol is the number of columns of this chamber
    // chamrow is the number of rows of this chamber
    // startcol is the starting index of column
    // startrow is the starting index of row
    int door = 0; // number of DoorWays
    for(int r = 0; r < chamrow; ++r) {
        vector <shared_ptr<Tile>> temprow;
        for (int c = 0; c < chamcol; ++c) {
            cham->setChamberTile(r, c, grid[r + startrow][c + startcol]);
            if (grid[r + startrow][c + startcol]->getType() == TileType::DoorWay &&
                (chamrow != C_2_HEIGHT || (chamrow == C_2_HEIGHT && !cham->chamber2Check(grid[r + startrow][c + startcol])))) {
                cham->setDoorTile(door, grid[r + startrow][c + startcol]);
                door++;
            }
        }
    }
}

bool Floor::stairMove(string dir, int x, int y) {
    shared_ptr<Tile> cur = grid[y][x];
    shared_ptr<Tile> next = dirConver(grid[y][x], dir);
    if (next->getType() == TileType::Blank) {
        return false;
    } else {
        cur->toggleOccupy();
        next->toggleOccupy();
        shared_ptr<Object> obj = cur->getObj();
        next->attachObj(obj);
        shared_ptr<User> userPtr = dynamic_pointer_cast<User> (obj);
        if (next->getType() == TileType::DoorWay) {
            for (int i = 0; i < C_NUM; i++) {
                for (int j = 0; j < DOORWAY; j++) {
                    if (next == room[i]->getDoorTile(j)) {
                        userPtr->setState(State::Chamber);
                        room[i]->toggleCharStat();
                    }
                }
                
            }
        }
        cur->attachObj(nullptr);
        userPtr->setPosn(next->getX(), next->getY());
        cur->notify();
        next->notify();

        return true;
    }
}

void Floor::init() { // change to pointer
    // initialize floor
    ifstream map("map.txt");
    string s;
    int rowindex = 0;
    int colindex = 0;  //column index
    while(getline(map, s)) {
        istringstream ss{s};
        char c;
        while(ss >> noskipws >> c) {
            if(c == '|' || c == '-') {
                grid[rowindex][colindex]->setType(TileType::Wall);
            }
            else if(c == '+') {
                grid[rowindex][colindex]->setType(TileType::DoorWay);
            } else if(c == '.') {
                grid[rowindex][colindex]->setType(TileType::FloorTile);
            } else if(c == '#') {
                grid[rowindex][colindex]->setType(TileType::Stair);
            }
            ++colindex;
        }
        ++rowindex;
        colindex = 0;
    }
    
    
    shared_ptr<Chamber> cham1 (new Chamber(7, 29, 2, 2));
    chamber_init(grid, cham1, 29, 7, 2, 2);
    shared_ptr<Chamber> cham2 (new Chamber(13, 40, 37, 2));
    chamber_init(grid, cham2, 40, 13, 37, 2);
    
    shared_ptr<Chamber> cham3 (new Chamber(7, 14, 37, 8));
    chamber_init(grid, cham3, 14, 7, 37, 8);
    
    shared_ptr<Chamber> cham4 (new Chamber(10, 24, 3, 13));
    chamber_init(grid, cham4, 24, 10, 3, 13);
    
    shared_ptr<Chamber> cham5 (new Chamber(9, 42, 35, 14));
    chamber_init(grid, cham5, 42, 9, 35, 14);
    
    room.emplace_back(cham1);
    room.emplace_back(cham2);
    room.emplace_back(cham3);
    room.emplace_back(cham4);
    room.emplace_back(cham5);
}

void Floor::createGame(string race) {
    // User
    if (!userPtr) {
        userPtr = dynamic_pointer_cast<User> (f->GenPlayer(race));
    }
    
    int userChamber = rand() % C_NUM;
    
    if (userChamber == 0) {
        room[userChamber]->genPosn(userPtr);
        userPtr->setState(State::Chamber);
        room[userChamber]->toggleCharStat();
    } else if (userChamber == 1) {
        room[userChamber]->genPosn(userPtr);
        userPtr->setState(State::Chamber);
        room[userChamber]->toggleCharStat();
    } else if (userChamber == 2) {
        room[userChamber]->genPosn(userPtr);
        userPtr->setState(State::Chamber);
        room[userChamber]->toggleCharStat();
    } else if (userChamber == 3) {
        room[userChamber]->genPosn(userPtr);
        userPtr->setState(State::Chamber);
        room[userChamber]->toggleCharStat();
    } else if (userChamber == 4) {
        room[userChamber]->genPosn(userPtr);
        userPtr->setState(State::Chamber);
        room[userChamber]->toggleCharStat();
    }
    
    // Gate
    bool validGate = false;
    
    while (!validGate) {
        int i = rand() % (C_NUM);
        shared_ptr<Chamber> gateChamber = room[i];
        validGate = gateChamber->genGate();
    }
    
    // Potion & Treasure
    int dragonNum = 0;
    for (int i = 0; i < I_NUM; i++) {
        int c = rand() % (C_NUM);
        //shared_ptr<Potion> potionPtr = dynamic_pointer_cast<Potion> (f->GenPotion());
        room[c]->genPosn(f->GenPotion());
        c = rand() % (C_NUM);
        shared_ptr<Object> treasurePtr = f->GenTreasure();
        room[c]->genPosn(treasurePtr);
        if (treasurePtr->getRace() == "Dragon Horde") {
            shared_ptr<DraHorde> draHordePtr = dynamic_pointer_cast<DraHorde> (treasurePtr);
            shared_ptr<Dragon> dragonPtr = f->GenDragon(draHordePtr);
            room[c]->genPosn(draHordePtr, dragonPtr);
            dragonNum++;
        }
    }
    
    // Enemy
    for (int j = 0; j < E_NUM - dragonNum; j++) {
        int c = rand() % (C_NUM);
        shared_ptr<Enemy> enemyPtr = dynamic_pointer_cast<Enemy> (f->GenEnemy());
        room[c]->genPosn(enemyPtr);
    }
}

void Floor::createByFile(string race) {
    for(int row = 0; row < 25; ++row) {
        for(int col = 0; col <= 79; ++col) {
            char c;
            file >> noskipws >> c;
            shared_ptr<Object> obj;
            if(c == '0') {
                obj = f->GenPotion(RH_P);
            } else if(c == '1') {
                obj = f->GenPotion(BA_P);
            } else if(c == '2') {
                obj = f->GenPotion(BD_P);
            } else if(c == '3') {
                obj = f->GenPotion(PH_P);
            } else if(c == '4') {
                obj = f->GenPotion(WA_P);
            } else if(c == '5') {
                obj = f->GenPotion(WD_P);
            } else if(c == '6') {
                obj = f->GenTreasure(N_HORDE);
            } else if(c == '7') {
                obj = f->GenTreasure(S_HORDE);
            } else if(c == '8') {
                obj = f->GenTreasure(M_HORDE);
            } else if(c == '9') {
                shared_ptr <DraHorde> draHorde = dynamic_pointer_cast<DraHorde> (f->GenTreasure(D_HORDE));
                draHorde->setTile(grid[row][col]);
                if(col - 1 >= 0 && grid[row][col-1]->getObj() != nullptr && grid[row][col-1]->getObj()->getRace() == "D") {
                    shared_ptr <Dragon> dragon = dynamic_pointer_cast<Dragon> (grid[row][col-1]->getObj());
                    draHorde->attachDragon(dragon);
                    dragon->setHorde(draHorde);
                }
                if(row - 1 >= 0 && grid[row - 1][col]->getObj() != nullptr && grid[row-1][col]->getObj()->getRace() == "D") {
                    shared_ptr <Dragon> dragon = dynamic_pointer_cast<Dragon> (grid[row-1][col]->getObj());
                    draHorde->attachDragon(dragon);
                    dragon->setHorde(draHorde);
                }
                obj = draHorde;
            } else if(c == 'W') {
                obj = f->GenEnemy(WEREWOLF);
            } else if(c == 'V') {
                obj = f->GenEnemy(VAMPIRE);
            } else if(c == 'N') {
                obj = f->GenEnemy(GOBLIN);
            } else if(c == 'T') {
                obj = f->GenEnemy(TROLL);
            } else if(c == 'X') {
                obj = f->GenEnemy(PHEONIX);
            } else if(c == 'M') {
                obj = f->GenEnemy(MERCHANT);
            } else if(c == 'D') {
                shared_ptr <Dragon> dragon = dynamic_pointer_cast<Dragon> (f->GenDragon());
                if(col - 1 >= 0 && grid[row][col-1]->getObj() != nullptr && grid[row][col-1]->getObj()->getRace() == "Dragon Horde") {
                    shared_ptr <DraHorde> draHorde = dynamic_pointer_cast<DraHorde> (grid[row][col-1]->getObj());
                    draHorde->attachDragon(dragon);
                    dragon->setHorde(draHorde);
                    obj = dragon;
                }
                if(row - 1 >= 0 && grid[row-1][col]->getObj() != nullptr && grid[row-1][col]->getObj()->getRace() == "Dragon Horde") {
                    shared_ptr <DraHorde> draHorde = dynamic_pointer_cast<DraHorde> (grid[row-1][col]->getObj());
                    draHorde->attachDragon(dragon);
                    dragon->setHorde(draHorde);
                    obj = dragon;
                }
            } else if(c == '@') {
                if(userPtr) obj = userPtr;
                else obj = f->GenPlayer(race);
                userPtr = dynamic_pointer_cast<User> (obj);
                shared_ptr<User> user = dynamic_pointer_cast<User>(obj);
                user->setPosn(col, row);
                user->setState(State::Chamber);
                if(col >= 2 && col <= 2+29 && row >= 2 && row <= 2+7) {
                    room[0]->toggleCharStat();
                } else if(col >= 37 && col <= 37+40 && row >= 2 && row <= 2+13) {
                    if(room[1]->chamber2Check(grid[row - DIFFCHAMBER2Y][col - DIFFCHAMBER2X])) room[2]->toggleCharStat();
                    else room[1]->toggleCharStat();
                } else if(col >= 36 && col <= 36+14 && row >= 8 && row <= 8+7) {
                    room[2]->toggleCharStat();
                } else if(col >= 3 && col <= 3+24 && row >= 13 && row <= 13+10) {
                    room[3]->toggleCharStat();
                } else if(col >= 35 && col <= 35+42 && row >= 14 && row <= 14+9) {
                    room[4]->toggleCharStat();
                } else {
                    user->setState(State::Stair);
                }
            } else if(c == '\\') {
                grid[row][col]->setType(TileType::Gate);
                grid[row][col]->notify();
            }
            if(c == '0' || c== '1'|| c== '2'|| c== '3'|| c== '4'|| c== '5'|| c== '6'|| c== '7'|| c== '8'
               || c== '9'|| c== 'W'|| c== 'V'|| c== 'N'|| c== 'T'|| c== 'X'|| c== 'M'|| c== 'D'|| c== '@') {
                grid[row][col]->attachObj(obj);
                grid[row][col]->notify();
                grid[row][col]->toggleOccupy();
            }
        }
    }
}

string Floor::converToStr (string dir) {
    if (dir == NO) {
        return "North";
    } else if (dir == SO) {
        return "South";
    } else if (dir == EA) {
        return "East";
    } else if (dir == WE) {
        return "West";
    } else if (dir == NE) {
        return "North East";
    } else if (dir == NW) {
        return "North West";
    } else if (dir == SE) {
        return "South East";
    } else {
        return "South West";
    }
}

void Floor::charMove(string dir) {
    int x = userPtr->getX();
    int y = userPtr->getY();
    bool moveSuccess = false;
    int roomNum = 0;
    
    if (userPtr->getState() == State::Stair) {
        moveSuccess = stairMove(dir, x, y);
    } else {
        for (int i = 0; i < C_NUM; i++) {
            if (room[i]->charStat()) {
                moveSuccess = room[i]->charMove(dir, x, y);
                roomNum = i;
                break;
            }
        }
    }
    if (moveSuccess) {
        int x = userPtr->getX();
        int y = userPtr->getY();
        if (grid[y][x]->getType() == TileType::Gate) {
            nextFloor();
        } else {
            moveEnm();
        }
        movement = "PC moves " + converToStr(dir);
        shared_ptr<Tile> nextTile = dirConver(grid[y][x], dir);
        shared_ptr<Object> next = nextTile->getObj();
        if (next) {
            if (next->getType() == ObjType::Potion) {
                string race = next->getRace();
                if (userPtr->checkPotion(race)) {
                    movement += " and sees potion " + race;
                } else {
                    userPtr->addPotion(race);
                    movement += " and sees unknown potion";
                }
            }
        }
    } else {
        movement = "INCORRECT MOVEMENT";
    }
    movement += ".";
    movement += room[roomNum]->getAttInfo();
}

void Floor::charAtt(string dir) {
    int x = userPtr->getX();
    int y = userPtr->getY();
    bool attSuccess = false;
    int roomNum = 0;
    if (userPtr->getState() == State::Chamber) {
        for (int i = 0; i < C_NUM; i++) {
            if (room[i]->charStat()) {
                attSuccess = room[i]->charAtt(dir, x, y);
                roomNum = i;
                break;
            }
        }
    }
    if (attSuccess) {
        moveEnm();
        movement = room[roomNum]->getAttInfo();
    } else {
        movement = "INCORRECT MOVEMENT";
    }
}

void Floor::charUse(string dir) {
    int x = userPtr->getX();
    int y = userPtr->getY();
    string race = dirConver(grid[y][x], dir)->getObj()->getRace();
    int roomNum = 0;
    bool useSuccess = false;
    if (userPtr->getState() == State::Chamber) {
        for (int i = 0; i < C_NUM; i++) {
            if (room[i]->charStat()) {
                useSuccess = room[i]->charUse(dir, x, y);
                roomNum = i;
                break;
            }
        }
    }
    if (useSuccess) {
        moveEnm();
        movement = "PC uses " + race + ".";
        movement += room[roomNum]->getAttInfo();
    } else {
        movement = "INCORRECT MOVEMENT.";
    }
}

void Floor::moveEnm() {
    for (int i = 0; i < C_NUM; i++) {
        room[i]->moveEnem();
    }
}

bool Floor::checkDeath() {
    return userPtr->dead();
}

double Floor::score() {
    double gold = userPtr->getGold();
    if(userPtr->getRace() == "Human") {
        return gold + gold / 2;
    }
    return gold;
}

void Floor::clearFloor() {
    for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
            grid[i][j]->offOccupy();
			grid[i][j]->attachObj(nullptr);
            if (grid[i][j]->getType() == TileType::Gate) {
                grid[i][j]->setType(TileType::FloorTile);
            }
            grid[i][j]->notify();
		}
	}
    for (int j = 0; j < C_NUM; j++) {
        room[j]->reset();
    }
}

void Floor::nextFloor() {
    ++level;
    if (level == 6) {
        gg = true;
    } else {
        clearFloor();
        userPtr->clearBuff();
        if(inventByFile) createByFile(userPtr->getRace());
        else createGame(userPtr->getRace());
    }
}

void Floor::reset() {
	clearFloor();
}

bool Floor::gameOver() {
    return gg;
}

ostream &operator<<(ostream &out, const Floor &f) {
    out << *(f.td) << endl;
    out << "Race: " << f.userPtr->getRace() << " ";
    out << "Gold: " << f.userPtr->getGold();
    for(int i = 0; i < 50; ++i) {
        out << ' ';
    }
    out << "Floor " << f.level << endl;
    out << "HP: " << f.userPtr->getHp() << endl;
    out << "Atk: " << f.userPtr->getAtt() << endl;
    out << "Def: " << f.userPtr->getDef() << endl;
    out << "Action: " << f.movement << endl;
    return out;
}
