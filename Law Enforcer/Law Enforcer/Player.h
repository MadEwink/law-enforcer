//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_PLAYER_H
#define LAW_ENFORCER_PLAYER_H


#include "Entity.h"
#include "Inputs.h"

class Player : public Entity {
private:
    int jump_time_left;
    int jump_time_max;
    int max_speed;
    int jump_speed;
    int contact_stun;
	enum SpriteState anim;
    void do_jump(bool input_jump, float32 &current_vspeed) override;
public:
    Player(b2World &world, b2Vec2 coordonnees, int pvmax);
    void draw(sf::RenderWindow &window) override;
    void update(const Inputs &inputs, WorldRules &worldRules) override;
	//void setJump(bool) override;
    void dash(bool world_dash_rule, bool input_dash, b2Vec2& current_speed) override;
    int get_contact_stun() const;
};

enum SpriteState {
	player_idle,
	player_walk,
	player_jump,
	player_fall,
	player_dash,
	player_attack,
	player_hurt
};

#endif //LAW_ENFORCER_PLAYER_H
