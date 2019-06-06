//
// Created by mad on 01/06/19.
//
#pragma once

#ifndef LAW_ENFORCER_LEVEL_H
#define LAW_ENFORCER_LEVEL_H


#include <vector>
#include "Platform.h"
#include "Player.h"

class Level {
private:
    std::vector<Platform> platforms;
    Player player;
    b2World world;
public:
    Level();
    Level(std::string xml_file_path);
    void draw(sf::RenderWindow &window);
    void update();
};


#endif //LAW_ENFORCER_LEVEL_H
