#include "Board.h"

#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include "Crawler.h"
//
// Created by vladikslon on 3/30/25.
//
Board::Board() = default;

Board::Board(const vector<Crawler *> &bugs) {
    this->bugs = bugs;
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
         << setw(5)  << "ID"
         << setw(10) << "Bug"
         << setw(15) << "Position"
         << setw(6)  << "Size"
         << setw(12) << "Direction"
         << setw(8)  << "Status"
         << endl;
    for (const Crawler *bug: bugs) {
        ostringstream positionStream;
        positionStream << "(" << bug->getPosition().x << "," << bug->getPosition().y << ")";
        cout << left
             << setw(5)  << bug->getId()
             << setw(10) << bug->getBugType()
             << setw(15) << positionStream.str()
             << setw(6)  << bug->getSize()
             << setw(12) << bug->directionToString()
             << setw(8)  << (bug->isAlive() ? "Alive" : "Dead")
             << endl;
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

void Board::setBugs(vector<Crawler *> bugs) {
    this->bugs = std::move(bugs);
}
