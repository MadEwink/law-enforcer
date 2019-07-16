//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Level.h"
#include "Inputs.h"
#include "Player.h"
#include "Entity.h"

void loadFixture(b2Body* body, pugi::xml_node node)
{
    b2FixtureDef fixtureDef;
    fixtureDef.density = node.child("density").attribute("value").as_float(0);
    fixtureDef.friction = node.child("friction").attribute("value").as_float(0);
    fixtureDef.isSensor = node.child("isSensor").attribute("value").as_bool(false);
    fixtureDef.restitution = node.child("restitution").attribute("value").as_float(0);
    fixtureDef.userData = (void*)node.child("userData").attribute("value").as_int(0);
    if (node.child("shape").attribute("value").as_string("Rectangle") == "Circle")
    {
        b2CircleShape shape;
        shape.m_p = {node.child("position").attribute("x").as_float(0),
                     node.child("position").attribute("y").as_float(0)};
        shape.m_radius = {node.child("size").attribute("r").as_float(0)};
        fixtureDef.shape = &shape;
    } else {
        b2PolygonShape shape;
        shape.SetAsBox(node.child("size").attribute("x").as_float(0),
                node.child("size").attribute("y").as_float(0),
                {node.child("position").attribute("x").as_float(0),
                 node.child("position").attribute("y").as_float(0)},0);
        fixtureDef.shape = &shape;
    }
    body->CreateFixture(&fixtureDef);
}

Entity::Entity(b2World &world, pugi::xml_node node) :
    LevelObject(node),
    pvmax(node.child("pvmax").attribute("value").as_int(0)),
    pv(pvmax),
    has_control(true),
    can_jump(false),
    is_fall_attacking(false),
    is_dashing(false),
    is_facing_right(true),
    damage_attack(node.child("damage_attack").attribute("value").as_int(0)),
    damage_jump(node.child("damage_jump").attribute("value").as_int(0)),
    damage_dash(node.child("damage_dash").attribute("value").as_int(0)),
    attack_stun(node.child("attack_stun").attribute("value").as_int(0)),
    dash_stun(node.child("dash_stun").attribute("value").as_int(0)),
    jump_stun(node.child("jump_stun").attribute("value").as_int(0)),
    dash_speed(node.child("dash_speed").attribute("value").as_int(0))
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    for (auto i : node.child("Hitboxes").children()) {
        loadFixture(body, i);
    }
}

Entity::Entity(b2Vec2 coordonnees, int pvmax, int damage_attack, int damage_dash, int damage_jump, int attack_stun,
               int dash_stun, int jump_stun, int dash_speed) :
    LevelObject(coordonnees),
    pvmax(pvmax),
    pv(pvmax),
    has_control(true),
    can_jump(false),
    is_fall_attacking(false),
    is_dashing(false),
    is_facing_right(true),
    damage_attack(damage_attack),
    damage_jump(damage_jump),
    damage_dash(damage_dash),
    attack_stun(attack_stun),
    dash_stun(dash_stun),
    jump_stun(jump_stun),
    dash_speed(dash_speed)
{}

void Entity::setJump(bool jump) {
    can_jump = jump;
    if (jump) is_fall_attacking = false;
}

void Entity::take_damage(int damage, int time_without_control, b2Vec2 ejection_speed) {
    pv -= damage;
    if (pv <= 0)
    {
        pv = 0;
        printf("The entity %p has died.\n", this);
    }
    time_without_control_left = time_without_control;
    if (time_without_control_left > 0)
    {
        has_control = false;
    }
    this->ejection_speed = ejection_speed;
    time_ejection_left = time_without_control / 2;
}

int Entity::get_damage_attack() const { return damage_attack; }
int Entity::get_damage_dash() const { return damage_dash; }
int Entity::get_damage_jump() const { return damage_jump; }
b2Vec2 Entity::get_speed() const { return body->GetLinearVelocity(); }
bool Entity::get_is_fall_attacking() const { return is_fall_attacking; }
bool Entity::get_is_dashing() const { return is_dashing; }
int Entity::get_jump_stun() const { return jump_stun; }
int Entity::get_attack_stun() const { return attack_stun; }
int Entity::get_dash_stun() const { return dash_stun; }

void Entity::jump(bool world_jump_rule, bool input_jump, float32 &current_vspeed) {
    if (world_jump_rule)
    {
        do_jump(input_jump, current_vspeed);
    }
    else {
        is_fall_attacking = false;
    }
}
