#pragma once
#include "Player.h"
class CPUPlayer :
    public Player
{
public:
    CPUPlayer(const int& _boardX, const int& _boardY);
    ~CPUPlayer();
};