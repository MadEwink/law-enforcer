//
// Created by mad on 08/06/19.
//

#include "PlayerContactListener.h"
#include "global_definitions.h"

PlayerContactListener::PlayerContactListener(Player *player) :
    player(player)
{}

void PlayerContactListener::BeginContact(b2Contact *contact) {
    b2Fixture *fFootSensor = nullptr;
    b2Fixture *other = nullptr;
    if (contact->GetFixtureA()->GetUserData() == (void*)e_footsensor)
    {
        fFootSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)e_footsensor)
    {
        fFootSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    }
    if (fFootSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)p_groundbox);
        {
            player->setJump(true);
        }
    }
}

void PlayerContactListener::EndContact(b2Contact *contact) {
    b2Fixture *fFootSensor = nullptr;
    b2Fixture *other = nullptr;
    if (contact->GetFixtureA()->GetUserData() == (void*)e_footsensor)
    {
        fFootSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)e_footsensor)
    {
        fFootSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    }
    if (fFootSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)e_groundbox);
        {
            player->setJump(false);
        }
    }
}