//
// Created by dmytro on 26/03/25.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>

struct Position {
    int x;
    int y;
};

enum Direction {
    North,
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

    static void move();

    static bool isWayBlocked();

    [[nodiscard]] int getId() const;

    [[nodiscard]] Position getPosition() const;

    std::list<Position> getPath();

    [[nodiscard]] Direction getDirection() const;

    [[nodiscard]] int getSize() const;

    [[nodiscard]] bool isAlive() const;

    void setId(int id);

    void setPosition(Position position);

    void setDirection(Direction direction);

    void setSize(int size);

    void setAlive(bool alive);
};

#endif //CRAWLER_H
