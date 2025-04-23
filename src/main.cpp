#include <iostream>
#include "Crawler.h"
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.h"
#include "Hopper.h"

using namespace std;
using namespace sf;

void findBug(const Board &board) {
    int id;
    cout << "Please enter the bug's identification number you want to search: ";
    cin >> id;
    board.findBugById(id);
}

void menu(Board &board) {
    char choice;
    do {
        cout << endl;
        cout << "1. Initialize Bug Board (load data from file)" << endl;
        cout << "2. Display all Bugs" << endl;
        cout << "3. Find a Bug (given an id)" << endl;
        cout << "4. Tap the Bug Board (cause all to move, then fight/eat)" << endl;
        cout << "5. Display Life History of all Bugs (path taken)" << endl;
        cout << "6. Display all Cells listing their Bugs" << endl;
        cout << "7. Run simulation (generates a Tap every tenth of a second)" << endl;
        cout << "8. Exit (write Life History of all Bugs to file)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case '1': {
                std::vector<Bug *> bugs;
                board.loadBugs();
                break;
            }
            case '2':
                board.displayBugs();
                break;
            case '3':
                findBug(board);
                break;
            case '4':
                board.tap();
                board.fight();
                break;
            case '5':
                board.displayHistory();
                break;
            case '6':
                board.displayCells();
                break;
            case '7':
                board.runSimulation();
                break;
            case '8':
                board.writeHistoryToFile();
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != '8');
}

void drawBoard(vector<RectangleShape> &squares) {
    // view::BoardView board;

    bool colorWite = true;
    for (int i = 0; i < 10; i++) {
        for (int y = 0; y < 10; y++) {
            RectangleShape square(Vector2f(60, 60));
            square.setFillColor(colorWite ? Color::Green : Color::Magenta);
            colorWite = !colorWite;
            square.setPosition(static_cast<float>(i) * 60, static_cast<float>(y) * 60);
            squares.push_back(square);
        }
        colorWite = !colorWite;
    }

}

void renderBug(vector<const Bug *> &bugs, const Texture &crawler_texture, const Texture &hopper_texture,
               const Texture &super_texture,
               vector<Sprite> &sprites) {
    for (const Bug* &bug: bugs) {

        Sprite sprite;
        string type = bug->getBugType();
        cout << "Bug type: " << type << endl;

        if (type == "Crawler")  sprite.setTexture(crawler_texture);
        if (type == "Hopper") sprite.setTexture(hopper_texture);
        if (type == "Super") sprite.setTexture(super_texture);

        sprite.setScale(0.27, 0.27);
    sprite.setPosition(
        Vector2f((float) bug->getPosition().x * 60, (float) bug->getPosition().y * 60));
    sprites.push_back(sprite);
    }

}


void display_window() {
    srand(time(NULL));

    vector<RectangleShape> squares;
    Board board;
    board.loadBugs();
    vector<const Bug *> bugs = board.getBugs();
    string type = bugs.at(0)->getBugType();
    vector<Sprite> bugSprites;
    Texture crawlerTex, hopperTex, superTex;
    crawlerTex.loadFromFile("assets/crawler.jpeg");
    hopperTex.loadFromFile("assets/hopper.jpeg");
    superTex.loadFromFile("assets/super_bug.jpeg");
    RenderWindow window(VideoMode(600, 600, 32), "Board");
    window.setFramerateLimit(60);
    drawBoard(squares);

    renderBug(bugs, crawlerTex, hopperTex, superTex, bugSprites);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                board.tap();
                board.fight();
                bugs = board.getBugs();
                bugSprites.clear();
                renderBug(bugs, crawlerTex, hopperTex, superTex, bugSprites);
            }
        }
        window.clear(Color::Black);
        for (RectangleShape &square: squares) {
            window.draw(square);
        }
        for (Sprite &sprite: bugSprites) {
            window.draw(sprite);
        }
        window.display();
    }
}

int main() {
    srand(time(NULL));
    Board board;
    // menu(board);
     display_window();



    return 0;
}
