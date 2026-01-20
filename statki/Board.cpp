#include "Board.h"
#include <iomanip>

using namespace std;

Board::Board(const int& _x, const int& _y, const bool& _hideShips)
{
    x = _x;
    y = _y;
    hideShips = _hideShips;
    tiles = new char* [y];
    for (int i = 0; i < y; i++) {
        tiles[i] = new char[x];
    }
}

Board::~Board()
{
    for (int i = 0; i < y; i++) {
        delete[] tiles[i];
    }
    delete[] tiles;
}

void Board::Clear()
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            tiles[i][j] = '~';
        }
    }
}

void Board::Draw()
{
    cout << "  ";
    for (char i = 'A'; i < 'A' + x; i++) {
        cout << i;
    }
    cout << endl;
    for (int i = 0; i < y; i++) {
        cout << setw(2) << i + 1;
        for (int j = 0; j < x; j++) {
            cout << tiles[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Board::Save(ofstream& f)
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            f << tiles[j][i];
        }
        f << endl;
    }
}

void Board::Load(ifstream& f)
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            f >> tiles[j][i];
        }
    }
}
