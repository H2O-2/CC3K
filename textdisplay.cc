#include "textdisplay.h"
#include <fstream>
#include <sstream>
using namespace std;


TextDisplay::TextDisplay() {
	ifstream map {"map.txt"};
	string s;
	while(getline(map, s)) {
		vector <char> temprow;
		int len = s.length();
		for(int i = 0; i < len; ++i) {
			char c = s[i];
			temprow.emplace_back(c);
		}
		display.emplace_back(temprow);
	}
}

void TextDisplay::notify(int x, int y, char type) {
	display[y][x] = type;
}

void TextDisplay::setUser(std::shared_ptr<User> user) { PC = user; }


const int col = 79;  // number of columns of tiles
const int row = 25;  // number of rows of tiles

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for(int r = 0; r < row; ++r) {
		for(int c = 0; c < col; ++c) {
			out << td.display[r][c];
		}
		out << "\n";
	}
    return out;
}
