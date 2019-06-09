//
// Created by mad on 01/06/19.
//

#include "Level.h"
#include "Inputs.h"
#include "Player.h"
#include "Entity.h"

Entity::Entity(b2Vec2 coordonnees, int pvmax) :
    LevelObject(coordonnees),
    pvmax(pvmax),
    pv(pvmax),
    can_jump(false)
{}

void Entity::setJump(bool jump) {
    can_jump = jump;
}