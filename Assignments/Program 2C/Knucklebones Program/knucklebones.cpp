#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <iostream>

using namespace std;

class DiceAnimation {
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::Texture> frames;
    int currentFrame;
    float frameDuration;
    float currentTime;

public:
    DiceAnimation(float duration)
        : currentFrame(0), frameDuration(duration / 24), currentTime(0) {
        for (int i = 1; i <= 24; ++i) {
            sf::Texture frame;
            std::ostringstream filename;
            filename << "images/frame_" << std::setw(3) << std::setfill('0') << i << ".png";
            if (!frame.loadFromFile(filename.str())) {
                cerr << "Error loading animation frame " << filename.str() << endl;
                exit(EXIT_FAILURE);
            }
            frames.push_back(frame);
        }
        sprite.setTexture(frames[0]);
    }

    void update(float deltaTime) {
        currentTime += deltaTime;
        if (currentTime >= frameDuration) {
            currentTime -= frameDuration;
            currentFrame = (currentFrame + 1) % 24;
            sprite.setTexture(frames[currentFrame]);
        }
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position) {
        sprite.setPosition(position);
        window.draw(sprite);
    }
};

class DiceFace {
    sf::Sprite sprite;
    sf::Texture texture;

public:
    void setFace(int value) {
        if (!texture.loadFromFile("images/" + to_string(value) + ".png")) {
            cerr << "Error loading dice face: " << value << endl;
            exit(EXIT_FAILURE);
        }
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window, sf::Vector2f position) {
        sprite.setPosition(position);
        window.draw(sprite);
    }
};

class Dice {
public:
    Dice() { srand(static_cast<unsigned>(time(0))); }

    int roll() { return rand() % 6 + 1; }
};

class Grid {
    int cells[3][3];

public:
    Grid() { clearGrid(); }

    void clearGrid() {
        for (auto& row : cells)
            fill(row, row + 3, 0);
    }

    bool placeDice(int col, int value) {
        for (int row = 2; row >= 0; --row) {
            if (cells[row][col] == 0) {
                cells[row][col] = value;
                return true;
            }
        }
        return false;
    }

    int calculateScore() const {
        int total = 0;
        for (int col = 0; col < 3; ++col) {
            int product = 0;
            int counts[6] = {0};

            for (int row = 0; row < 3; ++row) {
                if (cells[row][col] != 0) {
                    counts[cells[row][col] - 1]++;
                }
            }

            for (int i = 0; i < 6; ++i) {
                if (counts[i] > 0) {
                    product += counts[i] * (i + 1) * counts[i];
                }
            }

            total += product;
        }
        return total;
    }

    void render(sf::RenderWindow& window, sf::Vector2f position, sf::Color color) {
        sf::RectangleShape cell(sf::Vector2f(60, 60));
        cell.setOutlineColor(color);
        cell.setOutlineThickness(2);

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font!" << endl;
            return;
        }

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cell.setPosition(position.x + j * 70, position.y + i * 70);
                window.draw(cell);

                if (cells[i][j] != 0) {
                    text.setString(to_string(cells[i][j]));
                    text.setPosition(position.x + j * 70 + 20, position.y + i * 70 + 10);
                    window.draw(text);
                }
            }
        }
    }
};

class Player {
    string name;
    int score;

public:
    Player(string n) : name(n), score(0) {}

    void addToScore(int points) { score += points; }
    int getScore() const { return score; }
    string getName() const { return name; }
};

class Game {
    Player player1, player2;
    Grid grid1, grid2;
    Dice dice;
    int turn;
    bool running;

    bool isValidClick(sf::Vector2i mousePos, const sf::Vector2f& gridPosition) {
        sf::FloatRect gridBounds(gridPosition.x, gridPosition.y, 3 * 70, 3 * 70); // 3x3 grid, 70px cell
        return gridBounds.contains(static_cast<sf::Vector2f>(mousePos));
    }

public:
    Game() : player1("Player 1"), player2("Player 2"), turn(0), running(true) {}

    void play() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Knucklebones Game");

        // Load logo
        sf::Texture logoTexture;
        if (!logoTexture.loadFromFile("images/knuckleboneslogo.jpg")) {
            cerr << "Error loading logo!" << endl;
            return;
        }
        sf::Sprite logoSprite;
        logoSprite.setTexture(logoTexture);

