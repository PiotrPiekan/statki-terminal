#include "Game.h"
#include "helpers.h"
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <map>

Game::Game(
    const int& _boardHeight,
    const int& _boardWidth,
    const string& shipConfig,
    const string& _saveName,
    const bool& random
)
{
    turn = 1;
    boardHeight = _boardHeight;
    boardWidth = _boardWidth;
    nextXCoord = -1;
    nextYCoord = -1;
    messageId = -1;
    saveName = _saveName;
    human = new HumanPlayer(_boardWidth, _boardHeight);
    enemy = new CPUPlayer(_boardWidth, _boardHeight);
    
    map<int, int> shipList = ReadShipConfig(shipConfig);

    for (auto const& it : shipList) {
        if (it.first > boardHeight || it.first > boardWidth) {
            throw "Statki nie mieszcz¹ siê w polu " + to_string(10) + "x" + to_string(10);
        }
    }

    enemy->PositionShipsRandomly(shipList);
    if (random) {
        human->PositionShipsRandomly(shipList);
    } else {
        human->PositionShipsManually(shipList);
    }

    human->ClearBoard();
    enemy->ClearBoard();
    human->ResetShipsVisuals();
    enemy->ResetShipsVisuals();
    human->SetShips();
}

Game::Game(const string& saveName)
{
    ifstream saveFile(saveName);
    if (!saveFile.good()) {
        throw "Nie mo¿na wczytaæ stanu gry.";
    }

    saveFile >> turn >> boardHeight >> boardWidth;
    human = new HumanPlayer(boardWidth, boardHeight);
    human->LoadPlayerFromFile(saveFile);
    enemy = new CPUPlayer(boardWidth, boardHeight);
    enemy->LoadPlayerFromFile(saveFile);
    saveFile.close();

    nextXCoord = -1;
    nextYCoord = -1;
    messageId = -1;
}

Game::Game()
{
    turn = 0;
    nextXCoord = 0;
    nextYCoord = 0;
    boardWidth = 0;
    boardHeight = 0;
    messageId = 0;
    saveName = "";
    human = 0;
    enemy = 0;
}

Game::~Game()
{
    delete human;
    delete enemy;
}

void Game::DrawGame()
{
    system("cls");
    cout << "Tura " << turn << endl << endl;
    cout << string(16, '-') << endl << endl;

    cout << " Przeciwnik:" << endl << endl;
    enemy->DrawBoard();
    cout << " Pozosta³e statki:" << endl;
    enemy->ListAliveShips();
    cout << endl << string(16, '-') << endl << endl;

    cout << " Ty:" << endl << endl;
    human->DrawBoard();
    cout << " Pozosta³e statki:" << endl;
    human->ListAliveShips();
    cout << endl;
}

bool Game::SaveGame()
{
    ofstream saveFile(saveName);
    if (saveFile.good()) {
        saveFile << turn << ' ' << boardHeight << ' ' << boardWidth << endl;
        human->SavePlayer(saveFile);
        enemy->SavePlayer(saveFile);
        return true;
    }
    return false;
}

map<int, int> Game::ReadShipConfig(const string& fname)
{
    ifstream shipCfg(fname);
    if (!shipCfg.good()) {
        throw "Nie znaleziono pliku konfiguracyjnego " + fname;
    }

    map<int, int> shipList;
    string line;
    string shipLengthTest, shipCountTest;
    int shipLength, shipCount;

    while (getline(shipCfg, line)) {
        if (line[0] == '#') {
            continue;
        }

        istringstream l(line);
        l >> shipLengthTest >> shipCountTest;
        if (!isNumber(shipLengthTest) || !isNumber(shipCountTest)) {
            shipCfg.close();
            throw "Plik " + fname + " nie jest we w³aœciwym formacie:\nd³ugoœæ_statku iloœæ_statków";
        }

        shipLength = stoi(shipLengthTest);
        shipCount = stoi(shipCountTest);

        if (shipLength <= 0) {
            shipCfg.close();
            throw "D³ugoœæ statków musi byæ dodatnia";
        }

        shipList.insert({ shipLength, shipCount });
    }
    shipCfg.close();

    if (shipList.empty()) {
        throw "Plik " + fname + " nie zawiera statków";
    }

    return shipList;
}

