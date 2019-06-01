//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_ENTITY_H
#define LAW_ENFORCER_ENTITY_H

#include "LevelObject.h"

class Entity : public LevelObject {
protected:
    int pvmax;
    int pv;
    // *TODO* sprites (animation compatible)
public:
    Entity(pugi::xml_node node);
    virtual void draw(sf::RenderWindow &window) override;
};


#endif //LAW_ENFORCER_ENTITY_H
