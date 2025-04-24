//
// Created by vladikslon on 4/24/25.
//

#ifndef SUPERBUG_H
#define SUPERBUG_H
#include "Bug.h"


class Superbug : public Bug {
    public:
    Superbug() = default;

    Superbug(int id, Position position, Direction direction, int size);

    void move() override;

    std::string getBugType() const override ;

    void displayBug() override;

    void manualMove(Direction d);

};



#endif //SUPERBUG_H
