#pragma once
#include "HumanPlayer.h"
#include "CPUPlayer.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;

class Game
{
    int turn;
    int nextXCoord;
    int nextYCoord;
    int boardWidth;
    int boardHeight;
    int messageId;
    string saveName;
    HumanPlayer* human;
    CPUPlayer* enemy;

    void DrawGame();
    bool SaveGame();
    map<int, int> ReadShipConfig(const string& fname);
    int GetCommand();
    bool GetCoords(const string& line);
    bool ShootSequence();
    void Message();
    int IsGameOver();
    inline void PrintCoords();

public:
    Game(
        const int& _boardHeight,
        const int& _boardWidth,
        const string& shipConfig,
        const string& _saveName,
        const bool& random
    );
    Game(const string& saveName);
    Game();
    ~Game();

    void Play();
};