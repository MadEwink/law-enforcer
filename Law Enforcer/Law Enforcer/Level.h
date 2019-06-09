//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_LEVEL_H
#define LAW_ENFORCER_LEVEL_H


#include <vector>
#include "global_definitions.h"
#include "Platform.h"
#include "Player.h"
#include "Inputs.h"
#include "PlayerContactListener.h"

class Level {
private:
    std::vector<Platform> platforms;
    b2World world;
    Player player;
    Inputs inputs;
    PlayerContactListener pcl;
    WorldRules worldRules;
public:
    Level();
    Level(std::string xml_file_path);
    void draw(sf::RenderWindow &window);
    void update(sf::Event event);
    void update_world_rules();
};


#endif //LAW_ENFORCER_LEVEL_H
