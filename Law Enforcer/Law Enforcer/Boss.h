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
	int landing_time;
	int landing_time_left;
    void do_jump(bool input_jump, float32 &current_vspeed) override;
public:
    Boss(b2World &world, b2Vec2 coordonnees, int pvmax, int damage_attack, int damage_dash, int damage_jump,
         int damage_contact, int attack_stun, int dash_stun, int jump_stun, int dash_speed);
    Boss(b2World &world, pugi::xml_node node);
    void draw(sf::RenderWindow &window) override;
    void update(const Inputs &inputs, WorldRules &worldRules) override;
	void setJump(bool) override;
    void dash(bool world_dash_rule, bool input_dash, b2Vec2& current_speed) override;
    void random_move(float32 &current_hspeed);
    int get_damage_contact() const;
};


#endif //LAW_ENFORCER_BOSS_H
