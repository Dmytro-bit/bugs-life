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
    vector<Crawler *> bugs;
    std::unordered_map<int, vector<Crawler *> > cells;
    const int size_x = 10;
    const int size_y = 10;

public:
    Board();

    Board(const unordered_map<int, vector<Crawler *> > &cells, const vector<Crawler *> &bugs);

    void fight();
    [[nodiscard]] vector<Crawler> getBugs() const;


    void setBugs(vector<Crawler *> bugs);

    void setCells(const unordered_map<int, vector<Crawler *> >);

    // unordered_map<int, vector<Crawler *> >  getCells();


    void displayBugs() const;

    void findBugById(const int &id) const;

    void displayCells();

    void tap();
    void displayHistory() const;
};


#endif //BOARD_H
