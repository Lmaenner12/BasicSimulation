#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class TrackCoordinate{
    public:
        float x_coord;
        float y_coord;

    TrackCoordinate(float x, float y) : x_coord(x), y_coord(y){};
};

class Track {
    private:
    std::vector<TrackCoordinate> innerLine;
    std::vector<TrackCoordinate> middleLine;
    std::vector<TrackCoordinate> outerLine;
    float frictionValue;

    public:

    Track(const std::vector<TrackCoordinate>& inner,const std::vector<TrackCoordinate>& middle, const std::vector<TrackCoordinate>& outer, const float mue) : innerLine(inner), middleLine(middle), outerLine(outer), frictionValue(mue) {}

    // Funktion zum Ausgeben der Koordinaten jeder Linie
    void printCoordinates() const {
        std::cout << "Innere Linie:\n";
        printLineCoordinates(innerLine);
        std::cout << "\nMittlere Linie:\n";
        printLineCoordinates(middleLine);
        std::cout << "\nÄußere Linie:\n";
        printLineCoordinates(outerLine);
    }
    // Funktion zum Zeichnen der Strecke mit SFML
    void render(sf::RenderWindow& window) const {
        drawLine(window, innerLine, sf::Color::Black);
        drawLine(window, middleLine, sf::Color::Black);
        drawLine(window, outerLine, sf::Color::Black);
    }

    private:
    // Hilfsfunktion zum Ausgeben der Koordinaten einer Linie
    void printLineCoordinates(const std::vector<TrackCoordinate>& line) const {
        for (const auto& coord : line) {
            std::cout << "(" << coord.x_coord << ", " << coord.y_coord << ")\n";
        }
    }

    void drawLine(sf::RenderWindow& window, const std::vector<TrackCoordinate>& line, sf::Color color) const {
        sf::VertexArray trackLine(sf::LineStrip, line.size());  // trackLine wird als VertexArray deklariert. Mit Art der Verbindung und größe des Arrays bzw. Anzahl an Verteces (pl. von Vertex)

        for (size_t i = 0; i < line.size(); ++i) {
            // 
            trackLine[i].position = sf::Vector2f(line[i].x_coord, line[i].y_coord);     //Normales Array funktioniert auch, sf Vektor evtl besser, wird sich zeigen 
            trackLine[i].color = color;
        }

        window.draw(trackLine);
    }

    
};