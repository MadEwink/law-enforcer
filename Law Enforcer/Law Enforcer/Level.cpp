//
// Created by mad on 01/06/19.
//

#include <iostream>
#include "Level.h"

Level::Level() :
    world({0.0f, -9.8f})/*,
    player(this->world,{-1,-2},50)*/
{
    Platform random_platform(world, {-1, -1}, {3,1});
    platforms.emplace_back(random_platform);
    platforms.emplace_back(Platform(world, {1, -3}, {2,1}));
    player = *(new Player(world, {0,0}, 50));
}

void Level::draw(sf::RenderWindow &window) {
    for (Platform platform : platforms)
    {
        platform.draw(window);
    }
    player.draw(window);
}

void Level::update() {
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterations, positionIterations);
    player.update();
}