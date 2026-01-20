#pragma once
#include "Board.h"
#include "Ship.h"
#include <deque>
#include <map>

using namespace std;

class Player
{
protected:
    Board* board;
    deque<Ship*> ships;

    void FillShipsFromMap(map<int, int>& shipList);
    bool CheckShipCollisions(const Ship& ship1);
    void ActivateAllShips();
    void DeactivateAllShips();
    void SetShipsWithGuides();

public:
    Player(const int& _boardX, const int& _boardY, const bool& _hideShips);
    ~Player();

    void DrawBoard();
    void ClearBoard();
    void SavePlayer(ofstream& f);
    void LoadPlayerFromFile(ifstream& f);
    void ResetShipsVisuals();
    void SetShips();
    void ListInactiveShips();
    void ListAliveShips();
    bool AreAllShipsSunk();
    bool HasAlreadyBeenHit(const int& xCoord, const int& yCoord);
    int ShipsGetHit(const int& xCoord, const int& yCoord);
    void PositionShipsRandomly(map<int, int> shipList);
};
