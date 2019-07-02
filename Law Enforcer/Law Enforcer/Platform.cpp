//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Platform.h"

Platform::Platform(b2World &world, b2Vec2 coordonnees, b2Vec2 size, float32 friction) :
    LevelObject(coordonnees),
    size(size)
{
    b2BodyDef bodyDef;
    b2PolygonShape groundbox;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    groundbox.SetAsBox(size.x, size.y);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundbox;
    fixtureDef.friction = friction;
    fixtureDef.density=0.0f;
    fixtureDef.userData = (void*)plateform_groundbox;
    body->CreateFixture(&fixtureDef);
    //body->CreateFixture(&groundbox, 0.0f);
    coordonnees_sfml = convert_coords(coordonnees, -size.x*PIXELS_BY_METER, -size.y*PIXELS_BY_METER);
}

void Platform::draw(sf::RenderWindow &window) {
	float size_x = size.x*2.0*PIXELS_BY_METER;
	float size_y = size.y*2.0*PIXELS_BY_METER;
    sf::RectangleShape shape({size_x, size_y});
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(coordonnees_sfml);
    window.draw(shape);
}

void Platform::update(const Inputs &inputs, WorldRules &worldRules) {

}