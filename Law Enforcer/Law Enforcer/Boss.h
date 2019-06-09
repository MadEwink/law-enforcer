//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_BOSS_H
#define LAW_ENFORCER_BOSS_H

#include "pch.h"
#include "Entity.h"

class Boss : public Entity {
protected:
    int damage_attack;
    int damage_dash;
    int damage_jump;
public:
};


#endif //LAW_ENFORCER_BOSS_H
