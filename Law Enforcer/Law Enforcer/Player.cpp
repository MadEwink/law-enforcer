//
// Created by mad on 01/06/19.
//

#include "global_definitions.h"
#include "Player.h"
#include "Inputs.h"

#define PLAYER_SIZE 0.3

Player::Player(b2World &world, b2Vec2 coordonnees, int pvmax) :
        Entity(coordonnees, pvmax, 5, 5, 5, 0, 0, 0),
    jump_time_max(15),
    jump_time_left(0),
    max_speed(10),
    jump_speed(8),
    contact_stun(30)
{
    b2BodyDef bodyDef;
    b2PolygonShape groundbox;
    b2FixtureDef fixtureDef;
    coordonnees_sfml=convert_coords(this->coordonnees, -PLAYER_SIZE*PIXELS_BY_METER,-PLAYER_SIZE*PIXELS_BY_METER);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    // groundbox (collision with platforms)
    groundbox.SetAsBox(PLAYER_SIZE, PLAYER_SIZE/10.0f, {0, -PLAYER_SIZE+PLAYER_SIZE/20.0f}, 0);
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData = (void*)entity_groundbox;
    body->CreateFixture(&fixtureDef);
    // groundDetector (decides whether can jump)
    b2PolygonShape groundDetector;
    groundDetector.SetAsBox(PLAYER_SIZE-(PLAYER_SIZE/20.0f),PLAYER_SIZE/20.0f, {0,-PLAYER_SIZE}, 0);
    b2FixtureDef gDec_fixtureDef;
    gDec_fixtureDef.shape = &groundDetector;
    gDec_fixtureDef.isSensor = true;
    gDec_fixtureDef.userData = (void*)player_footsensor;
    body->CreateFixture(&gDec_fixtureDef);
    // hurtbox (take damage)
    b2PolygonShape hurtbox;
    hurtbox.SetAsBox(PLAYER_SIZE,PLAYER_SIZE);
    b2FixtureDef hb_fdef;
    hb_fdef.shape = &hurtbox;
    //hb_fdef.isSensor = true;
    hb_fdef.userData = (void*)player_hurtbox;
    body->CreateFixture(&hb_fdef);
    // jump_hitbox
    b2PolygonShape jump_hitbox;
    jump_hitbox.SetAsBox(PLAYER_SIZE-(PLAYER_SIZE/20.0f), PLAYER_SIZE/1.0f, {0,-PLAYER_SIZE}, 0);
    b2FixtureDef j_h_fDef;
    j_h_fDef.shape = &jump_hitbox;
    j_h_fDef.isSensor = true;
    j_h_fDef.userData = (void*)player_jump_hitbox;
    body->CreateFixture(&j_h_fDef);
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

void Player::update(const Inputs &inputs, WorldRules &worldRules) {
    b2Vec2 speed_applied(body->GetLinearVelocity());
    if (time_without_control_left <= 0)
    {
        has_control = true;
    }
    if (has_control && inputs.get_pressed(left)) speed_applied.x = -max_speed;
    else if (has_control && inputs.get_pressed(right)) speed_applied.x = max_speed;
    else
    {
        if (abs(speed_applied.x) < 0.7f) speed_applied.x = 0;
        if (speed_applied.x > 0) speed_applied.x -= 0.7f;
        else if (speed_applied.x < 0) speed_applied.x += 0.7f;
    }
    if (has_control)
        speed_applied.y = jump(worldRules.jump, inputs.get_pressed(action_key::jump), speed_applied.y);
    else
    {
        time_without_control_left--;
    }
    if (time_ejection_left > 0)
    {
        time_ejection_left--;
        speed_applied = ejection_speed;
    }
    body->SetLinearVelocity(speed_applied);
}

float32 Player::jump(bool world_jump_rule, bool input_jump, float32 current_vspeed) {
    if (world_jump_rule) {
        auto contact = body->GetContactList();
        if (input_jump) {
            if (can_jump) {
                current_vspeed = jump_speed;
                jump_time_left = jump_time_max;
            } else if (jump_time_left > 0) {
                current_vspeed = jump_speed - (jump_time_max - jump_time_left) * (jump_speed / jump_time_max);
                jump_time_left--;
            }
        } else {
            jump_time_left = 0;
        }
        if (current_vspeed < 0) is_fall_attacking = true;
    } else
    {
        is_fall_attacking = false;
    }
    return current_vspeed;
}

int Player::get_contact_stun() const { return contact_stun; }

