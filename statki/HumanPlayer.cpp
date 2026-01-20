#include "HumanPlayer.h"
#include <iostream>
#include <conio.h>

HumanPlayer::HumanPlayer(const int& _boardX, const int& _boardY)
    : Player(_boardX, _boardY, false)
{
}

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::PositionShipsManually(map<int, int> shipList)
{
    FillShipsFromMap(shipList);

    bool keepAsking, done = false;
    string response = "";
    deque<Ship*>::iterator currentShip = ships.begin();
    while (!done) {
        while (currentShip != ships.end()) {
            ClearBoard();
            SetShipsWithGuides();
            (*currentShip)->SetCollisionVisuals();
            (*currentShip)->SetShip();

            system("cls");
            cout << "Rozstaw swoje statki:" << endl << endl;
            DrawBoard();
            cout << endl;
            cout << "WASD - poruszaj statkiem" << endl;
            cout << "Spacja - ustaw statek" << endl;
            cout << "E - obróæ statek" << endl;
            cout << "Q - cofnij" << endl;
            cout << endl;
            cout << "Pozosta³e statki:" << endl;
            ListInactiveShips();
            cout << response;
            response = "";
            do {
                keepAsking = false;
                switch (_getch()) {
                    case 'w':
                    case 'W':
                        (*currentShip)->MoveY(-1);
                        break;
                    case 's':
                    case 'S':
                        (*currentShip)->MoveY(1);
                        break;
                    case 'a':
                    case 'A':
                        (*currentShip)->MoveX(-1);
                        break;
                    case 'd':
                    case 'D':
                        (*currentShip)->MoveX(1);
                        break;
                    case 'e':
                    case 'E':
                        (*currentShip)->Flip();
                        break;
                    case 'q':
                    case 'Q':
                        if (currentShip != ships.begin()) {
                            currentShip--;
                            (*currentShip)->isActive = false;
                        }
                        break;
                    case ' ':
                        if (!CheckShipCollisions(**currentShip)) {
                            (*currentShip)->isActive = true;
                            currentShip++;
                        } else {
                            response = "Statki nie mog¹ siê stykaæ!\n";
                        }
                        break;
                    default:
                        keepAsking = true;
                }
            } while (keepAsking == true);
        }
        ClearBoard();
        SetShips();

        system("cls");
        cout << "Twój uk³ad statków:" << endl << endl;
        DrawBoard();
        cout << endl;
        cout << "Spacja - rozpocznij grê" << endl;
        cout << "Q - cofnij" << endl;
        do {
            keepAsking = false;
            switch (_getch()) {
                case 'q':
                case 'Q':
                    if (currentShip != ships.begin()) {
                        currentShip--;
                        (*currentShip)->isActive = false;
                    }
                    break;
                case ' ':
                    done = true;
                    break;
                default:
                    keepAsking = true;
            }
        } while (keepAsking == true);
    }
}

void HumanPlayer::GetAimedByEnemy(int& xCoords, int& yCoords)
{
    while (true) {
        xCoords = rand() % 10;
        yCoords = rand() % 10;
        if (!HasAlreadyBeenHit(xCoords, yCoords)) { return; }
    }
}
