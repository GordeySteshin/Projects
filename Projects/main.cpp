#include <SFML/Graphics.hpp> // ����������� ���������� SFML ��� ������ � ��������
#include <string> // ����������� ���������� ��� ������ �� ��������
#include <vector> // ����������� ���������� ��� ������ � ���������
#include <cmath> // ����������� ���������� ��� �������������� �������
#include <iostream> // ����������� ���������� ��� �����/������
#include <cstdlib> //��� �������
using namespace sf; // ���������� ������������ ���� sf ��� ��������� ����
using namespace std; // ���������� ����������� ������������ ����

int main() {
    // ���������� ��� ������������ �������
    float totalTime = 0.0f; // ����� ����� ����
    const float animationDuration = 10.0f; // ������������ �������� (�� ������������ � ����)
    Clock gameClock; // ���� ��� ������������ ������� ����

    // �������� ���� � ��������� 1280x720 � ���������� "Snake"
    RenderWindow win(sf::VideoMode(1280, 720), "Snake");
    win.setVerticalSyncEnabled(true); // ��������� ������������ ������������� ��� ���������� �������� �����������

    Texture snakeTexture;
    if (!snakeTexture.loadFromFile("Image/snake image.png")) {
        return 5; 
    }
    //�����
    Texture ratTexture;
    if (!ratTexture.loadFromFile("Image/rat.png")) {
        return 7;
    }
    CircleShape circle_rat(10.0f);
    circle_rat.setTexture(&ratTexture);
	circle_rat.setOrigin(circle_rat.getRadius(), circle_rat.getRadius());
    srand(static_cast<unsigned int>(time(0))); //������������� ���������� �����
    float randomX = static_cast<float>(rand() % (1280 - static_cast<int>(circle_rat.getRadius() * 2))) + circle_rat.getRadius();
    float randomY = static_cast<float>(rand() % (720 - static_cast<int>(circle_rat.getRadius() * 2))) + circle_rat.getRadius();
    circle_rat.setPosition(randomX, randomY); //��������� ���������

    //��������� ����������� ������
    Texture death;
    if (!death.loadFromFile("Image/dead.png")) {
        return 6; 
    }
    Sprite deathSprite;
    deathSprite.setTexture(death);
    deathSprite.setScale(
        static_cast<float>(win.getSize().x) / death.getSize().x,
        static_cast<float>(win.getSize().y) / death.getSize().y
    );

    // �������� � ��������� ������ ����
    Image icon;
    if (!icon.loadFromFile("Image/snake icon.png")) {
        return 1; // ���� ������ �� �������, ���������� ���������
    }
    win.setIcon(512, 512, icon.getPixelsPtr()); // ��������� ������ ����

    // �������� ����� � �������� 16.5 ��������
    CircleShape circle(16.5f);
    circle.setFillColor(Color::Magenta); // ��������� ����� ����� �� �������
    circle.setTexture(&snakeTexture);
    circle.setPosition(640 - circle.getRadius(), 360 - circle.getRadius()); // ������������� ����� � ����

    // �������� ������
    Font font;
    if (!font.loadFromFile("Font/Harmonica.ttf")) {
        return 2; // ���� ����� �� ������, ���������� ���������
    }

    // �������� ��������� �������� ��� ����������� ����������
    Text scoreText, timeText, lineText, name_game_Text;

    int score = 0; //����

    // ��������� ������ ��� �����
    scoreText.setFont(font); // ��������� ������
    scoreText.setString("Score: " + score); // ��������� ��������� ������ �����
    scoreText.setCharacterSize(24); // ��������� ������� ������
    scoreText.setFillColor(Color::Green); // ��������� ����� ������ �� �������
    scoreText.setPosition(10, 10); // ������� ������ � ����

    // ��������� ������ ��� �������
    timeText.setFont(font); // ��������� ������
    timeText.setString("Time Alive: 0 sec"); // ��������� ���������� ������ �������
    timeText.setCharacterSize(24); // ��������� ������� ������
    timeText.setFillColor(Color::Green); // ��������� ����� ������ �� �������
    timeText.setPosition(700, 10); // ������� ������ �������

    // ����� ������� �����
    lineText.setFont(font); // ��������� ������
    lineText.setString("------------------------------------------------------------"); // ��������� ������
    lineText.setCharacterSize(24); // ��������� ������� ������
    lineText.setFillColor(Color::Green); // ��������� ����� ������ �� �������
    lineText.setPosition(10, 30); // ������� �����

    // �������� �������� ����
    Texture Texture_earth;
    if (!Texture_earth.loadFromFile("Image/earth.png")) {
        return 3; // ���� �������� �� �������, ���������� ���������
    }

    // �������� ������� ��� ����
    Sprite sprite_earth(Texture_earth); // �������� ������� � ���������
    sprite_earth.setScale(
        128.0f / Texture_earth.getSize().x, // ��������������� �� ������
        72.0f / Texture_earth.getSize().y // ��������������� �� ������
    );

    Clock clock; // ���� ��� ������������ �������
    float currentTime = 0.0f; // ������� ����� (�� ������������ � ����)

    // �������� ������� ����
    RenderTexture backgroundTexture; // �������� ��� ��������� ����
    backgroundTexture.create(win.getSize().x, win.getSize().y); // �������� �������� � ��������� ����
    Sprite backgroundSprite; // ������ ��� ����������� ����
    vector<Vector2f> drawnPositions; // ������ ��� �������� ������� ������������ ��������
    float y = 50; // ��������� ������� �� ��������� ��� ��������� ����
    float delay = 1.0f; // �������� ����� �����������
    bool otrisovka = true; // ���� ��� ��������� ����

    // ������ ����� ��� ����������� �������� ����
    vector<string> name = { "G", "a", "m", "e", " ", "S", "n", "a", "k", "e" };
    vector<Text> nameTexts(name.size()); // ������ ��� �������� ��������� �������� �������� ����

    // ��������� ������� �� ������� name
    for (size_t i = 0; i < name.size(); ++i) {
        nameTexts[i].setFont(font); // ��������� ������
        nameTexts[i].setString(name[i]); // ��������� ������
        nameTexts[i].setCharacterSize(48); // ��������� ������� ������
        nameTexts[i].setFillColor(Color::Red); // ��������� ����� ������ �� �������
        nameTexts[i].setPosition(360 + i * 50, 360); // ������� ������
    }

    bool nachalo = false; // ���� ��� ������ ����
    int a = 0; // ������� ��� ����������� �������� ����
    float x = 640 - circle.getRadius(); // ��������� ������� ����� �� �����������
    float y1 = 360 - circle.getRadius(); // ��������� ������� ����� �� ���������
    int c = 1; // ������� ��� ���������� �������
    float deltaTime = 0.0f;
    float omegaTime = 0.0f;
    int d = 1;
    int move = 0;
	bool death_bool = false; 
    int l = 1; //��� ����
	float speed = 0.1f;
    // �������� ������� ����
    while (win.isOpen()) {
        Event event; // ������ ��� �������� �������
        while (win.pollEvent(event)) {
            if (event.type == Event::Closed) { win.close(); } // �������� ���� �� �������
            if (event.type == Event::KeyPressed) {
                nachalo = true; // ������ ���� �� ������� �������
                if (!death_bool) {win.draw(circle);}

                if (event.key.code == Keyboard::A) {
                    move = 1;
                }
                else if (event.key.code == Keyboard::S) {
                    move = 2;
                }
                else if (event.key.code == Keyboard::D) {
                    move = 3;
                }
                else if (event.key.code == Keyboard::W) {
                    move = 4;
                }
            }
        }

        deltaTime = gameClock.restart().asSeconds(); // ����� ����� �������
        omegaTime = clock.restart().asSeconds();
        currentTime += omegaTime;

        if (currentTime >= speed && nachalo == true) {
            if (move == 1)
            {
                circle.setPosition(x - circle.getRadius(), y1);
                x -= circle.getRadius();
                currentTime = 0.0f;
            }
            else if (move == 2)
            {
                circle.setPosition(x, y1 + circle.getRadius());
                y1 += circle.getRadius();
                currentTime = 0.0f;
            }
            else if (move == 3)
            {
                circle.setPosition(x + circle.getRadius(), y1);
                x += circle.getRadius();
                currentTime = 0.0f;
            }
            else if (move == 4)
            {
                circle.setPosition(x, y1 - circle.getRadius());
                y1 -= circle.getRadius();
                currentTime = 0.0f;
            }
        }

        totalTime += deltaTime; // ���������� ������ �������

        // ��������� ����� �������� � ��������
        if (otrisovka && totalTime >= delay) {
            if (y <= win.getSize().y) {
                for (float x = 0; x < win.getSize().x; x += 128) {
                    Vector2f pos(x, y); // ������� ��� ���������
                    drawnPositions.push_back(pos); // ���������� ������� � ������
                    sprite_earth.setPosition(pos); // ��������� ������� �������
                    backgroundTexture.draw(sprite_earth); // ��������� ������� � ��������
                }
                y += 72; // ���������� ������� �� ���������
                delay += 0.05f; // ���������� ��������
            }
            backgroundTexture.display(); // ���������� ��������
            backgroundSprite.setTexture(backgroundTexture.getTexture()); // ��������� �������� �������
            if (a <= 8) { a++; } // ���������� �������� ��� ����������� �������� ����
        }
        //������
        float radius = circle.getRadius();
        if (circle.getPosition().x <= 0 ||
            circle.getPosition().x >= 1280 ||
            circle.getPosition().y <= 0 ||
            circle.getPosition().y >= 720) 
        {
			death_bool = true;  
            win.draw(deathSprite);
            
        }

        // ���������� ������ �������
        int seconds = static_cast<int>(totalTime); // �������������� ������� � �������

        // ��������� ����� � ����
        if (!death_bool) {
            win.clear(); // ������� ����
            win.draw(backgroundSprite); // ��������� ����
            scoreText.setString("Score: " + to_string(score));
            win.draw(scoreText); // ��������� ������ �����
            win.draw(timeText); // ��������� ������ �������
            win.draw(lineText); // ��������� �����
            if (a <= 8) {
                win.draw(nameTexts[a]); // ��������� ������ �������� ����
            }
            else {
                if (!nachalo) {
                    for (const auto& text : nameTexts) {
                        win.draw(text); // ��������� ������ �������� ����
                    }
                }
                else {
                    if (c == 1) {
                        totalTime -= totalTime; // ��������� ������ �������
                        c++; // ���������� ��������
                    }
                    float distance = sqrt(pow(circle_rat.getPosition().x - circle.getPosition().x, 2) +
                        pow(circle_rat.getPosition().y - circle.getPosition().y, 2));
                    timeText.setString("Time Alive: " + to_string(seconds) + " sec"); // ���������� ������ �������
                    win.draw(circle); // ��������� �����
                    if (l == 1) {
                        circle_rat.setPosition(randomX, randomY);
                        win.draw(circle_rat);
                        l++;
                    }
                    else if (distance - 3 < (circle_rat.getRadius() + circle.getRadius()))
                    {
                        score += 100;
                        speed -= 0.002;
                        randomX = static_cast<float>(rand() % (1280 - static_cast<int>(circle_rat.getRadius() * 2))) + circle_rat.getRadius();
                        randomY = static_cast<float>(rand() % (720 - static_cast<int>(circle_rat.getRadius() * 2))) + circle_rat.getRadius();
                        circle_rat.setPosition(randomX, randomY);
                    }
                    else { win.draw(circle_rat); }
                }
            }
        }
        win.display(); // ����������� ����������� ����

        if (y >= 780) {
            otrisovka = false; // ��������� ��������� ����
        }
    }

    return 0;
}