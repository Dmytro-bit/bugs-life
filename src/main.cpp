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
    for (int i = 0; i <= 10; i++) {
        for (int y = 0; y <= 10; y++) {
            RectangleShape square(Vector2f(60, 60));
            square.setFillColor(colorWite ? Color::White : Color::Black);
            colorWite = !colorWite;
            square.setPosition(static_cast<float>(i) * 60, static_cast<float>(y) * 60);
            squares.push_back(square);
        }
    }
    colorWite = !colorWite;
}

void renderBug(Bug &bug, Texture &bugTexture, Sprite &sprite) {
    sprite.setScale(0.27, 0.27);
    string type = bug.getBugType();
    switch (char type_c = type.at(0)) {
        case 'C':
            bugTexture.loadFromFile("assets/crawler.jpeg");
            break;
        case 'H':
            bugTexture.loadFromFile("assets/hopper.jpeg");
            break;
        case 'S':
            bugTexture.loadFromFile("assets/super_bug.jpeg");
            break;
        default:
            cout << "Invalid bug type" << endl;
    }
    sprite.setTexture(bugTexture);
    sprite.setPosition(Vector2f(0.0, 0.0));

}

void display_window() {
    vector<RectangleShape> squares;
    Crawler bug;
    Sprite sprite;
    Texture texture;
    RenderWindow window(VideoMode(600, 600, 32), "Board");
    window.setFramerateLimit(60);
    drawBoard(squares);

    renderBug(bug, texture, sprite);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear(Color::Black);
        for (RectangleShape &square: squares) {
            window.draw(square);
        }
        window.draw(sprite);
        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(640, 480, 32), "Board");
    // srand(time(NULL));
    // Board board;
    // menu(board);
    display_window();
    return 0;
}
