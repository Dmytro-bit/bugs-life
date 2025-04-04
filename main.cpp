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


int main() {
    srand(time(NULL));
    Board board;
    std::vector<Crawler *> bugs;
    loadBugs(bugs);
    board.setBugs(bugs);

    board.runSimulation();
    return 0;
}
