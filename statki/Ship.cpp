#include "Ship.h"

Ship::Ship(
    const int& _x,
    const int& _y,
    const int& _length,
    const bool& _isHorizontal,
    Board* _pBoard
)
{
    x = _x;
    y = _y;
    length = _length;
    health = length;
    isHorizontal = _isHorizontal;
    isActive = false;
    pieces = new char[length];
    pBoard = _pBoard;
}

Ship::~Ship()
{
    delete[] pieces;
}

void Ship::SaveShip(ofstream& f)
{
    f << x << ' ' << y << ' ' << length << ' ' << health << ' ';
    f << (int)isHorizontal << ' ';
    for (int i = 0; i < length; i++) {
        f << pieces[i];
    }
    f << endl;
}

void Ship::LoadShip(ifstream& f)
{
    f >> x >> y >> length >> health >> isHorizontal;
    for (int i = 0; i < length; i++) {
        f >> pieces[i];
    }
    isActive = true;
}

void Ship::MoveX(const int& move)
{
    if (x + move < 0) {
        return;
    }
    if (isHorizontal) {
        if (x + move + length > pBoard->x) {
            return;
        }
    } else {
        if (x + move >= pBoard->x) {
            return;
        }
    }
    x += move;
}

void Ship::MoveY(const int& move)
{
    if (y + move < 0) {
        return;
    }
    if (isHorizontal) {
        if (y + move >= pBoard->y) {
            return;
        }
    } else {
        if (y + move + length > pBoard->y) {
            return;
        }
    }
    y += move;
}

void Ship::Flip()
{
    x = y = 0;
    isHorizontal = !isHorizontal;
}

void Ship::PositionRandomly()
{
    isHorizontal = (bool)(rand() % 2);
    if (isHorizontal) {
        x = rand() % (pBoard->x - length + 1);
        y = rand() % pBoard->y;
    } else {
        x = rand() % pBoard->x;
        y = rand() % (pBoard->y - length + 1);
    }
}

bool Ship::IsAlive()
{
    return health > 0;
}

int Ship::CheckIfHit(const int& xCoord, const int& yCoord)
{
    bool hit = false;
    if ((isHorizontal && yCoord == y && xCoord >= x && xCoord < x + length) ||
        (!isHorizontal && xCoord == x && yCoord >= y && yCoord < y + length)) {
        hit = true;
        GetHit(xCoord, yCoord);
        SetShip();
    }
    if (hit) {
        if (!IsAlive()) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void Ship::GetHit(const int& xCoord, const int& yCoord)
{
    if (--health == 0) {
        GetSunk();
    } else if (isHorizontal) {
        pieces[xCoord - x] = '*';
    } else {
        pieces[yCoord - y] = '*';
    }
}

void Ship::GetSunk()
{
    for (int i = 0; i < length; i++) {
        pieces[i] = 'X';
    }
}

bool Ship::CheckShipCollision(const Ship& sh)
{
    int w1, h1, w2, h2;
    if (isHorizontal) {
        w1 = length; h1 = 1;
    } else {
        w1 = 1; h1 = length;
    }
    if (sh.isHorizontal) {
        w2 = sh.length; h2 = 1;
    } else {
        w2 = 1; h2 = sh.length;
    }
    if (x + w1 - sh.x < 0 || x - sh.x - w2 > 0 || y + h1 - sh.y < 0 || y - sh.y - h2 > 0) {
        return false;
    }
    return true;
}

void Ship::ResetVisuals()
{
    if (pBoard->hideShips) {
        for (int i = 0; i < length; i++) {
            pieces[i] = '~';
        }
    } else {
        for (int i = 0; i < length; i++) {
            pieces[i] = '#';
        }
    }
}

void Ship::SetCollisionVisuals()
{
    if (isHorizontal) {
        for (int i = 0; i < length; i++) {
            if (pBoard->tiles[y][x + i] == '~') {
                pieces[i] = '#';
            } else {
                pieces[i] = '!';
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (pBoard->tiles[y + i][x] == '~') {
                pieces[i] = '#';
            } else {
                pieces[i] = '!';
            }
        }
    }
}

void Ship::SetShipWithGuides()
{
    if (isHorizontal) {
        for (int i = y - 1; i <= y + 1; i++) {
            if (i < 0 || i > pBoard->y) continue;
            for (int j = x - 1; j <= x + length; j++) {
                if (j < 0 || j > pBoard->x) continue;
                pBoard->tiles[i][j] = '.';
            }
        }
    } else {
        for (int i = y - 1; i <= y + length; i++) {
            if (i < 0 || i > pBoard->y) continue;
            for (int j = x - 1; j <= x + 1; j++) {
                if (j < 0 || j > pBoard->x) continue;
                pBoard->tiles[i][j] = '.';
            }
        }
    }
    SetShip();
}

void Ship::SetShip()
{
    if (isHorizontal) {
        for (int i = 0; i < length; i++) {
            pBoard->tiles[y][x + i] = pieces[i];
        }
    } else {
        for (int i = 0; i < length; i++) {
            pBoard->tiles[y + i][x] = pieces[i];
        }
    }
}
