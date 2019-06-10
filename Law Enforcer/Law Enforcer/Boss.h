//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_BOSS_H
#define LAW_ENFORCER_BOSS_H

#include "Entity.h"

#define BOSS_SIZE 0.8f

class Boss : public Entity {
protected:
    int damage_contact;
public:
    Boss(b2World &world, b2Vec2 coordonnees, int pvmax, int damage_attack, int damage_dash, int damage_jump,
         int damage_contact, int attack_stun, int dash_stun, int jump_stun);
    void draw(sf::RenderWindow &window) override;
    void update(const Inputs &inputs, WorldRules &worldRules) override;
    float32 jump(bool world_jump_rule, bool input_jump, float32 current_vspeed) override;
    void random_move(float32 &current_hspeed);
    int get_damage_contact() const;
};


#endif //LAW_ENFORCER_BOSS_H
