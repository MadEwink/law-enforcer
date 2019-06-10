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
    b2Fixture *fPlayerHurtSensor = nullptr;
    b2Fixture *fPlayerJumpHitbox = nullptr;
    b2Fixture *fPlayerDashHitboxLeft = nullptr;
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
    } else if (contact->GetFixtureA()->GetUserData() == (void*)player_hurtbox)
    {
        fPlayerHurtSensor = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)player_hurtbox)
    {
        fPlayerHurtSensor = contact->GetFixtureB();
        other = contact->GetFixtureA();
    } else if (contact->GetFixtureA()->GetUserData() == (void*)player_jump_hitbox)
    {
        fPlayerJumpHitbox = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)player_jump_hitbox)
    {
        fPlayerJumpHitbox = contact->GetFixtureB();
        other = contact->GetFixtureA();
    } else if (contact->GetFixtureA()->GetUserData() == (void*)player_dash_hitbox_left)
    {
        fPlayerDashHitboxLeft = contact->GetFixtureA();
        other = contact->GetFixtureB();
    } else if (contact->GetFixtureB()->GetUserData() == (void*)player_dash_hitbox_left)
    {
        fPlayerDashHitboxLeft = contact->GetFixtureB();
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
        if (other != nullptr && other->GetUserData() == (void*)plateform_groundbox)
        {
            boss->setJump(true);
        }
    }
    if (fPlayerJumpHitbox != nullptr && player->get_is_fall_attacking() && other != nullptr && other->GetUserData() == (void*)boss_hurtbox)
    {
        // player hit boss by jumping
        printf("Player attacks Boss\n");
        b2Vec2 player_rebounce_speed(0, player->get_coordinates().y - boss->get_coordinates().y);
        player_rebounce_speed *= 5;
        player->take_damage(0, boss->get_jump_stun()/2, player_rebounce_speed);
        boss->take_damage(player->get_damage_jump(), boss->get_jump_stun(), -player_rebounce_speed);
    } else if (fPlayerDashHitboxLeft != nullptr && player->get_is_dashing() && other != nullptr && other->GetUserData() == (void*)boss_hurtbox)
    {
        //player hit box by dashing
        printf("Player attacks Boss\n");
        b2Vec2 player_rebounce_speed(player->get_coordinates().x - boss->get_coordinates().x, 0);
        player_rebounce_speed *= 5;
        player->take_damage(0, boss->get_dash_stun()/2, player_rebounce_speed);
        boss->take_damage(player->get_damage_dash(), boss->get_dash_stun(), -player_rebounce_speed);
    }
    else if (fPlayerHurtSensor != nullptr)
    {
        if (other != nullptr && other->GetUserData() == (void*)boss_contact_hitbox)
        {
            // boss hit player by contact
            printf("Boss attacks Player\n");
            b2Vec2 eject_speed;
            eject_speed = (player->get_coordinates() - boss->get_coordinates());
            eject_speed *= 5;
            player->take_damage(boss->get_damage_contact(), player->get_contact_stun(), eject_speed);
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
        if (other != nullptr && other->GetUserData() == (void*)plateform_groundbox)
        {
            boss->setJump(false);
        }
    }
}