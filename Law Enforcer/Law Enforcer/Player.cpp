//
// Created by mad on 01/06/19.
//

#include "Player.h"
#include "global_definitions.h"

#define PLAYER_SIZE 1

Player::Player() : Entity({0,0}, 1) {}

Player::Player(b2World &world, b2Vec2 coordonnees, int pvmax) :
    Entity(coordonnees, pvmax)
{
    coordonnees_sfml=convert_coords(this->coordonnees, 0,-PLAYER_SIZE*PIXELS_BY_METER/2);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    //groundbox.Set(this->coordonnees, {this->coordonnees.x, this->coordonnees.y});
    groundbox.Set({-PLAYER_SIZE/2,-PLAYER_SIZE/2}, {PLAYER_SIZE/2, -PLAYER_SIZE/2});
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

void Player::draw(sf::RenderWindow &window) {
    //coordonnees_sfml = convert_coords(body->GetPosition(),0,-PLAYER_SIZE*PIXELS_BY_METER/2);
    coordonnees_sfml = convert_coords(body->GetPosition(),0,0);
    sf::RectangleShape shape({PLAYER_SIZE*PIXELS_BY_METER,PLAYER_SIZE*PIXELS_BY_METER});
    shape.setPosition(coordonnees_sfml);
    shape.setFillColor(sf::Color(60,0,60));
    window.draw(shape);
    sf::CircleShape debug_circle(5);
    debug_circle.setFillColor(sf::Color::Red);
    debug_circle.setPosition(SCREEN_WIDTH/2+body->GetPosition().x*PIXELS_BY_METER, SCREEN_WIDTH/2-body->GetPosition().y*PIXELS_BY_METER);
    sf::Vector2f position = debug_circle.getPosition();
    window.draw(debug_circle);
    debug_circle.setPosition(coordonnees_sfml);
    position = debug_circle.getPosition();
    window.draw(debug_circle);
}

void Player::update() {
}