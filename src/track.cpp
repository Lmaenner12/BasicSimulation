#include "../include/track.h"
#include <iostream>

Track::Track(const std::vector<TrackCoordinate> &inner, const std::vector<TrackCoordinate> &middle, const std::vector<TrackCoordinate> &outer, const float mue) : innerLine(inner), middleLine(middle), outerLine(outer), frictionValue(mue) {}

void Track::printCoordinates() const
{
    std::cout << "Innere Linie:\n";
    printLineCoordinates(innerLine);
    std::cout << "\nMittlere Linie:\n";
    printLineCoordinates(middleLine);
    std::cout << "\nÄußere Linie:\n";
    printLineCoordinates(outerLine);
}

void Track::render(sf::RenderWindow &window) const
{
    drawLine(window, innerLine, sf::Color::Black);
    drawLine(window, middleLine, sf::Color::Black);
    drawLine(window, outerLine, sf::Color::Black);
}

void Track::printLineCoordinates(const std::vector<TrackCoordinate> &line) const
{
    for (const auto &coord : line)
    {
        std::cout << "(" << coord.x_coord << ", " << coord.y_coord << ")\n";
    }
}

void Track::drawLine(sf::RenderWindow &window, const std::vector<TrackCoordinate> &line, sf::Color color) const
{
    sf::VertexArray trackLine(sf::LineStrip, line.size());

    for (size_t i = 0; i < line.size(); ++i)
    {
        trackLine[i].position = sf::Vector2f(line[i].x_coord, line[i].y_coord);
        trackLine[i].color = color;
    }

    window.draw(trackLine);
}