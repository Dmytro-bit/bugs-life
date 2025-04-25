//
// Created by dmytro on 26/03/25.
//

#include "Crawler.h"

#include <iomanip>
#include <ios>


Crawler::Crawler() {
}

Crawler::Crawler(int const id, Position const position, Direction const direction, int const size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = true;
}

void Crawler::move() {
    if (!alive)
        return;

    if (this->isWayBlocked()) {
        for (int i = 0; i < this->size; i++) {
            int newDir = (rand() % 4) + 1;
            direction = static_cast<Direction>(newDir);
        }
    }
    if (this->isWayBlocked()) {
        return;
    }
    switch (this->getDirection()) {
        case North:
            this->setPosition({this->getPosition().x, this->getPosition().y + 1});
            break;
        case East:
            this->setPosition({this->getPosition().x + 1, this->getPosition().y});
            break;
        case South:
            this->setPosition({this->getPosition().x, this->getPosition().y - 1});
            break;
        case West:
            this->setPosition({this->getPosition().x - 1, this->getPosition().y});
            break;
    }

    path.push_back(position);
    // while (this->isWayBlocked()) {
    //     int newDir = (rand() % 4) + 1;
    //     direction = static_cast<Direction>(newDir);
    // }
}

string Crawler::getBugType() const {
    return "Crawler";
}

void Crawler::displayBug() {
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
