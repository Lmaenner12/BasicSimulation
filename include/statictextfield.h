#ifndef STATIC_TEXT_FIELD_H
#define STATIC_TEXT_FIELD_H

#include <SFML/Graphics.hpp>

class StaticTextField
{
public:
    StaticTextField(float x, float y, float width, float height, std::string textDisplay, std::string type);
    void render(sf::RenderWindow &window);
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;
    std::string type;
};

#endif // STATIC_TEXT_FIELD_H
