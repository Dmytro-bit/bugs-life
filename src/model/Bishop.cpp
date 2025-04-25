//
// Created by vladikslon on 4/23/25.
//

#include "Bishop.h"

#include "Board.h"
using  namespace std;



Bishop::Bishop(const int id, const Position position, const Direction direction, const int size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;

}

void Bishop::move() {
    if (!alive)
        return;
    int  newDir;

    if (this->isWayBlocked()) {
        for (int i = 0; i <= 4; i++) {
            newDir = (rand() % 4) + 1;
        direction = static_cast<Direction>(newDir);
        }

    }

    if (this->isWayBlocked()) {
        return;
    }
    switch (this->getDirection()) {
        case North:
            this->setPosition({this->getPosition().x + 1, min(this->getPosition().y + 1, Board::getBoardSizeY())});
            newDir = (rand() % 4) + 1;
            direction = static_cast<Direction>(newDir);
            break;
        case East:
            this->setPosition({min(this->getPosition().x + 1, Board::getBoardSizeX()), this->getPosition().y - 1 });
            newDir = (rand() % 4) + 1;
            direction = static_cast<Direction>(newDir);
            break;
        case South:
            this->setPosition({this->getPosition().x - 1, max(this->getPosition().y - 1, 0)});
            newDir = (rand() % 4) + 1;
            direction = static_cast<Direction>(newDir);
            break;
        case West:
            this->setPosition({max(this->getPosition().x - 1, 0), this->getPosition().y + 1});
            break;
    }

    path.push_back(position);
}


std::string Bishop::getBugType() const {
    return "Bishop";
}


void Bishop::displayBug() {
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
