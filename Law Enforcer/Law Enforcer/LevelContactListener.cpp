//
// Created by mad on 09/06/19.
//

#include "LevelContactListener.h"

LevelContactListener::LevelContactListener(Player *player, Boss *boss) :
        player(player),
        boss(boss)
{}

void LevelContactListener::BeginContact(b2Contact *contact) {
    b2Fixture *fPlayerFootSensor = nullptr;
    b2Fixture *fBossFootSensor = nullptr;
    b2Fixture *other = nullptr;
    if (contact->GetFixtureA()->GetUserData() == (void*)player_footsensor)
    {
        fPlayerFootSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)player_footsensor)
    {
        fPlayerFootSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    } else if (contact->GetFixtureA()->GetUserData() == (void*)boss_footsensor)
    {
        fBossFootSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)boss_footsensor)
    {
        fBossFootSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    }
    if (fPlayerFootSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)plateform_groundbox)
        {
            player->setJump(true);
        }
    }
    if (fBossFootSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)boss_footsensor)
        {
            boss->setJump(true);
        }
    }
}

void LevelContactListener::EndContact(b2Contact *contact) {
    b2Fixture *fPlayerFootSensor = nullptr;
    b2Fixture *fBossFootSensor = nullptr;
    b2Fixture *other = nullptr;
    if (contact->GetFixtureA()->GetUserData() == (void*)player_footsensor)
    {
        fPlayerFootSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)player_footsensor)
    {
        fPlayerFootSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    } else if (contact->GetFixtureA()->GetUserData() == (void*)boss_footsensor)
    {
        fBossFootSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)boss_footsensor)
    {
        fBossFootSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    }
    if (fPlayerFootSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)plateform_groundbox)
        {
            player->setJump(false);
        }
    }
    if (fBossFootSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)boss_footsensor)
        {
            boss->setJump(false);
        }
    }
}
