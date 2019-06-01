//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_PLATFORM_H
#define LAW_ENFORCER_PLATFORM_H

#include "LevelObject.h"

class Platform : public LevelObject {
private:
    sf::Image sprite;
public:
    Platform(pugi::xml_node node);
    virtual void draw(sf::RenderWindow &window) override;
};


#endif //LAW_ENFORCER_PLATFORM_H
