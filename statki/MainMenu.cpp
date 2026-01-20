#include "MainMenu.h"
#include <iostream>
#include <conio.h>

using namespace std;

void MainMenu::MainSelect()
{
    cout << " 1: Rozpocznij grê" << endl;
    cout << " 2: Wczytaj grê" << endl;
    cout << " 0: WyjdŸ" << endl;

    bool keepAsking;
    do {
        keepAsking = false;
        switch (_getch()) {
            case '1':
                state = 1;
                break;
            case '2':
                choice = 2;
                break;
            case '0':
                state = 2;
                break;
            default:
                keepAsking = true;
        }
    } while (keepAsking);
}

void MainMenu::RandomSelect()
{
    cout << ">>> Rozpocznij grê <<<" << endl;
    cout << "1: Rozstaw statki losowo" << endl;
    cout << "2: Sam rozstawiam statki" << endl;
    cout << "0: Wróæ" << endl;

    bool keepAsking;
    do {
        keepAsking = false;
        switch (_getch()) {
            case '1':
                choice = 11;
                break;
            case '2':
                choice = 12;
                break;
            case '0':
                choice = -1;
                break;
            default:
                keepAsking = true;
        }
    } while (keepAsking);
    state = 0;
}

void MainMenu::QuitSelect()
{
    cout << ">>> WyjdŸ <<<" << endl;
    cout << "Na pewno? (t/n)" << endl;

    bool keepAsking;
    do {
        keepAsking = false;
        switch (_getch()) {
            case 't':
            case 'T':
                choice = 0;
                break;
            case 'n':
            case 'N':
                choice = -1;
                break;
            default:
                keepAsking = true;
        }
    } while (keepAsking);
    state = 0;
}

void MainMenu::PrintLogo()
{
    cout << endl;
    cout << "  ###  #####  ###  ##### #  ## ### " << endl;
    cout << " #   #   #   #   #   #   # #    #  " << endl;
    cout << "  #      #   #   #   #   ##     #  " << endl;
    cout << "   ##    #   #####   #   # #    #  " << endl;
    cout << " #   #   #   #   #   #   #  #   #  " << endl;
    cout << "  ###    #   #   #   #   #   # ### " << endl << endl;
}

MainMenu::MainMenu()
{
    state = 0;
    choice = -1;
}

MainMenu::~MainMenu()
{
}

int MainMenu::Select()
{
    state = 0;
    choice = -1;
    while (choice == -1) {
        system("cls");
        PrintLogo();
        switch (state) {
            case 0:
                MainSelect();
                break;
            case 1:
                RandomSelect();
                break;
            case 2:
                QuitSelect();
                break;
        }
    }
    return choice;
}

void MainMenu::QuitMessage()
{
    system("cls");
    PrintLogo();
    cout << "Zamykanie...";
}

void MainMenu::WarningMessage(const string& msg)
{
    system("cls");
    PrintLogo();
    cout << msg << endl;
    cout << "Wciœnij dowolny klawisz, by wróciæ do menu." << endl;
    int a = _getch();
}