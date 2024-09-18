#include "../include/utils.h"

void measureFPS(float &deltaTime, sf::Clock &frameClock, float &fps)
{
    deltaTime = frameClock.restart().asSeconds();
    fps = 1.0f / deltaTime;
}