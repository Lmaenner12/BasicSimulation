#include <SFML/Graphics.hpp>
#include <iostream>


class TextBox {
private:
    sf::RectangleShape box;

    sf::Font font;

    bool isSelected;
    bool keyPressed;            // Flags um zu überprüfen, ob eine Taste gedrückt ist
    bool backspacePressed;      // Soll mehreres Registrieren durch die window loop der SFML verhindern

public:
    sf::Text text;
    TextBox(float x, float y, float width, float height) {
        // Lade eine Schriftart (Passe den Pfad an)
        if (!font.loadFromFile("arial.ttf")) {
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

    // Setzt den Textinhalt
    void setText(const std::string& input) {
        text.setString(input);
    }

    // Gibt den Textinhalt zurück
    std::string getText() const {
        return text.getString();
    }

    // Setzt den Fokus auf das Eingabefeld
    void setSelected(bool selected) {
        isSelected = selected;
        if (isSelected) {
            box.setOutlineColor(sf::Color::Red); // Roter Rand, wenn ausgewählt
        } else {
            box.setOutlineColor(sf::Color::Black); // Schwarzer Rand, wenn nicht ausgewählt
        }
    }

    bool getSelected() const {
        return isSelected;
    }

    // Render-Funktion
    void render(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }

    // Update-Funktion für Tastatureingaben
    void handleInput(sf::Event event, Vehicle& Vehicle) {
        if (isSelected) {
            if (event.type == sf::Event::TextEntered) {
                // Verhindert, dass wiederholt Zeichen eingefügt werden
                if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13 ) { // Nur ASCII Zeichen
                    addCharakterToText(event);
                }else if (event.text.unicode == 8){     // unicode  8 = backspace
                    removeLastUserInput();
                }else if (event.text.unicode == 13){    // uncicode 13 = enter
                    if(text.getString().isEmpty()){     // Crash, wenn Textfeld leer ist 
                        return;
                    }
                    resetAfterNewUserInput(Vehicle);
                    keyPressed = true;                  // Taste ist jetzt gedrückt
                }
            }else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Delete) {
                    removeLastUserInput();
                }
            }else if (event.type == sf::Event::KeyReleased){
                // FPS sind so hoch, dass einmaliges tippen mehrmals registriert wird. Deswegen werden Flags verwendet 
                // hier werden Flags zurückgesetzt
                keyPressed = false;         
                backspacePressed = false;
            }
        }
    }

    void addCharakterToText(sf::Event &event)
    {
        if (!keyPressed)
        {
            std::string str = text.getString();
            str += static_cast<char>(event.text.unicode);
            setText(str);
            keyPressed = true; // Taste ist jetzt gedrückt
        }
    }

    void removeLastUserInput()
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

    void resetAfterNewUserInput(Vehicle &Vehicle)
    {
        std::string str = text.getString();
        Vehicle.idlePosition();
        Vehicle.startingSpeed = std::stof(str);
        Vehicle.aktualSpeed = std::stof(str);
        Vehicle.updateProperties();
    }

    // Prüft, ob der Klick in das Eingabefeld war
    bool isClicked(sf::Vector2i mousePos) {
        return box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
};