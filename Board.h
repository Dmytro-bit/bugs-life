//
// Created by vladikslon on 3/30/25.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>

#include "Crawler.h"
using namespace std;
class Board {


public:
    [[nodiscard]] vector<Crawler> getBugs() const;

    void setBugs(vector<Crawler *> bugs);
    Board();

    Board(const vector<Crawler *> &bugs);

    void displayBugs() const;

    void findBugById(const int &id) const;

private:
    vector<Crawler*> bugs;

};


#endif //BOARD_H
