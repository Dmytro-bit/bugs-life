//
// Created by dmytro on 26/03/25.
//

#include "Crawler.h"

#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>


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
}

bool Crawler::isWayBlocked() { return false; }

int Crawler::getId() const { return id; }

Position Crawler::getPosition() const { return position; }

Direction Crawler::getDirection() const { return direction; }

int Crawler::getSize() const { return size; }

bool Crawler::isAlive() const { return alive; }
string Crawler::getBugType() {
    return "Crawler";
}

std::list<Position> Crawler::getPath() { return path; }

void Crawler::setId(const int id) {
    this->id = id;
}

string Crawler::directionToString() const {
    switch (this->getDirection()) {
            case North:
                return "North";
            case East:
                return "East";
            case South:
                return "South";
            case West:
                return "West";
            default:
                return "Direction undefined";
        }
}

void Crawler::displayBug() const {
    ostringstream positionStream;
    positionStream << "(" << getPosition().x << "," << getPosition().y << ")";
    cout << left
         << setw(5)  << getId()
         << setw(10) << getBugType()
         << setw(15) << positionStream.str()
         << setw(6)  << getSize()
         << setw(12) << directionToString()
         << setw(8)  << (isAlive() ? "Alive" : "Dead")
         << endl;
}


void Crawler::setPosition(const Position position) {
    this->position = position;
}

void Crawler::setDirection(const Direction direction) {
    this->direction = direction;
}

void Crawler::setSize(const int size) {
    this->size = size;
}

void Crawler::setAlive(const bool alive) {
    this->alive = alive;
}

