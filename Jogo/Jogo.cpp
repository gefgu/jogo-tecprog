#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/math/Coordinates.h"

using namespace std;
using namespace Math;

int main()
{
    //sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    window.clear();
    //    window.draw(shape);
    //    window.display();
    //}

    //return 0;
    Coord<int> pos1 = Coord<int>(1, 2);
    Coord<int> pos2 = Coord<int>(3, 2);
    cout << pos1 << endl;
    cout << (pos1 * 2) << endl;
    cout << (pos1 + pos2) << endl;
}