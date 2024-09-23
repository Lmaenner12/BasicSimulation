#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <SFML/Graphics.hpp>

class TrackCoordinate
{
public:
    float x_coord;
    float y_coord;

    TrackCoordinate(float x, float y) : x_coord(x), y_coord(y) {};
};

class Track
{
private:
    std::vector<TrackCoordinate> innerLine;
    std::vector<TrackCoordinate> middleLine;
    std::vector<TrackCoordinate> outerLine;
    float frictionValue;

public:
    Track(const std::vector<TrackCoordinate> &inner, const std::vector<TrackCoordinate> &middle, const std::vector<TrackCoordinate> &outer, const float mue);

    // Funktion zum Ausgeben der Koordinaten jeder Linie
    void printCoordinates() const;
    // Funktion zum Zeichnen der Strecke mit SFML
    void render(sf::RenderWindow &window) const;

private:
    // Hilfsfunktion zum Ausgeben der Koordinaten einer Linie
    void printLineCoordinates(const std::vector<TrackCoordinate> &line) const;

    void drawLine(sf::RenderWindow &window, const std::vector<TrackCoordinate> &line, sf::Color color) const;
};

#endif // TRACK_H