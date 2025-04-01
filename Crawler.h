//
// Created by dmytro on 26/03/25.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>
#include <string>
using namespace std;

struct Position {
    int x;
    int y;
};

enum Direction {
    North = 1,
    East,
    South,
    West
};

class Crawler {
private:
    int id{};
    Position position{};
    Direction direction;
    int size{};
    bool alive = true;
    std::list<Position> path;

public:
    Crawler();

    Crawler(int id, Position position, Direction direction, int size);

    void move();

    bool isWayBlocked();

    static string getBugType();

    [[nodiscard]] int getId() const;

    [[nodiscard]] Position getPosition() const;

    [[nodiscard]] std::list<Position> getPath() const;

    [[nodiscard]] Direction getDirection() const;

    [[nodiscard]] int getSize() const;

    [[nodiscard]] bool isAlive() const;

    void setId(int id);

    void setPosition(Position position);

    void setDirection(Direction direction);

    void setSize(int size);

    void setAlive(bool alive);

    [[nodiscard]] string directionToString() const;

    void displayBug() const;
};

#endif //CRAWLER_H
