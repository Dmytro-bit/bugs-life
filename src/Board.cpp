#include "Board.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>

#include "Crawler.h"
//
// Created by vladikslon on 3/30/25.
//

Board::Board() = default;

Board::Board(const unordered_map<int, vector<Crawler *> > &cells,
             const vector<Crawler *> &bugs): cells(cells), bugs(bugs) {
}

int Board::getBoardSizeX() {
    return size_x;
}

int Board::getBoardSizeY() {
    return size_y;
}

void Board::setBugs(vector<Crawler *> bugs) {
    this->bugs = std::move(bugs);
}


vector<Crawler> Board::getBugs() const {
    vector<Crawler> bugsCopies;
    bugsCopies.reserve(bugs.size());
    for (const auto bug: bugs) {
        bugsCopies.push_back(*bug);
    }
    return bugsCopies;
}


void Board::displayBugs() const {
    cout << "Bugs list:" << endl;
    cout << left
            << setw(5) << "ID"
            << setw(10) << "Bug"
            << setw(15) << "Position"
            << setw(6) << "Size"
            << setw(12) << "Direction"
            << setw(8) << "Status"
            << setw(8) << "Eaten by"
            << endl;
    for (const Crawler *bug: bugs) {
        ostringstream positionStream;
        positionStream << "(" << bug->getPosition().x << "," << bug->getPosition().y << ")";
        cout << left
                << setw(5) << bug->getId()
                << setw(10) << bug->getBugType()
                << setw(15) << positionStream.str()
                << setw(6) << bug->getSize()
                << setw(12) << bug->directionToString()
                << setw(8) << (bug->isAlive() ? "Alive" : "Dead")
                << setw(10) << bug->getEatenBy() << endl;
    }
}

void Board::findBugById(const int &id) const {
    vector<Crawler> bugs = this->getBugs();
    bool bugFound = false;
    for (const Crawler &bug: bugs) {
        if (bug.getId() == id) {
            bugFound = true;
            bug.displayBug();
            break;
        }
    }
    if (!bugFound) {
        cout << "Bug not found" << endl;
    }
}

void Board::displayCells() {
    vector<Crawler *> bugsInCell;
    int posY, posX;
    cout << "Cells:" << endl;
    for (int i = 0; i <= size_x; i++) {
        for (int j = 0; j <= size_y; j++) {
            int index = j * size_x + i;

            cout << "(" << i << "," << j << ") ";

            if (cells.contains(index)) {
                vector<Crawler *> bugs = cells.at(index);
                for (const Crawler *bugPointer: bugs) {
                    if (bugPointer->isAlive()) {
                        cout << "| ";
                        cout << bugPointer->getId() << " ";
                        cout << bugPointer->getBugType() << ";  ";
                    }
                }
            } else {
                cout << "! Empty";
            }

            cout << endl;
        }
    }
}

void Board::tap() {
    cells.clear();

    for (Crawler *bug: bugs) {
        if (bug->isAlive()) {
            bug->move();
            Position pos = bug->getPosition();
            int cellKey = pos.y * size_x + pos.x;

            cells[cellKey].push_back(bug);
        }
    }
}

void Board::fight() {
    for (const auto &[cell, values]: this->cells) {
        if (values.size() <= 1) continue;

        Crawler *pBigBug = nullptr;
        vector<Crawler *> sameSizeBugs;
        int total_bugs_size = 0;
        int dead_bugs = -1;

        for (Crawler *bugPointer: values) {
            if (pBigBug == nullptr || bugPointer->getSize() > pBigBug->getSize()) {
                sameSizeBugs.clear();
                pBigBug = bugPointer;
            } else if (bugPointer->getSize() == pBigBug->getSize()) {
                sameSizeBugs.push_back(bugPointer);
            }
            total_bugs_size += bugPointer->getSize();
            ++dead_bugs;
        }


        if (!sameSizeBugs.empty()) {
            sameSizeBugs.push_back(pBigBug);
            pBigBug = sameSizeBugs[rand() % sameSizeBugs.size()];
        }

        for (Crawler *bugPointer: values) {
            if (bugPointer != pBigBug) {
                bugPointer->setAlive(false);
                bugPointer->setEatenBy(pBigBug->getId());
            }
        }
        deadBugs += dead_bugs;
        cells[cell].clear();
        pBigBug->setSize(total_bugs_size);
        cells[cell].push_back(pBigBug);
    }
}


void Board::displayHistory() const {
    for (const Crawler *bug: bugs) {
        cout << bug->getId() << " " << Crawler::getBugType() << " Path: ";

        const list<Position> &history = bug->getPath();

        for (const Position &pos: history) {
            cout << "(" << pos.x << "," << pos.y << ")";
        }

        cout << " Eaten by: ";
        if (bug->isAlive()) {
            cout << "None";
        } else {
            cout << bug->getEatenBy();
        }
        cout << endl;
    }
}

void Board::runSimulation() {
    while (deadBugs != bugs.size() - 1) {
        tap();
        fight();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    displayBugs();
}

void Board::writeHistoryToFile() const {
    time_t now = std::time(nullptr);
    tm *localTime = std::localtime(&now);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H:%M:%S", localTime);


    string filename = "bugs_life_history_" + string(timestamp) + ".out";


    ofstream file(filename);
    for (const Crawler *bug: bugs) {
        file << bug->getId() << " " << Crawler::getBugType() << " Path: ";
        const list<Position> &history = bug->getPath();
        for (const Position &pos: history) {
            file << "(" << pos.x << "," << pos.y << ")";
        }
        if (bug->isAlive()) {
            file << " Eaten by: None";
        } else {
            file << " Eaten by: " << bug->getEatenBy();
        }
        file << endl;
    }
    file.close();
    cout << "History saved to: " << filename << endl;
}
