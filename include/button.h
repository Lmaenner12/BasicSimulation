#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "vehicle.h"
enum ButtonState
{
    btn_idle,
    btn_hover,
    btn_active
};

class Button
{
public:
    Button(float x, float y, float width, float height, const std::string &text, const sf::Font &font,
           const sf::Color &idle, const sf::Color &hover, const sf::Color &active);

    virtual ~Button() = default; // Virtueller Destruktor für Vererbung

    // Setter für Button-Farben
    void setColors(const sf::Color &idle, const sf::Color &hover, const sf::Color &active);

    // Setter für die Button-Position und -Größe
    void setPosition(float x, float y);

    void setSize(float width, float height);

    virtual void render(sf::RenderWindow &window);

    // Abstrakte Update-Methode
    virtual void update(const sf::Vector2i &mousePosInt) = 0; // Reine virtuelle Methode

    ButtonState getButtonState();
    void setButtonState(ButtonState state);

protected:
    ButtonState buttonState;
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font buttonFont;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
};

class startButton : public Button
{
public:
    startButton(float x, float y, float width, float height, const sf::Font &font);

    bool isPressed(Vehicle &vehicle);

    void update(const sf::Vector2i &mousePosInt);
};

class resetButton : public Button
{
public:
    resetButton(float x, float y, float width, float height, const sf::Font &font);

    bool isPressed(Vehicle &vehicle, startButton &startButton);

    void update(const sf::Vector2i &mousePosInt);
};

#endif // BUTTON_H