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

    string getBugType() const override;

    void displayBug() override;
};

#endif //CRAWLER_H
