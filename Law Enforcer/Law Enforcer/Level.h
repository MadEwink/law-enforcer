//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_LEVEL_H
#define LAW_ENFORCER_LEVEL_H


#include <vector>
#include "Platform.h"

class Level {
private:
    std::vector<Platform> platforms;
public:
    Level();
    Level(std::string xml_file_path);
    void draw(sf::RenderWindow &window);
};


#endif //LAW_ENFORCER_LEVEL_H
