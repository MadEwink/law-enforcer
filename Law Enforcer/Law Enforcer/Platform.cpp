//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Platform.h"
#include "global_definitions.h"


Platform::Platform(b2Vec2 coordonnees, float32 size) :
    LevelObject(coordonnees),
    size(size)
{
    groundbox.Set(coordonnees, {coordonnees.x + size, coordonnees.y});
}

void Platform::draw(sf::RenderWindow &window) {
    sf::RectangleShape shape({size*PIXELS_BY_METER, 10});
    shape.setFillColor(sf::Color::Blue);
    window.draw(shape);
}

void Platform::update() {

}