        // Resize logo to 200 pixels in width while maintaining aspect ratio
        sf::Vector2u logoSize = logoTexture.getSize();
        float logoScale = 200.0f / logoSize.x;
        logoSprite.setScale(logoScale, logoScale);

        // Center the logo at the top
        float logoX = (window.getSize().x - logoSize.x * logoScale) / 2;
        logoSprite.setPosition(logoX, 10);

        // Load font
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font!" << endl;
            return;
        }

        // Adjust positions of grids
        sf::Vector2f grid1Position(150, 200); // Slightly lower to make space for the logo
        sf::Vector2f grid2Position(450, 200);

        // Text for instructions
        sf::Text infoText;
        infoText.setFont(font);
        infoText.setCharacterSize(24); // Larger text for readability
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(20, 500); // Positioned below grids


        while (window.isOpen() && running) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    takeTurn(window, grid1Position, grid2Position, infoText);
                }
            }

            window.clear(sf::Color::Black);
            window.draw(logoSprite); // Draw logo

            grid1.render(window, grid1Position, sf::Color::Red);
            grid2.render(window, grid2Position, sf::Color::Blue);

            infoText.setString((turn % 2 == 0 ? "Player 1" : "Player 2") + std::string("'s Turn\nPress 'R' to roll."));
            infoText.setFillColor(turn % 2 == 0 ? sf::Color::Red : sf::Color::Blue);
            window.draw(infoText);
            window.display();
        }

        endGame(window);
    }

    void takeTurn(sf::RenderWindow& window, const sf::Vector2f& grid1Position, const sf::Vector2f& grid2Position, sf::Text& infoText) {
        int roll = dice.roll();
        Player& currentPlayer = turn % 2 == 0 ? player1 : player2;
        Grid& currentGrid = turn % 2 == 0 ? grid1 : grid2;
        sf::Vector2f gridPosition = turn % 2 == 0 ? grid1Position : grid2Position;

        DiceAnimation diceAnimation(1.0f);
        float elapsedTime = 0.0f;
        sf::Clock clock;

        // Animation loop
        while (elapsedTime < 1.0f) {
            elapsedTime += clock.restart().asSeconds();
            diceAnimation.update(elapsedTime);
            window.clear(sf::Color::Black);
            grid1.render(window, grid1Position, sf::Color::Red);
            grid2.render(window, grid2Position, sf::Color::Blue);
            diceAnimation.draw(window, sf::Vector2f(300, 300));
            infoText.setString(currentPlayer.getName() + "'s Turn");
            window.draw(infoText);
            window.display();
        }

        // Show rolled dice face
        DiceFace diceFace;
        diceFace.setFace(roll);
        window.clear(sf::Color::Black);
        grid1.render(window, grid1Position, sf::Color::Red);
        grid2.render(window, grid2Position, sf::Color::Blue);
        diceFace.draw(window, sf::Vector2f(300, 300));
        infoText.setString(currentPlayer.getName() + "'s Turn\nRolled: " + to_string(roll));
        window.draw(infoText);
        window.display();

        sf::sleep(sf::seconds(1.0f));

        // Wait for a valid click
        bool placed = false;
        while (!placed) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    running = false;
                    window.close();
                    return;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                    // Check if the click is within the current player's grid
                    if (isValidClick(mousePos, gridPosition)) {
                        int col = (mousePos.x - static_cast<int>(gridPosition.x)) / 70;
                        if (col >= 0 && col < 3) {
                            placed = currentGrid.placeDice(col, roll);
                        }
                    }
                }
            }
        }

        turn++;
        checkGameOver();
    }

    void checkGameOver() {
        if (turn >= 18) {
            running = false;
        }
    }

    void endGame(sf::RenderWindow& window) {
        int score1 = grid1.calculateScore();
        int score2 = grid2.calculateScore();

        sf::Text resultText;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error loading font!" << endl;
            exit(EXIT_FAILURE);
        }

        resultText.setFont(font);
        resultText.setCharacterSize(24);
        resultText.setFillColor(sf::Color::White);

        string result;
        if (score1 > score2)
            result = "Player 1 Wins!";
        else if (score2 > score1)
            result = "Player 2 Wins!";
        else
            result = "It's a Draw!";

        resultText.setString("Game Over!\nPlayer 1: " + to_string(score1) + "\nPlayer 2: " + to_string(score2) + "\n" + result);
        resultText.setPosition(200, 200);

        window.clear(sf::Color::Black);
        window.draw(resultText);
        window.display();

        sf::sleep(sf::seconds(5));
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
