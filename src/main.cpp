#include <iostream>
#include "model/Crawler.h"
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "model/Board.h"
#include "model/Hopper.h"
#include "model/Superbug.h"

using namespace std;
using namespace sf;

void display_window();


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
        cout << "8. Run GUI" << endl << endl;
        cout << "9. Exit (write Life History of all Bugs to file)" << endl;

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
                board.displayHistory();

                break;
            case '9':
                board.writeHistoryToFile();
                break;
            case '8':
                display_window();
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != '9');
}

void drawBoard(vector<RectangleShape> &squares) {
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
               const Texture &super_texture, const Texture &bishop_texture,
               vector<Sprite> &sprites) {
    const float cellSize = 60.f;
    sprites.clear();
    for (const Bug *bug: bugs) {
        Sprite sprite;
        const string type = bug->getBugType();
        if (type == "Crawler") sprite.setTexture(crawler_texture);
        else if (type == "Hopper") sprite.setTexture(hopper_texture);
        else if (type == "Bishop") sprite.setTexture(bishop_texture);
        else if (type == "Super") sprite.setTexture(super_texture);
        auto bounds = sprite.getGlobalBounds();
        float scale_x, scale_y;
        scale_x = cellSize/bounds.width;
        scale_y = cellSize/bounds.height;
        sprite.setScale(scale_x, scale_y);
        sprite.setPosition(
            bug->getPosition().x * 60.f,
            bug->getPosition().y * 60.f
        );
        sprites.push_back(sprite);
    }
}


void processEvent(const Event &ev, Board &board, vector<const Bug *> &bugs, const Texture &crawlerTex,
                  const Texture &hopperTex, const Texture &bishopTex,
                  const Texture &superTex, vector<Sprite> &sprites) {
    if (ev.type == Event::KeyPressed) {
        switch (ev.key.code) {
            case Keyboard::Up:
                board.moveSuper(North);
                board.fight();

                break;
            case Keyboard::Down:
                board.moveSuper(South);
                board.fight();

                break;
            case Keyboard::Left:
                board.moveSuper(West);
                board.fight();

                break;
            case Keyboard::Right:
                board.moveSuper(East);
                board.fight();

                break;
            default:
                break;
        }
        bugs = board.getBugs();
        renderBug(bugs, crawlerTex, hopperTex, superTex, bishopTex, sprites);
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
    Texture crawlerTex, hopperTex, superTex, bishop_texture;
    crawlerTex.loadFromFile("../assets/crawler.jpeg");
    hopperTex.loadFromFile("../assets/hopper.jpeg");
    superTex.loadFromFile("../assets/super_bug.jpg");
    bishop_texture.loadFromFile("../assets/Bishop.jpeg");
    RenderWindow window(VideoMode(600, 600, 32), "Board");
    window.setFramerateLimit(60);
    drawBoard(squares);
    bool simulation = false;
    renderBug(bugs, crawlerTex, hopperTex, superTex, bishop_texture, bugSprites);
    Clock clock;
    const float interval = 0.1f;
    float time = 0.f;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                board.displayHistory();
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                board.tap();
                board.fight();
                bugs = board.getBugs();
                bugSprites.clear();
                renderBug(bugs, crawlerTex, hopperTex, superTex, bishop_texture, bugSprites);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                simulation = !simulation;
            }
            if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Down||event.key.code == Keyboard::Up||event.key.code == Keyboard::Left||event.key.code == Keyboard::Right)) {
                board.tap();
                board.fight();

            }
            processEvent(event, board, bugs, crawlerTex, hopperTex, bishop_texture, superTex, bugSprites);
        }
        float delta = clock.restart().asSeconds();
        time += delta;
        while (time >= interval && simulation) {
            time -= interval;

            if (!board.getBugs().empty()) {
                board.tap();
                board.fight();
                bugs = board.getBugs();
                bugSprites.clear();
                renderBug(bugs, crawlerTex, hopperTex, superTex, bishop_texture, bugSprites);
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
    menu(board);


    return 0;
}
