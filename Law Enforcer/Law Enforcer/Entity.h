//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_ENTITY_H
#define LAW_ENFORCER_ENTITY_H

#include "pch.h"
#include "LevelObject.h"

class Entity : public LevelObject {
protected:
    int pvmax;
    int pv;
    b2FixtureDef fixtureDef;
    // TODO sprites (animation compatible)
public:
    Entity(b2Vec2 coordonnees, int pvmax);
    Entity(pugi::xml_node node);
};


#endif //LAW_ENFORCER_ENTITY_H
