//
// Created by vladikslon on 4/23/25.
//

#ifndef CHAOTIC_H
#define CHAOTIC_H
#include "Bug.h"


class Bishop : public Bug {
    public:
    Bishop() = default;
    ~Bishop() {}
    Bishop(int id, Position position, Direction direction, int size);
    void move() override;

    [[nodiscard]] std::string getBugType() const override;

    void displayBug() override;

    [[nodiscard]] bool isWayBlocked() const;

};



#endif //CHAOTIC_H
