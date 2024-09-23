#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "../include/vehicle.h"
#include <SFML/Graphics.hpp>

class TextBox
{
private:
    sf::RectangleShape box;

    sf::Font font;

    bool isSelected;
    bool keyPressed;       // Flags um zu überprüfen, ob eine Taste gedrückt ist
    bool backspacePressed; // Soll mehreres Registrieren durch die window loop der SFML verhindern

public:
    sf::Text text;
    TextBox(float x, float y, float width, float height);

    // Setzt den Textinhalt
    void setText(const std::string &input);

    // Gibt den Textinhalt zurück
    std::string getText() const;

    // Setzt den Fokus auf das Eingabefeld
    void setSelected(bool selected);

    bool getSelected() const;

    // Render-Funktion
    void render(sf::RenderWindow &window);

    // Update-Funktion für Tastatureingaben
    void handleInput(sf::Event event, Vehicle &vehicle);

    void addCharakterToText(sf::Event &event);

    void removeLastUserInput();

    void resetAfterNewUserInput(Vehicle &vehicle);

    // Prüft, ob der Klick in das Eingabefeld war
    bool isClicked(sf::Vector2i mousePos);
};

#endif // TEXTINPUT_H