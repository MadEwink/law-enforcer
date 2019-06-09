//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_PLAYER_H
#define LAW_ENFORCER_PLAYER_H

#include "pch.h"
#include "Entity.h"
#include "Inputs.h"

class Player : public Entity {
private:
    int jump_time_left;
    int jump_time_max;
public:
    Player();
    Player(b2World &world, b2Vec2 coordonnees, int pvmax);
    void draw(sf::RenderWindow &window) override;
    void update(const Inputs &inputs) override;
};


#endif //LAW_ENFORCER_PLAYER_H
