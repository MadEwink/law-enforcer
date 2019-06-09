//
// Created by mad on 01/06/19.
//

#include "Boss.h"

Boss::Boss(b2World &world, b2Vec2 coordonnees, int pvmax, int damage_attack, int damage_dash, int damage_jump,
           int damage_contact) :
           Entity(coordonnees, pvmax),
           damage_attack(damage_attack),
           damage_contact(damage_contact),
           damage_dash(damage_dash),
           damage_jump(damage_jump)
{
    b2BodyDef bodyDef;
    b2PolygonShape groundbox;
    b2FixtureDef fixtureDef;
    coordonnees_sfml=convert_coords(this->coordonnees, -BOSS_SIZE*PIXELS_BY_METER,-BOSS_SIZE*PIXELS_BY_METER);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    groundbox.SetAsBox(BOSS_SIZE, BOSS_SIZE);
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData = (void*)entity_groundbox;
    body->CreateFixture(&fixtureDef);
    b2CircleShape groundDetector;
    groundDetector.m_radius = BOSS_SIZE-0.001;
    groundDetector.m_p.Set(0,-BOSS_SIZE);
    b2FixtureDef gDec_fixtureDef;
    gDec_fixtureDef.shape = &groundDetector;
    gDec_fixtureDef.isSensor = true;
    gDec_fixtureDef.userData = (void*)player_footsensor;
    body->CreateFixture(&gDec_fixtureDef);
}

void Boss::draw(sf::RenderWindow &window) {
    coordonnees_sfml=convert_coords(body->GetPosition(), -BOSS_SIZE*PIXELS_BY_METER,-BOSS_SIZE*PIXELS_BY_METER);
    sf::RectangleShape shape({BOSS_SIZE*PIXELS_BY_METER*2.0,BOSS_SIZE*PIXELS_BY_METER*2.0});
    shape.setPosition(coordonnees_sfml);
    shape.setFillColor(sf::Color(145,215,255));
    window.draw(shape);
}

void Boss::update(const Inputs &inputs, WorldRules &worldRules) {

}

float32 Boss::jump(bool world_jump_rule, bool input_jump, float32 current_vspeed) {
    return current_vspeed;
}