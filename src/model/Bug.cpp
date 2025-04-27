//
// Created by dmytro on 15/04/25.
//

#include "Bug.h"

#include <iomanip>

#include "Board.h"
#include <iostream>
#include <sstream>

Direction Bug::getDirection() const { return direction; }

bool Bug::isWayBlocked() const {
    switch (direction) {
        case North:
            if (position.y + 1 <= Board::getBoardSizeY()) {
                return false;
            }
            break;
        case East:
            if (position.x + 1 <= Board::getBoardSizeX()) {
                return false;
            }
            break;
        case South:
            if (position.y - 1 >= 0) {
                return false;
            }
            break;
        case West:
            if (position.x - 1 >= 0) {
                return false;
            }
            break;
    }
    return true;
}

std::list<Position> Bug::getPath() const { return path; }

void Bug::setId(const int id) {
    this->id = id;
}

std::string Bug::directionToString() const {
    switch (direction) {
        case North: return "North";
        case East: return "East";
        case South: return "South";
        case West: return "West";
        default: return "Unknown";
    }
}

bool Bug::operator>(const Bug &bug) const {
    return this->size > bug.size;
}

bool Bug::operator<(const Bug &bug) const {
    return this->size < bug.size;
}

bool Bug::operator==(const Bug &bug) const {
    return this->size == bug.size;
}


void Bug::setPosition(const Position position) {
    this->position = position;
}

void Bug::setDirection(const Direction direction) {
    this->direction = direction;
}

void Bug::setSize(const int size) {
    this->size = size;
}

void Bug::setAlive(const bool alive) {
    this->alive = alive;
}

void Bug::setEatenBy(int id) {
    this->eaten_by = id;
}
