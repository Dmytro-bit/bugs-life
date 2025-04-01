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
    int size_x = 10;
    int size_y = 10;

public:
    Board();

    Board(const unordered_map<int, vector<Crawler *> > &cells, const vector<Crawler *> &bugs);


    [[nodiscard]] vector<Crawler> getBugs() const;


    void setBugs(vector<Crawler *> bugs);

    void setCells(const unordered_map<int, vector<Crawler *> >);

    void getCells();


    void displayBugs() const;

    void findBugById(const int &id) const;

    void tap();
    void displayHistory() const;
};


#endif //BOARD_H
