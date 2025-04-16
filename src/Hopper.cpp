//
// Created by dmytro on 15/04/25.
//

#include "Hopper.h"

#include "Board.h"

Hopper::Hopper() {
}

Hopper::Hopper(const int id, const Position position, const Direction direction, const int size, const int hopLength) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->hopLength = hopLength;
}


void Hopper::move() {
    if (!alive)
        return;

    while (this->isWayBlocked()) {
        int newDir = (rand() % 4) + 1;
        direction = static_cast<Direction>(newDir);
    }

    switch (this->getDirection()) {
        case North:
            this->setPosition({this->getPosition().x, min(this->getPosition().y + hopLength, Board::getBoardSizeY())});
            break;
        case East:
            this->setPosition({min(this->getPosition().x + hopLength, Board::getBoardSizeX()), this->getPosition().y});
            break;
        case South:
            this->setPosition({this->getPosition().x, max(this->getPosition().y - hopLength, 0)});
            break;
        case West:
            this->setPosition({max(this->getPosition().x - hopLength, 0), this->getPosition().y});
            break;
    }

    path.push_back(position);
}


string Hopper::getBugType() {
    return "Hopper";
}


void Hopper::displayBug() {
    ostringstream positionStream;
    positionStream << "(" << getPosition().x << "," << getPosition().y << ")";
    cout << left
            << setw(5) << getId()
            << setw(10) << getBugType()
            << setw(15) << positionStream.str()
            << setw(6) << getSize()
            << setw(12) << directionToString()
            << setw(8) << (isAlive() ? "Alive" : "Dead")
            << setw(8) << getEatenBy() << endl;
}
