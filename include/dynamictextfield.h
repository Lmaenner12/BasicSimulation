#ifndef DYNAMIC_TEXT_FIELD_H
#define DYNAMIC_TEXT_FIELD_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class DynamicTextField
{
public:
    DynamicTextField(float x, float y, float width, float height, std::string textDisplay, std::string type);
    void update(std::unordered_map<std::string, std::string> &vehicle_properties);
    void render(sf::RenderWindow &window);
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;
    std::string type;
};

#endif // DYNAMIC_TEXT_FIELD_H