//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_LEVEL_H
#define LAW_ENFORCER_LEVEL_H

#include "pch.h"
#include <vector>
#include "Platform.h"
#include "Player.h"
#include "Inputs.h"

class Level {
private:
    std::vector<Platform> platforms;
    b2World world;
    Player player;
    Inputs inputs;
public:
    Level();
    Level(std::string xml_file_path);
    void draw(sf::RenderWindow &window);
    void update(sf::Event event);
};


#endif //LAW_ENFORCER_LEVEL_H
