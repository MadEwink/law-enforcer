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
    bool can_jump;
    int max_speed;
    int jump_speed;
public:
    Player();
    Player(b2World &world, b2Vec2 coordonnees, int pvmax);
    void draw(sf::RenderWindow &window) override;
    void update(const Inputs &inputs) override;
    float32 jump(bool world_jump_rule, bool input_jump, float32 current_vspeed) override;
    void setJump(bool);
};


#endif //LAW_ENFORCER_PLAYER_H
