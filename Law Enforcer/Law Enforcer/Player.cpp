//
// Created by mad on 01/06/19.
//

#include "Player.h"
#include "global_definitions.h"

Player::Player() : Entity({0,0}, 1) {}

Player::Player(b2World &world, b2Vec2 coordonnees, int pvmax) :
    Entity(coordonnees, pvmax)
{
    coordonnees_sfml=convert_coords(this->coordonnees, 0,-5);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    //groundbox.Set(this->coordonnees, {this->coordonnees.x+10/PIXELS_BY_METER, this->coordonnees.y});
    groundbox.Set({0,0}, {10/PIXELS_BY_METER, 0});
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

void Player::draw(sf::RenderWindow &window) {
    sf::RectangleShape shape({10,10});
    shape.setPosition(coordonnees_sfml);
    shape.setFillColor(sf::Color(60,0,60));
    window.draw(shape);
}

void Player::update() {
    coordonnees_sfml = convert_coords(body->GetPosition(),0,-5);
}