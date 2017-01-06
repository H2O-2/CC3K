#include "floor.h"
using namespace std;

// These are all valid command for user to enter
const string NO = "no";
const string SO = "so";
const string EA = "ea";
const string WE = "we";
const string NE = "ne";
const string NW = "nw";
const string SE = "se";
const string SW = "sw";
const string U_NO = "u<no>";
const string U_SO = "u<so>";
const string U_EA = "u<ea>";
const string U_WE = "u<we>";
const string U_NE = "u<ne>";
const string U_NW = "u<nw>";
const string U_SE = "u<se>";
const string U_SW = "u<sw>";
const string A_NO = "a<no>";
const string A_SO = "a<so>";
const string A_EA = "a<ea>";
const string A_WE = "a<we>";
const string A_NE = "a<ne>";
const string A_NW = "a<nw>";
const string A_SE = "a<se>";
const string A_SW = "a<sw>";



int main(int argc, char* argv[]) {
    
    cout << endl;
    cout << "Hello, welcome to the world of CC3K! You can type the following commands to play this game:" << endl;
    cout << endl;
    cout << "Directions: no, so, ea, we, ne, nw, se, sw" << endl;
    cout << "Using potions: u<directions>" << endl;
    cout << "Attack enemies: a<directions>" << endl;
    cout << endl;
    
	while(true) {
		// user choose race
		string race;
		while(true) {
            cout << "Please choose a race from: h (Human), e (Elves), d (Dwarf), o (Orc)." << endl;
            cout << "DLC characters: s (Saber), a (Archer), b (Berserker), l (Lancer)." << endl;
			string tempRace;
			cin >> tempRace;
            if(tempRace.size() == 1 && (tempRace[0] == 'h' || tempRace[0] == 'e' || tempRace[0] == 'd' || tempRace[0] == 'o' || tempRace[0] == 'a' || tempRace[0] == 's' || tempRace[0] == 'b' ||
                tempRace[0] == 'l' )) {
                if(tempRace == "h") race = "Human";
                else if(tempRace == "e") race = "Elves";
                else if(tempRace == "d") race = "Dwarf";
                else if(tempRace == "o") race = "Orc";
                else if(tempRace == "a") race = "Archer";
                else if(tempRace == "l") race = "Lancer";
                else if(tempRace == "s") race = "Saber";
                else race = "Berserker";
				break;
			}
			cout << "Invalid input." << endl;
		}

        // initialize floor
        string fileName;
        shared_ptr <Floor> floor;
        if(argc == 1) {
            floor = shared_ptr <Floor> (new Floor());
            floor->init();
            floor->createGame(race);
        }
        else {
            floor = shared_ptr <Floor> (new Floor(argv[1]));
            floor->init();
            floor->createByFile(race);
        }
        cout << *floor;

		// user enter command to play the game
		string command;
		while(true) {
            if(floor->checkDeath() || floor->gameOver()) {
                if (floor->checkDeath()) {
                    int gold = floor->score();
                    cout << "YOU DIED LOL. Your score is " << gold << "."<< endl;
                } else {
                    double gold = floor->score();
                    cout << "Congratulations! You have won the game. Your score is: " << gold << endl;
                    break;
                }
                cout << "Start a new game? r(yes & restart), q(no & quit)" << endl;
                cin >> command;
                if(command == "q") {
                    cout << "Thank you for playing the game. Bye!" << endl;
                    return 0;
                } else if(command == "r") {
                    cout << "Restarting the game..." << endl;
                    floor.reset();
                    break;
                } else {
                    continue;
                }
            }
            
			while(true) {
				cin >> command;
				if(command == NO || command == SO || command == EA || command == WE || command == NE || command == NW || command == SE || command == SW ||
					command == U_NO || command == U_SO || command == U_EA || command == U_WE || command == U_NE || command == U_NW || command == U_SE || command == U_SW ||
					command == A_NO || command == A_SO || command == A_EA || command == A_WE || command == A_NE || command == A_NW || command == A_SE || command == A_SW ||
					command == "q" || command == "r") break;
					cout << "Invalid command, please re-enter a valid command" << endl;
			}
            
			if(command == "q") {
				cout << "Thank you for playing the game. Bye!" << endl;
                return 0;
			}
			else if(command == "r") {
				cout << "Restarting the game..." << endl;
				floor.reset();
				break;
			}
			else if(command == NO || command == SO || command == EA || command == WE || command == NE || command == NW || command == SE || command == SW) {
                cout << "sb" << endl;
				floor->charMove(command);
			}
			else if(command == U_NO || command == U_SO || command == U_EA || command == U_WE || command == U_NE || command == U_NW || command == U_SE || command == U_SW) {
				string dir = command.substr(2, 2);
				floor->charUse(dir);
			}
			else {
				string dir = command.substr(2, 2);
				floor->charAtt(dir);
			}
            cout << *floor;
		}
	}
}

