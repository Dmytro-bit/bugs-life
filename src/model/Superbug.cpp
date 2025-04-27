//
// Created by vladikslon on 4/24/25.
//

#include "Superbug.h"

#include "Board.h"

using namespace std;

Superbug::Superbug(int id, Position position, Direction direction, int size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = true;
}

void Superbug::manualMove(Direction d) {
    setDirection(d);
    int x = getPosition().x;
    int y = getPosition().y;
    switch (d) {
        case North: if (y > 0) --y;
            break;
        case South: if (y < Board::getBoardSizeY()) ++y;
            break;
        case East: if (x < Board::getBoardSizeX()) ++x;
            break;
        case West: if (x > 0) --x;
            break;
    }
    setPosition({x, y});
    path.push_back(position);
}

void Superbug::move() {
}

std::string Superbug::getBugType() const {
    return "Super";
}

void Superbug::displayBug() {
    std::ostringstream positionStream;
    positionStream << "(" << getPosition().x << "," << getPosition().y << ")";
    std::cout << left
            << setw(5) << getId()
            << setw(10) << getBugType()
            << setw(15) << positionStream.str()
            << setw(6) << getSize()
            << setw(12) << directionToString()
            << setw(8) << (isAlive() ? "Alive" : "Dead")
            << setw(8) << getEatenBy() << endl;
}
