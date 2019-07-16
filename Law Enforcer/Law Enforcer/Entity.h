//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_ENTITY_H
#define LAW_ENFORCER_ENTITY_H

#include "LevelObject.h"
#include "Inputs.h"

class Entity : public LevelObject {
protected:
    int pvmax;
    int pv;
    bool can_jump;
    bool has_control;
    int time_without_control_left;
    int jump_speed;
    b2Vec2 ejection_speed;
    int time_ejection_left;
    // TODO sprites (animation compatible)
	sf::Texture sheet;
	sf::Sprite sprite;
    int damage_attack;
    int damage_dash;
    int damage_jump;
    int jump_stun;
    int dash_stun;
    int attack_stun;
    int dash_speed;
    bool is_fall_attacking;
    bool is_dashing;
    bool is_facing_right;
    virtual void do_jump(bool input_jump, float32 &current_vspeed) = 0;
public:
    Entity(b2Vec2 coordonnees, int pvmax, int damage_attack, int damage_dash, int damage_jump, int attack_stun,
           int dash_stun, int jump_stun, int dash_speed, int jump_speed);
    Entity(b2World &world, pugi::xml_node node);
    virtual void dash(bool world_dash_rule, bool input_dash, b2Vec2& current_speed) = 0;
    //virtual void dash(bool world_dash_rule) = 0;
    //virtual void attack(bool world_attack_rule) = 0;
    virtual void setJump(bool);
    virtual void take_damage(int damage, int time_without_control, b2Vec2 ejection_speed);
    int get_damage_attack() const;
    int get_damage_dash() const;
    int get_damage_jump() const;
    b2Vec2 get_speed() const;
    bool get_is_fall_attacking() const;
    bool get_is_dashing() const;
    int get_jump_stun() const;
    int get_attack_stun() const;
    int get_dash_stun() const;
    void jump(bool world_jump_rule, bool input_jump, float32 &current_vspeed);
};


#endif //LAW_ENFORCER_ENTITY_H
