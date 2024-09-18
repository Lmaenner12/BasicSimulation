#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

class DynamicTextField{
public:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;
    std::string type;
    DynamicTextField(float x, float y, float width, float height, std::string textDisplay, std::string type) : type(type) {
        // Lade eine Schriftart (Passe den Pfad an)
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
        }

        // Initialisierung des Rechtecks (des Eingabefelds)
        box.setSize(sf::Vector2f(width, height));
        box.setPosition(sf::Vector2f(x, y));
        box.setFillColor(sf::Color::White);

        // Initialisierung des Texts
        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 6, y + 6); // Text leicht eingerückt
        text.setString(textDisplay);

    }
    void update(std::unordered_map<std::string, std::string>& vehicle_properties){
        text.setString(vehicle_properties[type]);
    }
        // Render-Funktion
    void render(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }
};