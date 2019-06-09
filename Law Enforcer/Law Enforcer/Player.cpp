//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Player.h"
#include "global_definitions.h"
#include "Inputs.h"

#define PLAYER_SIZE 0.8

Player::Player() : Entity({0,0}, 1) {}

Player::Player(b2World &world, b2Vec2 coordonnees, int pvmax) :
    Entity(coordonnees, pvmax),
    jump_time_max(30)
{
    coordonnees_sfml=convert_coords(this->coordonnees, -PLAYER_SIZE*PIXELS_BY_METER,-PLAYER_SIZE*PIXELS_BY_METER);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    groundbox.SetAsBox(PLAYER_SIZE, PLAYER_SIZE);
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

void Player::draw(sf::RenderWindow &window) {
    //coordonnees_sfml = convert_coords(body->GetPosition(),0,-PLAYER_SIZE*PIXELS_BY_METER/2);
    coordonnees_sfml=convert_coords(body->GetPosition(), -PLAYER_SIZE*PIXELS_BY_METER,-PLAYER_SIZE*PIXELS_BY_METER);
    sf::RectangleShape shape({PLAYER_SIZE*PIXELS_BY_METER*2.0,PLAYER_SIZE*PIXELS_BY_METER*2.0});
    shape.setPosition(coordonnees_sfml);
    shape.setFillColor(sf::Color(145,215,255));
    sf::RectangleShape shape2({PLAYER_SIZE*PIXELS_BY_METER*2.0, PLAYER_SIZE*PIXELS_BY_METER*2.0*3.0/5.0});
    sf::Vector2f delta(0,PLAYER_SIZE*PIXELS_BY_METER*2.0/5.0);
    shape2.setPosition(coordonnees_sfml+delta);
    shape2.setFillColor(sf::Color(255,102,255));
    sf::RectangleShape shape3({PLAYER_SIZE*PIXELS_BY_METER*2.0, PLAYER_SIZE*PIXELS_BY_METER*2.0/5.0});
    sf::Vector2f delta2(0,PLAYER_SIZE*PIXELS_BY_METER*2.0*2.0/5.0);
    shape3.setPosition(coordonnees_sfml+delta2);
    shape3.setFillColor(sf::Color::White);
    window.draw(shape);
    window.draw(shape2);
    window.draw(shape3);
}

void Player::update(const Inputs &inputs) {
    /*
    if (body->GetContactList() != nullptr)
        body->ApplyForceToCenter({0,40}, true);
        */
    b2Vec2 speed_applied(body->GetLinearVelocity());
    //b2Vec2 speed_applied(0,0);
    int max_speed = 10;
    int jump_speed = 8;
    if (inputs.get_pressed(left)) speed_applied.x = -max_speed;
    else if (inputs.get_pressed(right)) speed_applied.x = max_speed;
    else
    {
        if (abs(speed_applied.x) < 0.7f) speed_applied.x = 0;
        if (speed_applied.x > 0) speed_applied.x -= 0.7f;
        else if (speed_applied.x < 0) speed_applied.x += 0.7f;
    }
    if (inputs.get_pressed(jump))
    {
        auto contact = body->GetContactList();
        if (contact != nullptr && contact->contact->IsTouching())
        {
            jump_time_left = jump_time_max;
            b2Manifold *manifold = contact->contact->GetManifold();
            if (abs(manifold->localNormal.x) < abs(manifold->localNormal.y))
                speed_applied.y = jump_speed;
        }
        else if (jump_time_left > 0)
        {
            speed_applied.y = jump_speed-(jump_time_max-jump_time_left)*(jump_speed/jump_time_max);
            jump_time_left --;
        }
        else
        {
            speed_applied.y / 2;
        }
    }
    else
    {
        jump_time_left = 0;
        speed_applied.y / 2;
    }
    body->SetLinearVelocity(speed_applied);
}