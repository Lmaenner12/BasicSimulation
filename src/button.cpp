#include "../include/button.h"

Button::Button(float x, float y, float width, float height, const std::string &text,
               const sf::Font &font, const sf::Color &idle, const sf::Color &hover,
               const sf::Color &active) : idleColor(idle), hoverColor(hover), activeColor(active)
{
    buttonState = ButtonState::btn_idle;

    // Button Shape Initialisierung
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setPosition(sf::Vector2f(x, y));
    buttonShape.setFillColor(idleColor);

    // Text Initialisierung
    buttonFont = font;
    buttonText.setFont(buttonFont);
    buttonText.setString(text);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setCharacterSize(12);

    // Zentriere den Text im Button
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getGlobalBounds().width / 2.f) - buttonText.getGlobalBounds().width / 2.f,
        buttonShape.getPosition().y + (buttonShape.getGlobalBounds().height / 2.f) - buttonText.getGlobalBounds().height / 2.f);
}

void Button::setColors(const sf::Color &idle, const sf::Color &hover, const sf::Color &active)
{
    idleColor = idle;
    hoverColor = hover;
    activeColor = active;
}

void Button::setPosition(float x, float y)
{
    buttonShape.setPosition(sf::Vector2f(x, y));
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getGlobalBounds().width / 2.f) - buttonText.getGlobalBounds().width / 2.f,
        buttonShape.getPosition().y + (buttonShape.getGlobalBounds().height / 2.f) - buttonText.getGlobalBounds().height / 2.f);
}

void Button::setSize(float width, float height)
{
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getGlobalBounds().width / 2.f) - buttonText.getGlobalBounds().width / 2.f,
        buttonShape.getPosition().y + (buttonShape.getGlobalBounds().height / 2.f) - buttonText.getGlobalBounds().height / 2.f);
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(buttonShape);
    window.draw(buttonText);
}

ButtonState Button::getButtonState()
{
    return buttonState;
}

void Button::setButtonState(ButtonState state)
{
    buttonState = state;
}

// StartButton
startButton::startButton(float x, float y, float width, float height, const sf::Font &font) : Button(x, y, width, height, "Start", font, sf::Color(128, 128, 128, 200), sf::Color(128, 128, 128, 150), sf::Color(128, 128, 128, 255))
{
    // Weitere spezifische Initialisierungen für den StartButton (falls nötig)
}

bool startButton::isPressed(Vehicle &vehicle)
{
    if (buttonState == ButtonState::btn_active)
    {
        vehicle.animationRunning = true;
        return true;
    }
    return false;
}

void startButton::update(const sf::Vector2i &mousePosInt)
{
    // Mausposition konvertieren
    sf::Vector2f mousePos;
    mousePos = sf::Vector2f(mousePosInt); // In Weltkoordinaten umwandeln

    buttonState = ButtonState::btn_idle;

    // hover
    if (buttonShape.getGlobalBounds().contains(mousePos))
    {
        buttonState = ButtonState::btn_hover;

        // click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonState = ButtonState::btn_active;
        }
    }

    switch (buttonState)
    {

    case ButtonState::btn_idle:
        buttonShape.setFillColor(idleColor);
        break;

    case ButtonState::btn_hover:
        buttonShape.setFillColor(hoverColor);
        break;

    case ButtonState::btn_active:
        buttonShape.setFillColor(activeColor);
        break;
    }
}

// ResetButton
resetButton::resetButton(float x, float y, float width, float height, const sf::Font &font) : Button(x, y, width, height, "Reset", font, sf::Color(128, 128, 128, 200), sf::Color(128, 128, 128, 150), sf::Color(128, 128, 128, 255))
{
    // Weitere spezifische Initialisierungen für den StartButton (falls nötig)
}

bool resetButton::isPressed(Vehicle &vehicle, startButton &startButton)
{
    if (buttonState == ButtonState::btn_active)
    {
        vehicle.animationRunning = false;
        vehicle.aktualSpeed = vehicle.startingSpeed;
        vehicle.drivingTime = 0;
        vehicle.bremsweg = 0;
        vehicle.bremswegInsgesamt = 0;
        vehicle.updateProperties();
        startButton.setButtonState(ButtonState::btn_idle);
        return true;
    }
    return false;
}

void resetButton::update(const sf::Vector2i &mousePosInt)
{
    // Mausposition konvertieren
    sf::Vector2f mousePos;
    mousePos = sf::Vector2f(mousePosInt); // In Weltkoordinaten umwandeln

    buttonState = ButtonState::btn_idle;

    // hover
    if (buttonShape.getGlobalBounds().contains(mousePos))
    {
        buttonState = ButtonState::btn_hover;

        // click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonState = ButtonState::btn_active;
        }
    }

    switch (buttonState)
    {

    case ButtonState::btn_idle:
        buttonShape.setFillColor(idleColor);
        break;

    case ButtonState::btn_hover:
        buttonShape.setFillColor(hoverColor);
        break;

    case ButtonState::btn_active:
        buttonShape.setFillColor(activeColor);
        break;
    }
}