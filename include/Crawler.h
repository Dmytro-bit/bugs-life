//
// Created by dmytro on 26/03/25.
//

#ifndef CRAWLER_H
#define CRAWLER_H


#include "Bug.h"

using namespace std;


class Crawler : public Bug {
public:
    Crawler();

    Crawler(int id, Position position, Direction direction, int size);

    void move() override;

    static string getBugType();

    void displayBug() const;
};

#endif //CRAWLER_H
