#include <iostream>
#include "Crawler.h"
#include <fstream>
#include <sstream>

#include "Board.h"
#include "Hopper.h"

using namespace std;

void findBug(const Board &board) {
    int id;
    cout << "Please enter the bug's identification number you want to search: ";
    cin >> id;
    board.findBugById(id);
}

void menu(Board &board) {
    char choice;
    do {
        cout << endl;
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (cause all to move, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs" << endl;
        cout << "7. Run simulation (generates a Tap every tenth of a second)" << endl;
        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case '1': {
                std::vector<Bug *> bugs;
                board.loadBugs();
                break;
            }
            case '2':
                board.displayBugs();
                break;
            case '3':
                findBug(board);
                break;
            case '4':
                board.tap();
                board.fight();
                break;
            case '5':
                board.displayHistory();
                break;
            case '6':
                board.displayCells();
                break;
            case '7':
                board.runSimulation();
                break;
            case '8':
                board.writeHistoryToFile();
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != '8');
}


int main() {
    srand(time(NULL));
    Board board;
    menu(board);
    return 0;
}