int Game::GetCommand()
{
    string line;
    getline(cin, line);
    removeSpaces(line);
    if (line == "save") {
        return 2;
    }
    if (line == "quit") {
        return 3;
    }
    if (GetCoords(line)) {
        return 1;
    }
    return 0;
}

bool Game::GetCoords(const string& line)
{
    if (line.empty()) {
        return false;
    }
    int xCoord = (int)(line[0] - 'A');
    if (xCoord < 0 || xCoord >= boardWidth) {
        return false;
    }
    string yCoordStr(line.begin() + 1, line.end());
    if (!isNumber(yCoordStr)) {
        return false;
    }
    int yCoord = stoi(yCoordStr) - 1;
    if (yCoord < 0 || yCoord >= boardHeight) {
        return false;
    }
    nextYCoord = yCoord;
    nextXCoord = xCoord;
    return true;
}

int Game::IsGameOver()
{
    bool humanDead = human->AreAllShipsSunk();
    bool enemyDead = enemy->AreAllShipsSunk();
    if (enemyDead) {
        if (humanDead) {
            return 2;
        }
        return 1;
    }
    if (humanDead) {
        return -1;
    }
    return 0;
}

inline void Game::PrintCoords()
{
    cout << (char)(nextXCoord + 'A') << nextYCoord + 1;
}

bool Game::ShootSequence()
{
    int hitStatus;
    if (enemy->HasAlreadyBeenHit(nextXCoord, nextYCoord)) {
        return false;
    }
    system("cls");
    DrawGame();
    cout << "Strzelasz w ";
    PrintCoords();
    cout << "...";

    hitStatus = enemy->ShipsGetHit(nextXCoord, nextYCoord);
    
    Sleep(1000);
    system("cls");
    DrawGame();
    if (hitStatus == 2) {
        cout << "Trafiony, zatopiony!";
    } else if (hitStatus == 1) {
        cout << "Trafiony!";
    } else {
        cout << "Pud³o!";
    }

    human->GetAimedByEnemy(nextXCoord, nextYCoord);

    Sleep(1000);
    system("cls");
    DrawGame();
    
    if (enemy->AreAllShipsSunk()) {
        cout << "Przeciwnik odda³ jeden ostatni strza³!";
    } else {
        cout << "Przeciwnik strzela w ";
        PrintCoords();
        cout << "...";
    }
    
    hitStatus = human->ShipsGetHit(nextXCoord, nextYCoord);

    Sleep(1000);
    system("cls");
    DrawGame();
    if (hitStatus == 2) {
        cout << "Nasz okrêt pad³!";
    } else if (hitStatus == 1) {
        cout << "Dostaliœmy!";
    } else {
        cout << "Spud³owa³!";
    }

    Sleep(1000);
    return true;
}

void Game::Message()
{
    switch (messageId) {
        case 0:
            cout << "Nieznane polecenie lub wspó³rzêdne poza zasiêgiem" << endl;
            cout << "Poprawny format wspó³rzêdnych: A2" << endl;
            cout << "save - zapis" << endl;
            cout << "quit - wyjœcie" << endl << endl;
            break;
        case 10:
            cout << "Ju¿ strzelano w ";
            PrintCoords();
            cout << endl << endl;
            break;
        case 20:
            cout << "Zapis siê siê nie powiód³." << endl << endl;
            break;
        case 21:
            cout << "Gra zapisana." << endl << endl;
            break;
    }
}

void Game::Play()
{
    int winner, command = -1, advanceTurn = 0;
    while ((winner = IsGameOver()) == 0) {
        system("cls");
        turn += advanceTurn;
        DrawGame();
        Message();

        cout << "Podaj wspó³rzêdne lub komendê: ";
        command = GetCommand();

        advanceTurn = 0;
        switch (command) {
            case 1:
                if (!ShootSequence()) {
                    messageId = 10;
                    break;
                }
                messageId = -1;
                advanceTurn = 1;
                break;
            case 2:
                if (SaveGame()) {
                    messageId = 21;
                } else {
                    messageId = 20;
                }
                break;
            case 3:
                return;
                break;
            default:
                messageId = 0;
                break;
        }
    }
    system("cls");
    DrawGame();
    if (winner == -1) {
        cout << "Zwyciêstwo!" << endl;
    } else if (winner == 1) {
        cout << "Pora¿ka!" << endl;
    } else {
        cout << "Remis!" << endl;
    }
    cout << "Wciœnij dowolny klawisz, by wróciæ do menu";
    int x = _getch();
}
