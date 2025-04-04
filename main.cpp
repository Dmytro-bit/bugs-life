#include <iostream>
#include "Crawler.h"
#include <fstream>
#include <sstream>

#include "Board.h"

using namespace std;

void parseLine(const std::string &line, Crawler *bug) {
    std::string temp;
    std::stringstream ss(line);

    getline(ss, temp, ',');
    // const string bugType = temp;
    getline(ss, temp, ',');


    const int id = std::stoi(temp);
    bug->setId(id);
    getline(ss, temp, ',');
    int x = std::stoi(temp);

    getline(ss, temp, ',');
    int y = std::stoi(temp);
    bug->setPosition({x, y});
    getline(ss, temp, ',');
    int direction = std::stoi(temp);

    bug->setDirection(static_cast<Direction>(direction));
    getline(ss, temp, ',');
    const int size = std::stoi(temp);
    bug->setSize(size);
}

void loadBugs(std::vector<Crawler *> &bugs) {
    if (std::ifstream file("../crawler-bugs.txt"); file) {
        std::string line;
        while (std::getline(file, line)) {
            auto *pbug = new Crawler();
            parseLine(line, pbug);
            bugs.push_back(pbug);
        }
    } else {
        std::cout << "File not found" << std::endl;
    }
}

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
                std::vector<Crawler *> bugs;
                loadBugs(bugs);
                board.setBugs(bugs);
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
