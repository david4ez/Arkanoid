#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <random>
#include <cstring>

const int NUMBER_OF_BLOCKS = 40;
const int LEN_X = 60;
const int LEN_Y = 20;

using namespace sf;
using namespace std;

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    srand(time(NULL));

    RenderWindow window(VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    RectangleShape paddle(Vector2f(100.f, 20.f));
    paddle.setFillColor(Color::Cyan);
    paddle.setPosition(350.f, 500.f);

    CircleShape ball(7.f);
    ball.setFillColor(Color::Green);

    Font font;
    font.loadFromFile("unicorn.ttf");

    Text gameOver("Game Over", font, 50);
    gameOver.setFillColor(Color::White);
    gameOver.setStyle(Text::Bold | Text::Italic);
    gameOver.setPosition(Vector2f(300.f, 200.f));

    Text gameStart("Start Game", font, 50);
    gameStart.setFillColor(Color::White);
    gameStart.setStyle(Text::Bold | Text::Italic);
    gameStart.setPosition(Vector2f(300.f, 200.f));

    Text gameReStart("Restart Game", font, 50);
    gameReStart.setFillColor(Color::White);
    gameReStart.setStyle(Text::Bold | Text::Italic);
    gameReStart.setPosition(Vector2f(275.f, 290.f));

    bool start = true;
    int score = 0;
    int destroyded_blocks = 0;

    Text gameScore("Score: " + to_string(score), font, 30);
    gameScore.setFillColor(Color::White);
    gameScore.setStyle(Text::Bold | Text::Italic);
    gameScore.setPosition(Vector2f(350.f, 14.f));

    int n = 0;
    RectangleShape* blocks = new RectangleShape[NUMBER_OF_BLOCKS];

    for (int i = 50; i < 800; i += 70) {
        for (int j = 60; j < 160; j += 30) {
            if (n == NUMBER_OF_BLOCKS)
                break;

            blocks[n].setSize(Vector2f(LEN_X, LEN_Y));
            blocks[n].setFillColor(Color::Blue);
            blocks[n].setPosition(i, j);
            n++;
        }
    }

    float paddle_x = 350;
    float dx = 6, dy = 4;
    float x = 200, y = 200;

    Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }

        if (start) {
            while (window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();
                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Escape)
                            window.close();
                    }
                    if (event.type == Event::MouseMoved) {
                        Vector2i mousePos = sf::Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                        if (gameStart.getGlobalBounds().contains(mousePosF))
                            gameStart.setFillColor(Color::Yellow);
                        else
                            gameStart.setFillColor(Color::White);
                    }
                    if (event.type == Event::MouseButtonPressed) {
                        Vector2i mousePos = sf::Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                        if (gameStart.getGlobalBounds().contains(mousePosF)) {
                            start = false;
                            goto Start;
                        }
                    }

                    window.clear();
                    window.draw(gameStart);
                    window.display();
                }
            }
        }

        Start:

        x += dx;
        for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(blocks[i].getGlobalBounds())) {
                blocks[i].setPosition(-100, 0);
                dx = -dx;
                score += 10;
                destroyded_blocks++;
            }
        }

        y += dy;
        for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(blocks[i].getGlobalBounds())) {
                blocks[i].setPosition(-100, 0);
                dy = -dy;
                score += 10;
                destroyded_blocks++;
            }
        }

        if (destroyded_blocks == NUMBER_OF_BLOCKS) {
            Text youWon("You Won!", font, 50);
            youWon.setFillColor(Color::White);
            youWon.setStyle(Text::Bold | Text::Italic);
            youWon.setPosition(Vector2f(300.f, 250.f));

            while (window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();
                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Escape)
                            window.close();
                    }
                }

                window.clear();
                window.draw(youWon);
                window.display();
            }
        }

        if (x < 0 || x > 793)
            dx = -dx;
        if (y < 0)
            dy = -dy;
        if (y > 600) {
            while (window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();
                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Escape)
                            window.close();
                    }
                    if (event.type == Event::MouseMoved) {
                        Vector2i mousePos = sf::Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                        if (gameReStart.getGlobalBounds().contains(mousePosF))
                            gameReStart.setFillColor(Color::Yellow);
                        else
                            gameReStart.setFillColor(Color::White);
                    }
                    if (event.type == Event::MouseButtonPressed) {
                        Vector2i mousePos = sf::Mouse::getPosition(window);
                        Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                        if (gameReStart.getGlobalBounds().contains(mousePosF)) {
                            n = 0;
                            for (int i = 50; i < 800; i += 70) {
                                for (int j = 60; j < 160; j += 30) {
                                    if (n == NUMBER_OF_BLOCKS)
                                        break;

                                    blocks[n].setPosition(i, j);
                                    n++;
                                }
                            }

                            paddle.setPosition(350.f, 500.f);
                            gameScore.setPosition(Vector2f(350.f, 14.f));

                            paddle_x = 350;
                            dx = 6;
                            dy = 4;
                            x = 200;
                            y = 200;
                            score = 0;
                            destroyded_blocks = 0;

                            goto Start;
                        }
                    }
                }

                window.clear();
                gameScore.setString("Score: " + to_string(score));
                gameScore.setPosition(Vector2f(345.f, 260.f));
                window.draw(gameOver);
                window.draw(gameScore);
                window.draw(gameReStart);
                window.display();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) && paddle_x < 700) {
            paddle.move(7, 0);
            paddle_x += 7;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && paddle_x > 0) {
            paddle.move(-7, 0);
            paddle_x -= 7;
        }

        if (FloatRect(x, y, 20, 12 ).intersects(paddle.getGlobalBounds()))
            dy = -(rand() % 5 + 2);

        ball.setPosition(x, y);

        window.clear();

        for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
            window.draw(blocks[i]);

        gameScore.setString("Score: " + to_string(score));
        window.draw(gameScore);
        window.draw(ball);
        window.draw(paddle);
        window.display();
    }

    delete[] blocks;

	return 0;
}