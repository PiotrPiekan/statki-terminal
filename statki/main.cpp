#include "Game.h"
#include <locale>
#include "MainMenu.h"

int main()
{
    srand((unsigned)time(0));
    setlocale(LC_ALL, "polish");

    Game* myGame = 0;
    MainMenu mainMenu;
    int option;
    while ((option = mainMenu.Select()) != 0) {
        try {
            switch (option) {
                case 11:
                    myGame = new Game(10, 10, "../shipconfig.txt", "../save.txt", true);
                    break;
                case 12:
                    myGame = new Game(10, 10, "../shipconfig.txt", "../save.txt", false);
                    break;
                case 2:
                    myGame = new Game("../save.txt");
                default:
                    throw "Coœ nie tak z menu.";
            }
            myGame->Play();
        } catch (string msg) {
            mainMenu.WarningMessage(msg);
        } catch (...) {
            mainMenu.WarningMessage("Plik zapisu jest w z³ym formacie.");
        }
        delete myGame; // coœ siê psuje jak wczytujê zapis
    }
    mainMenu.QuitMessage();
    return 0;
}