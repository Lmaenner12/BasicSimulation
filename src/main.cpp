#include "../include/button.h"
#include "../include/utils.h"
#include "../include/vehicle.h"
#include "../include/track.h"
#include "../include/textinput.h"
#include "../include/statictextfield.h"
#include "../include/dynamictextfield.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream> // For error output

int main()
{
    // Erstelle Vehicle Instanz mit Startgeschwindigkeit 13,89 m/s
    Vehicle Polo(13.89f);

    // Initialisierung der Linien
    std::vector<TrackCoordinate> innerLine = {
        {100, 100},
        {1100, 100},
    };
    std::vector<TrackCoordinate> middleLine = {{100, 130}, {1100, 130}};
    std::vector<TrackCoordinate> outerLine = {{100, 160}, {1100, 160}};

    // Verschiedene Mües sollen Untergründe simulieren. Für Asphalt ist mue = 0.8 ~, Sand ~0.4, Schnee ~0.1
    const float mue_h = 0.8;

    // Erstelle eine Track-Instanz
    Track track(innerLine, middleLine, outerLine, mue_h);

    sf::Font font;
    if (!font.loadFromFile("./resources/arial.ttf"))
    {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Erstelle Button-Instanzen
    startButton startButton(200, 300, 100, 50, font);
    resetButton resetButton(400, 300, 100, 50, font);

    // Erstelle User Input Box Instanz
    TextBox textBox(400.f, 200.f, 200.f, 25.f);
    textBox.setText(Polo.properties["StartGeschwindigkeit"]);

    // Erstelle Textfelder
    StaticTextField aktuelleGeschwindigkeit(200.f, 230.f, 200.f, 25.f, "Aktuelle Geschwindigkeit [m/s]: ", "AktuelleGeschwindigkeit");
    DynamicTextField aktuelleDynamicGeschwindigkeit(400.f, 230.f, 200.f, 25.f, " ", "AktuelleGeschwindigkeit");
    StaticTextField startGeschwindigkeit(200.f, 200.f, 180.f, 25.f, "Start-Geschwindigkeit [m/s]: ", "StartGeschwindigkeit");
    StaticTextField bremsweg(200.f, 255.f, 200.f, 25.f, "Aktueller Bremsweg [m]: ", "Bremsweg");
    DynamicTextField dynamicBremsweg(400.f, 255.f, 200.f, 25.f, " ", "Bremsweg");

    // Variablen zur Berechnung der FPS
    sf::Clock frameClock;
    float deltaTime = 0.0f;
    float fps = 0.0f;

    // Erstelle ein Fenster mit der Größe 1200x600 Pixel und dem Titel "Bremsweg Simulation"
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Bremsweg Simulation");

    float dt = 1.0f; // Zeitschritt 1s

    // Hauptschleife
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Reagiere auf Mausklicks, um das Eingabefeld zu aktivieren
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (textBox.isClicked(sf::Mouse::getPosition(window)))
                {
                    textBox.setSelected(true); // Fokus auf das Eingabefeld
                }
                else
                {
                    textBox.setSelected(false); // Fokus vom Eingabefeld nehmen
                }
            }

            // Reagiere auf Tastatureingaben
            textBox.handleInput(event, Polo);
        }

        // Berechne FPS
        deltaTime = frameClock.restart().asSeconds();
        if (deltaTime > 0)
            fps = 1.0f / deltaTime;

        // Lösche den vorherigen Frame
        window.clear(sf::Color::White);

        // Aktualisiere die Buttons und prüfe auf Klicks
        startButton.update(sf::Mouse::getPosition(window));
        resetButton.update(sf::Mouse::getPosition(window));

        if (startButton.isPressed(Polo))
        {
            Polo.startAnimation(); // Beispielaufruf
        }

        if (resetButton.isPressed(Polo, startButton))
        {
            Polo.reset();
        }

        // Aktualisiere Auto-Eigenschaften
        aktuelleDynamicGeschwindigkeit.update(Polo.properties);
        dynamicBremsweg.update(Polo.properties);

        // Aktualisiere das Fahrzeug, wenn die Animation läuft
        if (Polo.animationRunning)
        {
            Polo.update(dt / fps);
        }

        // Render die UI-Objekte
        track.render(window);
        Polo.render(window);
        startButton.render(window);
        resetButton.render(window);
        textBox.render(window);
        aktuelleGeschwindigkeit.render(window);
        startGeschwindigkeit.render(window);
        bremsweg.render(window);
        aktuelleDynamicGeschwindigkeit.render(window);
        dynamicBremsweg.render(window);

        // Zeige das Fenster
        window.display();
    }

    return 0;
}