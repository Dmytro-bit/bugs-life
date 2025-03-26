//
// Created by dmytro on 26/03/25.
//

#include "Crawler.h"


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

std::list<Position> Crawler::getPath() { return path; }

void Crawler::setId(int id) {
    this->id = id;
}

void Crawler::setPosition(Position position) {
    this->position = position;
}

void Crawler::setDirection(Direction direction) {
    this->direction = direction;
}

void Crawler::setSize(int size) {
    this->size = size;
}

void Crawler::setAlive(bool alive) {
    this->alive = alive;
}
