//
// Created by vladikslon on 3/30/25.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <unordered_map>

#include "Crawler.h"
using namespace std;

class Board {
private:
    vector<Bug *> bugs;
    int deadBugs = 0;
    std::unordered_map<int, vector<Bug *> > cells;
    static constexpr int size_x = 10;
    static constexpr int size_y = 10;

public:
    Board();
    ~Board();

    Board(const unordered_map<int, vector<Bug *> > &cells, const vector<Bug *> &bugs);

    void fight();

    [[nodiscard]] vector<const Bug*> getBugs() const;

    void setBugs(vector<Bug *> bugs);

    void displayBugs() const;

    void findBugById(const int &id) const;

    void displayCells();

    void tap();

    void displayHistory() const;

    void runSimulation();

    void writeHistoryToFile() const;

    void loadBugs();

    void moveSuper(Direction dir);

    static int getBoardSizeX();
    static int getBoardSizeY();
};


#endif //BOARD_H
