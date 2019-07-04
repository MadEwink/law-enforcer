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
#include "LevelContactListener.h"

class Level {
private:
    std::vector<Platform> platforms;
    b2World world;
    Player player;
    Boss boss;
    Inputs inputs;
    LevelContactListener lcl;
    WorldRules worldRules;
public:
    Level();
    Level(std::string xml_file_path);
	//void setJump(bool) override;
    void draw(sf::RenderWindow &window);
    void update(sf::Event event);
    void update_world_rules();
};


#endif //LAW_ENFORCER_LEVEL_H
