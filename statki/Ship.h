#pragma once
#include "Board.h"

using namespace std;

class Ship
{
    char* pieces;
    Board* pBoard;

public:
    int x;
    int y;
    int length;
    int health;
    bool isHorizontal;
    bool isActive;

    Ship(
        const int& _x,
        const int& _y,
        const int& _length,
        const bool& _isHorizontal,
        Board* _pBoard
    );
    ~Ship();

    void SaveShip(ofstream& f);
    void LoadShip(ifstream& f);
    void MoveX(const int& move);
    void MoveY(const int& move);
    void Flip();
    void PositionRandomly();
    bool IsAlive();
    int CheckIfHit(const int& xCoord, const int& yCoord);
    void GetHit(const int& xCoord, const int& yCoord);
    void GetSunk();
    bool CheckShipCollision(const Ship& sh);
    void ResetVisuals();
    void SetCollisionVisuals();
    void SetShip();
    void SetShipWithGuides();
};

