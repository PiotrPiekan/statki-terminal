#pragma once
#include "Player.h"
#include <map>
class HumanPlayer :
    public Player
{
public:
    HumanPlayer(const int& _boardX, const int& _boardY);
    ~HumanPlayer();

    void PositionShipsManually(map<int, int> shipList);
    void GetAimedByEnemy(int& xCoords, int& yCoords);
};

