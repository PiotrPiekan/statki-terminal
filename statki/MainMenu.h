#pragma once
#include <string>

using namespace std;

class MainMenu
{
    int state;
    int choice;

    void MainSelect();
    void RandomSelect();
    void QuitSelect();
    void PrintLogo();

public:
    MainMenu();
    ~MainMenu();
    int Select();
    void QuitMessage();
    void WarningMessage(const string& msg);
};
