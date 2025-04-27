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
                if (!board.getBugs().empty()) {
                    findBug(board);
                } else {
                    cout << "You have no bugs found. Please load bugs" << endl;
                }


                break;

            case '4':
                if (!board.getBugs().empty()) {
                    board.tap();

                    board.fight();
                } else {
                    cout << "You have no bugs found. Please load bugs" << endl;
                }


                break;

            case '5':
                if (!board.getBugs().empty()) {
                    board.displayHistory();
                } else {
                    cout << "You have no bugs found. Please load bugs" << endl;
                }


                break;

            case '6':

                board.displayCells();

                break;

            case '7':

                if (!board.getBugs().empty()) {
                    board.runSimulation();

                    board.displayHistory();
                } else {
                    cout << "You have no bugs found." << endl;
                }


                break;

            case '9':

                board.writeHistoryToFile();

                break;

            case '8':

                cout << endl;
                cout << "1. Display all Bugs" << endl;
                cout << "2. Display Life History of all Bugs (path taken)" << endl;
                cout << "3. Display all Cells listing their Bugs" << endl;
                cout << "4. Find a Bug (given an id)" << endl;
                cout << "Space. Tap the Bug Board (cause all to move, then fight/eat)" << endl;
                cout << "Enter. Run simulation (generates a Tap every tenth of a second)" << endl;
                cout << "Up/Down/Left/Right - move your superbug manually ";
                cout << "Escape. Exit (write Life History of all Bugs to file)" << endl;

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

void renderBug(vector<Bug *> &bugs, const Texture &crawler_texture, const Texture &hopper_texture,
               const Texture &super_texture, const Texture &bishop_texture,
               vector<Sprite> &sprites, Font &font, vector<Text> &labels) {
    font.loadFromFile("../assets/Trebuchet_MS.ttf");

    const float cellSize = 60.f;
    sprites.clear();
    labels.clear();
    for (Bug *bug: bugs) {
        Sprite sprite;
        const string type = bug->getBugType();
        if (type == "Crawler") sprite.setTexture(crawler_texture);
        else if (type == "Hopper") sprite.setTexture(hopper_texture);
        else if (type == "Bishop") sprite.setTexture(bishop_texture);
        else if (type == "Super") sprite.setTexture(super_texture);
        auto bounds = sprite.getGlobalBounds();
        float scale_x, scale_y;
        scale_x = cellSize / bounds.width;
        scale_y = cellSize / bounds.height;
        sprite.setScale(scale_x, scale_y);
        sprite.setPosition(
            bug->getPosition().x * 60.f,
            bug->getPosition().y * 60.f
        );
        sprites.push_back(sprite);

        Text label;
        int id = bug->getId();
        String idString = to_string(id);
        label.setString(idString);
        label.setFont(font);
        label.setCharacterSize(18);
        label.setFillColor(Color::Red);

        label.setPosition(
            bug->getPosition().x * cellSize,
            bug->getPosition().y * cellSize
        );

        labels.push_back(label);
    }
}


void processSuperbugEvent(const Event &ev, Board &board) {
    if (ev.type == Event::KeyPressed) {
        switch (ev.key.code) {
            case Keyboard::Up:
                board.penSuperDirection = North;

                break;
            case Keyboard::Down:
                board.penSuperDirection = South;

                break;
            case Keyboard::Left:
                board.penSuperDirection = West;

                break;
            case Keyboard::Right:
                board.penSuperDirection = East;

                break;
            default:
                break;
        }
    }

}


void display_window() {
    Font font;
    font.loadFromFile("../assets/Trebuchet_MS.ttf");
    vector<Text> labels;
    vector<RectangleShape> squares;
    Board board;
    board.loadBugs();
    vector<Bug *> bugs = board.getBugs();
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
    renderBug(bugs, crawlerTex, hopperTex, superTex, bishop_texture, bugSprites, font, labels);
    Clock clock;
    const float interval = 1.0f;
    float time = 0.f;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                board.writeHistoryToFile();
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                board.tap();
                board.fight();
                bugs = board.getBugs();

                bugSprites.clear();
                renderBug(bugs, crawlerTex, hopperTex, superTex, bishop_texture, bugSprites, font, labels);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                simulation = !simulation;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1) {
                board.displayBugs();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2) {
                board.displayHistory();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num3) {
                board.displayCells();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num4) {
                findBug(board);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                board.writeHistoryToFile();
                window.close();
            }

        }
        processSuperbugEvent(event, board);


        float delta = clock.restart().asSeconds();
        time += delta;
        while (time >= interval && simulation) {
            time -= interval;

            if (!board.getBugs().empty()) {
                if (board.penSuperDirection.has_value()) {
                    board.moveSuper(board.penSuperDirection.value());
                    board.penSuperDirection.reset();
                }

                board.tap();
                board.fight();
                bugs = board.getBugs();
            }
        }
        window.clear(Color::Black);
        for (RectangleShape &square: squares) {
            window.draw(square);
        }
        for (Sprite &sprite: bugSprites) {
            window.draw(sprite);
        }
        for (Text &text: labels) {
            window.draw(text);
        }
        bugSprites.clear();

        renderBug(bugs, crawlerTex, hopperTex, superTex, bishop_texture, bugSprites, font, labels);
        window.display();
    }
}

int main() {
    srand(time(nullptr));

    Board board;
    menu(board);


    return 0;
}
