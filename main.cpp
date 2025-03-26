#include <iostream>
#include "Crawler.h"
#include <fstream>
#include <sstream>

void parseLine(const std::string &line, Crawler *bug) {
    std::string temp;
    std::stringstream ss(line);

    getline(ss, temp, ',');
    getline(ss, temp, ',');
    int id = std::stoi(temp);
    bug->setId(id);
    getline(ss, temp, ',');
    int x = std::stoi(temp);

    getline(ss, temp, ',');
    int y = std::stoi(temp);
    bug->setPosition({x, y});
    getline(ss, temp, ',');
    int direction = std::stoi(temp);
    bug->setDirection(static_cast<Direction>(direction));
    getline(ss, temp, ',');
    int size = std::stoi(temp);
    bug->setSize(size);
}

void loadBugs(std::list<Crawler *> &bugs) {
    if (std::ifstream file("crawler-bugs.txt"); file) {
        std::string line;
        while (std::getline(file, line)) {
            Crawler *pbug = new Crawler();
            parseLine(line, pbug);
            bugs.push_back(pbug);
        }
    } else {
        std::cout << "File not found" << std::endl;
    }
}

void displayBugs(const std::list<Crawler *> &bugs) {
    for (const Crawler *bug: bugs) {
        std::cout << bug->getId() << " " << bug->getPosition().x << " " << bug->getPosition().y << " " <<
                bug->getDirection() << " " << bug->getSize() << std::endl;
    }
}

int main() {
    std::list<Crawler *> bugs;
    loadBugs(bugs);
    displayBugs(bugs);

    return 0;
}
