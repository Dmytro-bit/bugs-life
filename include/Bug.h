//
// Created by dmytro on 15/04/25.
//

#ifndef BUG_H
#define BUG_H
#include "utils/Direction.h"
#include "utils/Position.h"
#include <list>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>

class Bug {
protected:
    int id{};
    Position position{};
    Direction direction{};
    int size{};
    bool alive = true;
    std::list<Position> path;
    int eaten_by = -1;

public:
    virtual void move() = 0;

    [[nodiscard]] bool isWayBlocked() const;

    virtual ~Bug() = default;

    virtual std::string getBugType() =0;

    virtual void displayBug() =0;

    [[nodiscard]] Direction getDirection() const;


    [[nodiscard]] int getId() const { return id; }

    [[nodiscard]] Position getPosition() const { return position; }

    [[nodiscard]] std::list<Position> getPath() const;

    [[nodiscard]] int getSize() const { return size; }

    [[nodiscard]] bool isAlive() const { return alive; }

    void setId(int id);

    void setPosition(Position position);

    void setDirection(Direction direction);

    void setSize(int size);

    void setAlive(bool alive);

    void setEatenBy(int id);

    [[nodiscard]] int getEatenBy() const { return eaten_by; }

    [[nodiscard]] std::string directionToString() const;

    bool operator>(const Bug &bug) const;

    bool operator<(const Bug &bug) const;

    bool operator==(const Bug &bug) const;
};


#endif //BUG_H
