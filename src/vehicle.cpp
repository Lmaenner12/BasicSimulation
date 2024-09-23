#include "../include/vehicle.h"
#include <cmath>

Vehicle::Vehicle(float speed) : startingSpeed(speed), aktualSpeed(speed), bremsweg(0.0f)
{
    animationRunning = false;
    vehicleTexture.loadFromFile("./resources/auto.png");
    vehiclePosition = sf::Vector2f(100.0f, (115.0f - vehicleSprite.getGlobalBounds().height / 2.f));
    vehicleSprite.setScale(sf::Vector2f(0.3125f, 0.3125f));
    vehicleSprite.setPosition(vehiclePosition);
    vehicleSprite.setTexture(vehicleTexture);
    bremswegInsgesamt = 0;
    drivingTime = 0;

    // lade Bremsweg etc. in eine Map, um sie mittels vehicle["property"] abzurufen
    properties["Bremsweg"] = std::to_string(std::round(bremswegInsgesamt * 100.0) / 100.0);
    properties["AktuelleGeschwindigkeit"] = std::to_string(aktualSpeed);
    properties["StartGeschwindigkeit"] = std::to_string(startingSpeed);
}

void Vehicle::update(float dt)
{
    // ANNAHME: FAHRZEUG IST GLEICHMÄßIG BESCHLEUNIGT BZW VERZÖGERT
    if (aktualSpeed > 0)
    {
        drivingTime += dt;
        calculateVehicleProperties(dt);
    }
    else
    {
        animationRunning = false;
        aktualSpeed = 0.0f;
    }
    updateProperties();
}

void Vehicle::calculateVehicleProperties(float dt)
{
    if (drivingTime < 1)
    {
        bremsweg = (aktualSpeed * dt);
        animationRunning = true;
        // 1000 px für 100m Strecke --> 10px/m
        vehicleSprite.move(bremsweg * 10.0f, 0.0f);
        bremswegInsgesamt += bremsweg;
    }
    else
    {
        animationRunning = true;
        aktualSpeed = aktualSpeed - (8.0f * dt);
        // 1000 px für 200m Strecke --> 5px/m
        bremsweg = (aktualSpeed * dt);
        vehicleSprite.move(bremsweg * 5.0f, 0.0f);
        bremswegInsgesamt += bremsweg;
    }
}

void Vehicle::idlePosition()
{
    aktualSpeed = startingSpeed;
    bremsweg = 0.0f;
    animationRunning = false;
    vehicleSprite.setPosition(vehiclePosition);
    bremswegInsgesamt = bremsweg;
    drivingTime = 0;
}

void Vehicle::render(sf::RenderWindow &window)
{
    window.draw(vehicleSprite);
}

void Vehicle::startAnimation()
{
    animationRunning = true;
}

void Vehicle::reset()
{
    idlePosition();
    updateProperties();
}

void Vehicle::updateProperties()
{
    properties["Bremsweg"] = std::to_string(std::round(bremswegInsgesamt * 100.0) / 100.0);
    properties["AktuelleGeschwindigkeit"] = std::to_string(aktualSpeed);
    properties["StartGeschwindigkeit"] = std::to_string(startingSpeed);
}