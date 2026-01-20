#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Board
{
public:
    int x;
    int y;
    bool hideShips;
    char** tiles;

    Board(const int& _x, const int& _y, const bool& _hideShips);
    ~Board();

    void Clear();
    void Draw();
    void Save(ofstream& f);
    void Load(ifstream& f);
};