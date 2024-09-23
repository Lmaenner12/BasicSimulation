#include "../include/dynamictextfield.h"
#include <iostream>

DynamicTextField::DynamicTextField(float x, float y, float width, float height, std::string textDisplay, std::string type) : type(type)
{
    if (!font.loadFromFile("./resources/arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Initialization of the rectangle (the input field)
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(sf::Vector2f(x, y));
    box.setFillColor(sf::Color::White);

    // Initialization of the text
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 6, y + 6); // Text slightly indented
    text.setString(textDisplay);
}

void DynamicTextField::update(std::unordered_map<std::string, std::string> &vehicle_properties)
{
    text.setString(vehicle_properties[type]);
}

void DynamicTextField::render(sf::RenderWindow &window)
{
    window.draw(box);
    window.draw(text);
}