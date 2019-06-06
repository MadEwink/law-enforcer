//
// Created by mad on 01/06/19.
//
#pragma once

#ifndef LAW_ENFORCER_PLAYER_H
#define LAW_ENFORCER_PLAYER_H


#include "Entity.h"

class Player : public Entity {
private:
public:
    Player();
    Player(b2World &world, b2Vec2 coordonnees, int pvmax);
    void draw(sf::RenderWindow &window) override;
    void update() override;
};


#endif //LAW_ENFORCER_PLAYER_H
