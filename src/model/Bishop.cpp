//
// Created by vladikslon on 4/23/25.
//

#include "Bishop.h"

#include "Board.h"
using namespace std;


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
    for (int i = 0; i <= 4; i++) {
        newDir = (rand() % 4) + 1;
    direction = static_cast<Direction>(newDir);
    }

    if (this->isWayBlocked()) {
        return;
    }
    switch (this->getDirection()) {
        case North:
            this->setPosition({
                min(this->getPosition().x + 1, Board::getBoardSizeX()),
                min(this->getPosition().y + 1, Board::getBoardSizeY())
            });
            break;
        case East:
            this->setPosition({
                min(this->getPosition().x + 1, Board::getBoardSizeX()),
                max(this->getPosition().y - 1, 0)
            });
            break;
        case South:
            this->setPosition({
                max(this->getPosition().x - 1, 0),
                max(this->getPosition().y - 1, 0)
            });

            break;
        case West:
            this->setPosition({
                max(this->getPosition().x - 1, 0),
                min(this->getPosition().y + 1, Board::getBoardSizeY())
            });
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

bool Bishop::isWayBlocked() const {
    switch (direction) {
        case North:
            if (position.y + 1 <= Board::getBoardSizeY() && position.x + 1 <= Board::getBoardSizeX()) {
                return false;
            }
        break;
        case East:
            if (position.x + 1 <= Board::getBoardSizeX() && position.y -1 >= 0) {
                return false;
            }
        break;
        case South:
            if (position.y - 1 >= 0 && position.x >= 0) {
                return false;
            }
        break;
        case West:
            if (position.x - 1 >= 0 && position.y <= Board::getBoardSizeY()) {
                return false;
            }
        break;
    }
    return true;
}