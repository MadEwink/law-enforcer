//
// Created by mad on 01/06/19.
//

#include <iostream>
#include "Level.h"
#include "global_definitions.h"

Level::Level() :
    world({0.0f, -20.0f}),
    player(world,{0,0},50),
    pcl(&player)
{
    platforms.emplace_back(Platform(world, {0, 0.5 - WORLD_HEIGHT / 2.0}, {WORLD_WIDTH / 2.0, 0.5}, 1));
    platforms.emplace_back(Platform(world, {0.5 - WORLD_WIDTH / 2.0, 0}, {0.5, WORLD_HEIGHT / 2.0}, 0));
    platforms.emplace_back(Platform(world, {WORLD_WIDTH / 2.0 - 0.5, 0}, {0.5, WORLD_HEIGHT / 2.0}, 0));
    platforms.emplace_back(Platform(world, {-WORLD_WIDTH*2.0/10.0,-WORLD_HEIGHT/8.0}, {WORLD_WIDTH/10.0,0.1}, 0));
    platforms.emplace_back(Platform(world, {WORLD_WIDTH*2.0/10.0,-WORLD_HEIGHT/8.0}, {WORLD_WIDTH/10.0,0.1}, 0));
    world.SetContactListener(&pcl);
}

void Level::draw(sf::RenderWindow &window) {
    for (Platform platform : platforms)
    {
        platform.draw(window);
    }
    player.draw(window);
}

void Level::update(sf::Event event) {
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterations, positionIterations);
    inputs.update(event);
    player.update(inputs);
}