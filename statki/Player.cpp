#include "Player.h"

Player::Player(const int& _boardX, const int& _boardY, const bool& _hideShips)
{
    board = new Board(_boardX, _boardY, _hideShips);
}

Player::~Player()
{
    delete board;
    while (!ships.empty()) {
        delete ships.front();
        ships.pop_front();
    }
}

void Player::DrawBoard()
{
    board->Draw();
}

void Player::ClearBoard()
{
    board->Clear();
}

void Player::SavePlayer(ofstream& f)
{
    board->Save(f);
    f << ships.size() << endl;
    for (auto& ship : ships) {
        ship->SaveShip(f);
    }
}

void Player::LoadPlayerFromFile(ifstream& f)
{
    board->Load(f);
    int i;
    Ship* newShip = 0;
    for (f >> i; i > 0; i--) {
        newShip = new Ship(0, 0, 0, false, board);
        newShip->LoadShip(f);
        ships.push_front(newShip);
    }
}

void Player::FillShipsFromMap(map<int, int>& shipList)
{
    for (auto& it : shipList) {
        while (it.second--) {
            ships.push_front(new Ship(0, 0, it.first, true, board));
        }
    }
}

void Player::ListInactiveShips()
{
    int prevLen = ships.front()->length;
    for (const auto& it : ships) {
        if (!it->isActive) {
            if (it->length != prevLen) {
                prevLen = it->length;
                cout << endl;
            }
            cout << string(it->length, '#') << " ";
        }
    }
    cout << endl;
}

void Player::ListAliveShips()
{
    int prevLen = ships.front()->length;
    for (auto& it : ships) {
        if (it->IsAlive()) {
            if (it->length != prevLen) {
                prevLen = it->length;
                cout << endl;
            }
            cout << string(it->length, '#') << " ";
        }
    }
    cout << endl;
}

bool Player::AreAllShipsSunk()
{
    for (auto& ship : ships) {
        if (ship->isActive) {
            return false;
        }
    }
    return true;
}

bool Player::HasAlreadyBeenHit(const int& xCoord, const int& yCoord)
{
    if (board->tiles[yCoord][xCoord] == 'o' ||
        board->tiles[yCoord][xCoord] == '*' || 
        board->tiles[yCoord][xCoord] == 'X') {
        return true;
    }
    return false;
}

int Player::ShipsGetHit(const int& xCoord, const int& yCoord)
{
    int ret;
    for (auto& ship : ships) {
        if (ship->IsAlive() &&
            (ret = ship->CheckIfHit(xCoord, yCoord)) > 0) {
            return ret;
        }
    }
    board->tiles[yCoord][xCoord] = 'o';
    return 0;
}

bool Player::CheckShipCollisions(const Ship& ship1)
{
    for (auto& ship2 : ships) {
        if (ship2->isActive) {
            if (ship2->CheckShipCollision(ship1)) {
                return true;
            }
        }
    }
    return false;
}

void Player::ActivateAllShips()
{
    for (auto& ship : ships) {
        ship->isActive = true;
    }
}

void Player::DeactivateAllShips()
{
    for (auto& ship : ships) {
        ship->isActive = false;
    }
}

void Player::ResetShipsVisuals()
{
    for (auto& ship : ships) {
        ship->ResetVisuals();
    }
}

void Player::SetShipsWithGuides()
{
    for (auto& ship : ships) {
        if (ship->isActive) {
            ship->SetShipWithGuides();
        }
    }
}

void Player::SetShips()
{
    for (auto& ship : ships) {
        if (ship->isActive) {
            ship->SetShip();
        }
    }
}

void Player::PositionShipsRandomly(map<int, int> shipList)
{
    FillShipsFromMap(shipList);
    int tries = 10, smallTries;
    deque<Ship*>::iterator currentShip;
    while (tries > 0) {
        currentShip = ships.begin();
        for (smallTries = 1000; currentShip != ships.end() && smallTries > 0; smallTries--) {
            (*currentShip)->PositionRandomly();
            if (!CheckShipCollisions(**currentShip)) {
                (*currentShip)->isActive = true;
                currentShip++;
            }
        }
        if (currentShip != ships.end()) break;
        tries--;
    }
    if (tries == 0) {
        throw "Losowa generacja statków zajê³a zbyt d³ugo.";
    }
}