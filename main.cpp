#include <iostream>
#include "Vehicle.h"
#include "Button.h"
#include "Track.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "main.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "TextInput.h"
#include "StaticTextField.h"
#include "DynamicTextField.h"


void measureFPS(float &deltaTime, sf::Clock &frameClock, float &fps)
{
    // FPS berechnen
    deltaTime = frameClock.restart().asSeconds();

    if (deltaTime > 0)
    {
        fps = 1.0f / deltaTime;
    }
};


int main() {

    // Erstelle Vehicle Instaz mit Startgeschwindigkeit 13,89 m/s
    Vehicle Polo(13.89f);
    
    // Initialisierung der Linien
    std::vector<TrackCoordinate> innerLine = { {100, 100}, {1100, 100}, };
    std::vector<TrackCoordinate> middleLine = { {100, 130}, {1100, 130} };
    std::vector<TrackCoordinate> outerLine = { {100, 160}, {1100, 160} };

    // Verschiedene mues sollen untergründe Simulieren. Für Asphalt ist mue = 0.8 ~, Sand ~0.4, Schnee 0.1~
    // ToDo: füge Textbox oder Auswahlmenü für Untergrund ein
    const float mue_h = 0.8;   

    // Erstelle eine Track-Instanz
    Track track(innerLine, middleLine, outerLine, mue_h);     

    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Erstelle Button Instanzen
    startButton startButton(200,300,100,50,font);
    resetButton resetButton(400,300,100,50,font);
    
    // Erstelle User Input Box Instanz 
    TextBox textBox(400.f, 200.f, 200.f, 25.f); 
    textBox.setText(Polo.properties["StartGeschwindigkeit"]);

    // Erstelle Textboxen
    StaticTextField aktuelleGeschwindigkeit(200.f, 230.f, 200.f, 25.f,"Aktuelle Geschwindigkeit [m/s]: " ,"AktuelleGeschwindigkeit");
    DynamicTextField aktuelleDynamicGeschwindigkeit (400.f, 230.f, 200.f, 25.f," " ,"AktuelleGeschwindigkeit");
    StaticTextField startGeschwindigkeit(200.f, 200.f, 180.f, 25.f,"Start-Geschwindigkeit [m/s]: " ,"StartGeschwindigkeit");
    StaticTextField bremsweg(200.f, 255.f, 200.f, 25.f,"Aktueller Bremsweg [m]: " ,"Bremsweg");
    DynamicTextField dynamicBremsweg (400.f, 255.f, 200.f, 25.f," " ,"Bremsweg");

    // Variablen Berechnung der FPS 
    sf::Clock frameClock;
    float deltaTime = 0.0f;
    float fps = 0.0f;

    // Erstelle ein Fenster mit der Größe 1200x600 Pixel und dem Titel Bremsweg Simulation
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Bremsweg Simulation");

    float dt = 1.0f; // Zeitschritt 1s

    // Hauptschleife
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

         // Reagiere auf Mausklicks, um das Eingabefeld zu aktivieren
            if (event.type == sf::Event::MouseButtonPressed) {
                if (textBox.isClicked(sf::Mouse::getPosition(window))) {
                    textBox.setSelected(true); // Fokus auf das Eingabefeld
                } else {
                    textBox.setSelected(false); // Fokus vom Eingabefeld nehmen
                }
            }

        measureFPS(deltaTime, frameClock, fps);

        // Lösche den vorherigen Frame
        window.clear(sf::Color::White);

        // Reagiere auf Tastatureingaben
        textBox.handleInput(event,Polo);

        // Checke, ob Mausposition über Buttons liegt und auf Button geclickt wurde
        startButton.update(sf::Mouse::getPosition(window),window);
        resetButton.update(sf::Mouse::getPosition(window),window);
        startButton.isPressed(Polo);
        resetButton.isPressed(Polo,startButton);

        // Aktualisiere Auto Eigenschaften
        aktuelleDynamicGeschwindigkeit.update(Polo.properties);
        dynamicBremsweg.update(Polo.properties);
        if(Polo.animationRunning){
            Polo.update(dt/fps,window);
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

