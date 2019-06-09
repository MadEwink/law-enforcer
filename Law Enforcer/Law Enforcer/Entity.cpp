//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Entity.h"

Entity::Entity(b2Vec2 coordonnees, int pvmax) :
    LevelObject(coordonnees),
    pvmax(pvmax),
    pv(pvmax)
{}
