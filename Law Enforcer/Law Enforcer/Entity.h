//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_ENTITY_H
#define LAW_ENFORCER_ENTITY_H

#include "LevelObject.h"
#include "Inputs.h"

class Entity : public LevelObject {
protected:
    int pvmax;
    int pv;
    bool can_jump;
    // TODO sprites (animation compatible)
public:
    Entity(b2Vec2 coordonnees, int pvmax);
    Entity(pugi::xml_node node);
    virtual float32 jump(bool world_jump_rule, bool input_jump, float32 current_vspeed) = 0;
    //virtual void dash(bool world_dash_rule) = 0;
    //virtual void attack(bool world_attack_rule) = 0;
    void setJump(bool);
};


#endif //LAW_ENFORCER_ENTITY_H
