#include <SFML/Graphics.hpp>
#include <iostream>



enum ButtonState { btn_idle, btn_hover, btn_active };

class Button {
    protected:
    

    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font buttonFont;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    short unsigned buttonState;
    Button(float x, float y, float width, float height, const std::string& text, const sf::Font& font,
           const sf::Color& idle, const sf::Color& hover, const sf::Color& active) : idleColor(idle), hoverColor(hover), activeColor(active) {
        buttonState = btn_idle;

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
            buttonShape.getPosition().y + (buttonShape.getGlobalBounds().height / 2.f) - buttonText.getGlobalBounds().height / 2.f
        );
    }

    virtual ~Button() = default; // Virtueller Destruktor für Vererbung

    // Setter für Button-Farben
    void setColors(const sf::Color& idle, const sf::Color& hover, const sf::Color& active) {
        idleColor = idle;
        hoverColor = hover;
        activeColor = active;
    }

    // Setter für die Button-Position und -Größe
    void setPosition(float x, float y) {
        buttonShape.setPosition(sf::Vector2f(x, y));
    }

    void setSize(float width, float height) {
        buttonShape.setSize(sf::Vector2f(width, height));
    }

    virtual void render(sf::RenderWindow& window){
        window.draw(buttonShape);
        window.draw(buttonText);
    };

    // Abstrakte Update-Methode
    virtual void update(const sf::Vector2i& mousePosInt, const sf::RenderWindow& window) = 0; // Reine virtuelle Methode

        
};

class startButton : public Button {
    public:
        startButton(float x, float y, float width, float height, const sf::Font& font) : Button(x, y, width, height, "Start", font, sf::Color (128, 128, 128,200), sf::Color (128, 128, 128, 150), sf::Color (128, 128, 128, 255)) 
        {
        // Weitere spezifische Initialisierungen für den StartButton (falls nötig)
        }

        bool isPressed(Vehicle& vehicle) {
            if(buttonState == btn_active){
                vehicle.animationRunning = true;
                return true;
            }
            return false;
        }

        void update (const sf::Vector2i& mousePosInt, const sf::RenderWindow& window){

            // Mausposition konvertieren
            sf::Vector2f mousePos;
            mousePos = sf::Vector2f(mousePosInt);  // In Weltkoordinaten umwandeln
            
            buttonState = btn_idle;

            //hover
            if(buttonShape.getGlobalBounds().contains(mousePos)) {
                buttonState = btn_hover;

                //click
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    buttonState = btn_active;
                }
            }

            switch (buttonState) {

                case btn_idle:
                    buttonShape.setFillColor(idleColor);
                break;

                case btn_hover:
                    buttonShape.setFillColor(hoverColor);
                break;

                case btn_active:
                    buttonShape.setFillColor(activeColor);
                break;
            }
        };
};

class resetButton : public Button {
    public:
        resetButton(float x, float y, float width, float height, const sf::Font& font) : Button(x, y, width, height, "Reset", font, sf::Color (128, 128, 128,200), sf::Color (128, 128, 128, 150), sf::Color (128, 128, 128, 255)) 
        {
        // Weitere spezifische Initialisierungen für den StartButton (falls nötig)
        }

        bool isPressed(Vehicle& vehicle,startButton& startButton) {
            if(buttonState == btn_active){
                vehicle.animationRunning = false;
                startButton.buttonState = btn_idle;
                vehicle.idlePosition();
                vehicle.updateProperties();
                return true;
            }
            return false;
        }

        void update (const sf::Vector2i& mousePosInt, const sf::RenderWindow& window){

            // Mausposition konvertieren
            sf::Vector2f mousePos;
            mousePos = sf::Vector2f(mousePosInt);  // In Weltkoordinaten umwandeln
            
            buttonState = btn_idle;

            //hover
            if(buttonShape.getGlobalBounds().contains(mousePos)) {
                buttonState = btn_hover;

                //click
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    buttonState = btn_active;
                }
            }

            switch (buttonState) {

                case btn_idle:
                    buttonShape.setFillColor(idleColor);
                break;

                case btn_hover:
                    buttonShape.setFillColor(hoverColor);
                break;

                case btn_active:
                    buttonShape.setFillColor(activeColor);
                break;
            }
        };
};