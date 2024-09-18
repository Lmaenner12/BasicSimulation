#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class VehicleCoordinate
{
public:
    float x_coord;
    float y_coord;

    VehicleCoordinate(float x, float y) : x_coord(x), y_coord(y) {};
};

class Vehicle
{
public:
    std::unordered_map<std::string, std::string> properties;
    sf::Vector2f vehiclePosition;
    float startingSpeed; // km/h
    float aktualSpeed;
    float bremsweg;
    float bremswegInsgesamt;
    float drivingTime;
    sf::Texture vehicleTexture;
    sf::Sprite vehicleSprite;
    bool animationRunning;

    Vehicle(float speed);

    void update(float dt);
    void calculateVehicleProperties(float dt);
    void idlePosition();
    void render(sf::RenderWindow &window);
    void startAnimation();
    void reset();
    void updateProperties();
};

#endif // VEHICLE_H
