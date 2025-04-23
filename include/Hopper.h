//
// Created by dmytro on 15/04/25.
//

#ifndef HOPPER_H
#define HOPPER_H
#include "Bug.h"
#include <algorithm>

using namespace std;

class Hopper : public Bug {
private:
    int hopLength = 2;

public:
    Hopper();

    Hopper(int id, Position position, Direction direction, int size, int hopLength);

    void move() override;

    string getBugType() const override;

    void displayBug() override;
};


#endif //HOPPER_H
