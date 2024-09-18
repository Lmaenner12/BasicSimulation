#include "../include/textinput.h"
#include <iostream>

TextBox::TextBox(float x, float y, float width, float height)
{
    // Lade eine Schriftart (Passe den Pfad an)
    if (!font.loadFromFile("./resources/arial.ttf"))
    {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }

    // Initialisierung des Rechtecks (des Eingabefelds)
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(sf::Vector2f(x, y));
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);

    // Initialisierung des Texts
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 6, y + 6); // Text leicht eingerückt

    isSelected = false;
    keyPressed = false;
    backspacePressed = false;
}

void TextBox::setText(const std::string &input)
{
    text.setString(input);
}

std::string TextBox::getText() const
{
    return text.getString();
}

void TextBox::setSelected(bool selected)
{
    isSelected = selected;
    if (isSelected)
    {
        box.setOutlineColor(sf::Color::Red); // Roter Rand, wenn ausgewählt
    }
    else
    {
        box.setOutlineColor(sf::Color::Black); // Schwarzer Rand, wenn nicht ausgewählt
    }
}

bool TextBox::getSelected() const
{
    return isSelected;
}

void TextBox::render(sf::RenderWindow &window)
{
    window.draw(box);
    window.draw(text);
}

void TextBox::handleInput(sf::Event event, Vehicle &vehicle)
{
    if (isSelected)
    {
        if (event.type == sf::Event::TextEntered)
        {
            // Verhindert, dass wiederholt Zeichen eingefügt werden
            if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13)
            { // Nur ASCII Zeichen
                addCharakterToText(event);
            }
            else if (event.text.unicode == 8)
            { // unicode  8 = backspace
                removeLastUserInput();
            }
            else if (event.text.unicode == 13)
            { // uncicode 13 = enter
                if (text.getString().isEmpty())
                { // Crash, wenn Textfeld leer ist
                    return;
                }
                resetAfterNewUserInput(vehicle);
                keyPressed = true; // Taste ist jetzt gedrückt
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Delete)
            {
                removeLastUserInput();
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            // FPS sind so hoch, dass einmaliges tippen mehrmals registriert wird. Deswegen werden Flags verwendet
            // hier werden Flags zurückgesetzt
            keyPressed = false;
            backspacePressed = false;
        }
    }
}

void TextBox::addCharakterToText(sf::Event &event)
{
    if (!keyPressed)
    {
        std::string str = text.getString();
        str += static_cast<char>(event.text.unicode);
        setText(str);
        keyPressed = true; // Taste ist jetzt gedrückt
    }
}

void TextBox::removeLastUserInput()
{
    std::string str = text.getString();
    if (!backspacePressed)
    {
        if (!str.empty())
        {
            str.pop_back(); // Letztes Zeichen löschen
            setText(str);
            backspacePressed = true;
        }
    }
}

void TextBox::resetAfterNewUserInput(Vehicle &vehicle)
{
    std::string str = text.getString();
    vehicle.idlePosition();
    vehicle.startingSpeed = std::stof(str);
    vehicle.aktualSpeed = std::stof(str);
    vehicle.updateProperties();
}

bool TextBox::isClicked(sf::Vector2i mousePos)
{
    return box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}