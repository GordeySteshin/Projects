#include <SFML/Graphics.hpp> // Подключение библиотеки SFML для работы с графикой
#include <string> // Подключение библиотеки для работы со строками
#include <vector> // Подключение библиотеки для работы с векторами
#include <cmath> // Подключение библиотеки для математических функций
#include <iostream> // Подключение библиотеки для ввода/вывода
#include <cstdlib> //Для рандома
using namespace sf; // Используем пространство имен sf для упрощения кода
using namespace std; // Используем стандартное пространство имен

int main() {
    // Переменные для отслеживания времени
    float totalTime = 0.0f; // Общее время игры
    const float animationDuration = 10.0f; // Длительность анимации (не используется в коде)
    Clock gameClock; // Часы для отслеживания времени игры

    // Создание окна с размерами 1280x720 и заголовком "Snake"
    RenderWindow win(sf::VideoMode(1280, 720), "Snake");
    win.setVerticalSyncEnabled(true); // Включение вертикальной синхронизации для устранения разрывов изображения

    Texture snakeTexture;
    if (!snakeTexture.loadFromFile("Image/snake image.png")) {
        return 5; 
    }
    //Крыса
    Texture ratTexture;
    if (!ratTexture.loadFromFile("Image/rat.png")) {
        return 7;
    }
    CircleShape circle_rat(10.0f);
    circle_rat.setTexture(&ratTexture);
	circle_rat.setOrigin(circle_rat.getRadius(), circle_rat.getRadius());
    srand(static_cast<unsigned int>(time(0))); //Инициализация рандомного числа
    float randomX = static_cast<float>(rand() % (1280 - static_cast<int>(circle_rat.getRadius() * 2))) + circle_rat.getRadius();
    float randomY = static_cast<float>(rand() % (720 - static_cast<int>(circle_rat.getRadius() * 2))) + circle_rat.getRadius();
    circle_rat.setPosition(randomX, randomY); //Рандомное появление

    //Настройка изображения смерти
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

    // Загрузка и установка иконки окна
    Image icon;
    if (!icon.loadFromFile("Image/snake icon.png")) {
        return 1; // Если иконка не найдена, завершение программы
    }
    win.setIcon(512, 512, icon.getPixelsPtr()); // Установка иконки окна

    // Создание круга с радиусом 16.5 пикселей
    CircleShape circle(16.5f);
    circle.setFillColor(Color::Magenta); // Установка цвета круга на магенту
    circle.setTexture(&snakeTexture);
    circle.setPosition(640 - circle.getRadius(), 360 - circle.getRadius()); // Центрирование круга в окне

    // Загрузка шрифта
    Font font;
    if (!font.loadFromFile("Font/Harmonica.ttf")) {
        return 2; // Если шрифт не найден, завершение программы
    }

    // Создание текстовых объектов для отображения информации
    Text scoreText, timeText, lineText, name_game_Text;

    int score = 0; //Счёт

    // Настройка текста для счета
    scoreText.setFont(font); // Установка шрифта
    scoreText.setString("Score: " + score); // Установка начальной строки счета
    scoreText.setCharacterSize(24); // Установка размера шрифта
    scoreText.setFillColor(Color::Green); // Установка цвета текста на зеленый
    scoreText.setPosition(10, 10); // Позиция текста в окне

    // Настройка текста для времени
    timeText.setFont(font); // Установка шрифта
    timeText.setString("Time Alive: 0 sec"); // Установка начального текста времени
    timeText.setCharacterSize(24); // Установка размера шрифта
    timeText.setFillColor(Color::Green); // Установка цвета текста на зеленый
    timeText.setPosition(700, 10); // Позиция текста времени

    // Линия верхней рамки
    lineText.setFont(font); // Установка шрифта
    lineText.setString("------------------------------------------------------------"); // Установка строки
    lineText.setCharacterSize(24); // Установка размера шрифта
    lineText.setFillColor(Color::Green); // Установка цвета текста на зеленый
    lineText.setPosition(10, 30); // Позиция линии

    // Загрузка текстуры фона
    Texture Texture_earth;
    if (!Texture_earth.loadFromFile("Image/earth.png")) {
        return 3; // Если текстура не найдена, завершение программы
    }

    // Создание спрайта для фона
    Sprite sprite_earth(Texture_earth); // Создание спрайта с текстурой
    sprite_earth.setScale(
        128.0f / Texture_earth.getSize().x, // Масштабирование по ширине
        72.0f / Texture_earth.getSize().y // Масштабирование по высоте
    );

    Clock clock; // Часы для отслеживания времени
    float currentTime = 0.0f; // Текущее время (не используется в коде)

    // Основной игровой цикл
    RenderTexture backgroundTexture; // Текстура для отрисовки фона
    backgroundTexture.create(win.getSize().x, win.getSize().y); // Создание текстуры с размерами окна
    Sprite backgroundSprite; // Спрайт для отображения фона
    vector<Vector2f> drawnPositions; // Вектор для хранения позиций нарисованных объектов
    float y = 50; // Начальная позиция по вертикали для отрисовки фона
    float delay = 1.0f; // Задержка между отрисовками
    bool otrisovka = true; // Флаг для отрисовки фона

    // Массив строк для отображения названия игры
    vector<string> name = { "G", "a", "m", "e", " ", "S", "n", "a", "k", "e" };
    vector<Text> nameTexts(name.size()); // Вектор для хранения текстовых объектов названия игры

    // Настройка текстов из массива name
    for (size_t i = 0; i < name.size(); ++i) {
        nameTexts[i].setFont(font); // Установка шрифта
        nameTexts[i].setString(name[i]); // Установка строки
        nameTexts[i].setCharacterSize(48); // Установка размера шрифта
        nameTexts[i].setFillColor(Color::Red); // Установка цвета текста на красный
        nameTexts[i].setPosition(360 + i * 50, 360); // Позиция текста
    }

    bool nachalo = false; // Флаг для начала игры
    int a = 0; // Счетчик для отображения названия игры
    float x = 640 - circle.getRadius(); // Начальная позиция круга по горизонтали
    float y1 = 360 - circle.getRadius(); // Начальная позиция круга по вертикали
    int c = 1; // Счетчик для обновления времени
    float deltaTime = 0.0f;
    float omegaTime = 0.0f;
    int d = 1;
    int move = 0;
	bool death_bool = false; 
    int l = 1; //Для крыс
	float speed = 0.1f;
    // Основной игровой цикл
    while (win.isOpen()) {
        Event event; // Объект для хранения событий
        while (win.pollEvent(event)) {
            if (event.type == Event::Closed) { win.close(); } // Закрытие окна по событию
            if (event.type == Event::KeyPressed) {
                nachalo = true; // Начало игры по нажатию клавиши
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

        deltaTime = gameClock.restart().asSeconds(); // Время между кадрами
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

        totalTime += deltaTime; // Обновление общего времени

        // Отрисовка новых спрайтов в текстуру
        if (otrisovka && totalTime >= delay) {
            if (y <= win.getSize().y) {
                for (float x = 0; x < win.getSize().x; x += 128) {
                    Vector2f pos(x, y); // Позиция для отрисовки
                    drawnPositions.push_back(pos); // Добавление позиции в вектор
                    sprite_earth.setPosition(pos); // Установка позиции спрайта
                    backgroundTexture.draw(sprite_earth); // Отрисовка спрайта в текстуру
                }
                y += 72; // Обновление позиции по вертикали
                delay += 0.05f; // Обновление задержки
            }
            backgroundTexture.display(); // Обновление текстуры
            backgroundSprite.setTexture(backgroundTexture.getTexture()); // Установка текстуры спрайта
            if (a <= 8) { a++; } // Обновление счетчика для отображения названия игры
        }
        //Смерть
        float radius = circle.getRadius();
        if (circle.getPosition().x <= 0 ||
            circle.getPosition().x >= 1280 ||
            circle.getPosition().y <= 0 ||
            circle.getPosition().y >= 720) 
        {
			death_bool = true;  
            win.draw(deathSprite);
            
        }

        // Обновление текста времени
        int seconds = static_cast<int>(totalTime); // Преобразование времени в секунды

        // Отрисовка всего в окно
        if (!death_bool) {
            win.clear(); // Очистка окна
            win.draw(backgroundSprite); // Отрисовка фона
            scoreText.setString("Score: " + to_string(score));
            win.draw(scoreText); // Отрисовка текста счета
            win.draw(timeText); // Отрисовка текста времени
            win.draw(lineText); // Отрисовка линии
            if (a <= 8) {
                win.draw(nameTexts[a]); // Отрисовка текста названия игры
            }
            else {
                if (!nachalo) {
                    for (const auto& text : nameTexts) {
                        win.draw(text); // Отрисовка текста названия игры
                    }
                }
                else {
                    if (c == 1) {
                        totalTime -= totalTime; // Обнуление общего времени
                        c++; // Обновление счетчика
                    }
                    float distance = sqrt(pow(circle_rat.getPosition().x - circle.getPosition().x, 2) +
                        pow(circle_rat.getPosition().y - circle.getPosition().y, 2));
                    timeText.setString("Time Alive: " + to_string(seconds) + " sec"); // Обновление текста времени
                    win.draw(circle); // Отрисовка круга
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
        win.display(); // Отображение содержимого окна

        if (y >= 780) {
            otrisovka = false; // Остановка отрисовки фона
        }
    }

    return 0;
}