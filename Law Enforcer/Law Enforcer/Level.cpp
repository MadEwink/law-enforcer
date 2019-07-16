//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include <iostream>
#include "Level.h"

Level::Level(pugi::xml_node node) :
    world({node.child("World").child("gravity").attribute("x").as_float(0),
           node.child("World").child("gravity").attribute("y").as_float(0)}),
    player(world, node.child("Player")),
    boss(world, node.child("Boss")),
    lcl(&player, &boss)
{
    for (auto i : node.child("Platforms").children()) {
        platforms.emplace_back(Platform(world, i));
        platforms.emplace_back(Platform(world, {0, 0.1 - WORLD_HEIGHT / 2.0}, {WORLD_WIDTH / 2.0, 0.1}, 1));
    }
    world.SetContactListener(&lcl);
    worldRules.jump = node.child("World").child("rules").attribute("jump").as_bool(true);
    worldRules.dash = node.child("World").child("rules").attribute("dash").as_bool(true);
    worldRules.attack = node.child("World").child("rules").attribute("attack").as_bool(true);
}

Level::Level() :
    world({0.0f, -20.0f}),
    player(world,{-3,1},10),
    boss(world, {2, 4}, 10, 5, 5, 5, 1, 15, 60, 60, 10),
    lcl(&player, &boss)
{
    platforms.emplace_back(Platform(world, {0, 0.1 - WORLD_HEIGHT / 2.0}, {WORLD_WIDTH / 2.0, 0.1}, 1));
    platforms.emplace_back(Platform(world, {0.1 - WORLD_WIDTH / 2.0, 0}, {0.1, WORLD_HEIGHT / 2.0}, 0));
    platforms.emplace_back(Platform(world, {WORLD_WIDTH / 2.0 - 0.1, 0}, {0.1, WORLD_HEIGHT / 2.0}, 0));
    platforms.emplace_back(Platform(world, {-WORLD_WIDTH*2.0/10.0,-WORLD_HEIGHT/8.0-0.2}, {WORLD_WIDTH/10.0,0.1}, 0));
    platforms.emplace_back(Platform(world, {WORLD_WIDTH*2.0/10.0,-WORLD_HEIGHT/8.0-0.2}, {WORLD_WIDTH/10.0,0.1}, 0));
    world.SetContactListener(&lcl);
    worldRules.jump = true;
    worldRules.attack = true;
    worldRules.dash = true;
}

void Level::draw(sf::RenderWindow &window) {
    for (Platform platform : platforms)
    {
        platform.draw(window);
    }
    player.draw(window);
    boss.draw(window);
}

void Level::update(sf::Event event) {
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 100;
    int32 positionIterations = 50;
    world.Step(timeStep, velocityIterations, positionIterations);
    inputs.update(event);
    update_world_rules();
    player.update(inputs, worldRules);
    boss.update(inputs, worldRules);
}

void Level::update_world_rules() {
    if (inputs.get_pressed(modifier))
    {
        if (inputs.get_pressed(jump) && inputs.get_this_frame(jump))
        {
            worldRules.jump = !worldRules.jump;
        }
        else if (inputs.get_pressed(dash) && inputs.get_this_frame(dash))
        {
            worldRules.dash = !worldRules.dash;
        }
        else if (inputs.get_pressed(attack) && inputs.get_this_frame(attack))
        {
            worldRules.attack = !worldRules.attack;
        }
    }
}