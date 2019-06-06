//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include <SFML/System.hpp>
#include "Platform.h"
#include "global_definitions.h"

Platform::Platform(b2World &world, b2Vec2 coordonnees, b2Vec2 size) :
    LevelObject(coordonnees),
    size(size)
{
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    b2PolygonShape debug_gb;
    debug_gb.SetAsBox(size.x, size.y);
    body->CreateFixture(&debug_gb, 0.0f);
}

void Platform::draw(sf::RenderWindow &window) {
    sf::RectangleShape shape({size.x/((float)2)*PIXELS_BY_METER, size.y/((float)2)*PIXELS_BY_METER});
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(coordonnees_sfml);
    window.draw(shape);
}

void Platform::update() {

}