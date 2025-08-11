#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

// Define a Theme struct holding colors
struct Theme {
    sf::Color background;
    sf::Color text;
    sf::Color highlight;
};

int main() {
    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Calendar");
    window.setFramerateLimit(60);

    // Load OpenSans font
    sf::Font font;
    if (!font.loadFromFile("OpenSans.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    // Themes: Light and Dark
    std::vector<Theme> themes = {
        { sf::Color(250, 250, 250), sf::Color(20, 20, 20), sf::Color(100, 149, 237) }, // Light
        { sf::Color(34, 34, 34), sf::Color(220, 220, 220), sf::Color(255, 165, 0) }      // Dark
    };
    int currentTheme = 0;

    // Calendar params
    const int cols = 7;
    const int rows = 7; // including weekday labels
    const float cellW = 100;
    const float cellH = 70;
    sf::Vector2f origin(50, 50);

    // Weekday labels
    std::vector<std::string> weekdays = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Get current month/year
    auto today = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(today);
    tm local = *std::localtime(&tt);
    int month = local.tm_mon; // 0-11
    int year = local.tm_year + 1900;

    // Helper: days in month
    auto daysInMonth = [&](int y, int m) {
        static int mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        bool leap = (y%4==0 && y%100!=0) || (y%400==0);
        return (m==1 ? (leap?29:28) : mdays[m]);
    };

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            // Switch theme on T key
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::T) {
                currentTheme = (currentTheme + 1) % themes.size();
            }
            // Navigate months
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Left) month--;
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Right) month++;
            if (month < 0) { month = 11; year--; }
            if (month > 11) { month = 0; year++; }
        }

        // Draw background
        window.clear(themes[currentTheme].background);

        // Draw month-year header
        sf::Text header;
        header.setFont(font);
        header.setString(std::to_string(year) + " - " + std::to_string(month+1));
        header.setCharacterSize(30);
        header.setFillColor(themes[currentTheme].text);
        header.setPosition(window.getSize().x/2 - header.getLocalBounds().width/2, 10);
        window.draw(header);

        // Draw weekdays
        for (int i = 0; i < cols; ++i) {
            sf::Text wd;
            wd.setFont(font);
            wd.setString(weekdays[i]);
            wd.setCharacterSize(20);
            wd.setFillColor(themes[currentTheme].text);
            wd.setPosition(origin.x + i*cellW + 10, origin.y);
            window.draw(wd);
        }

        // Calculate first weekday
        tm first = local;
        first.tm_year = year - 1900;
        first.tm_mon = month;
        first.tm_mday = 1;
        std::mktime(&first);
        int offset = first.tm_wday; // 0=Sun

        int dim = daysInMonth(year, month);
        int day = 1;
        for (int r = 1; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int idx = (r-1)*cols + c;
                if (idx >= offset && day <= dim) {
                    sf::Text txt;
                    txt.setFont(font);
                    txt.setString(std::to_string(day));
                    txt.setCharacterSize(24);
                    sf::Vector2f pos(origin.x + c*cellW + 10, origin.y + r*cellH + 10);
                    txt.setPosition(pos);
                    // Highlight today's
                    if (day == local.tm_mday && month == local.tm_mon && year == local.tm_year+1900) {
                        sf::CircleShape circle(20);
                        circle.setFillColor(themes[currentTheme].highlight);
                        circle.setPosition(pos.x-5, pos.y-5);
                        window.draw(circle);
                        txt.setFillColor(sf::Color::White);
                    } else {
                        txt.setFillColor(themes[currentTheme].text);
                    }
                    window.draw(txt);
                    day++;
                }
            }
        }

        window.display();
    }

    return 0;
}
