//
// Created by mad on 08/06/19.
//

#ifndef LAW_ENFORCER_PLAYERCONTACTLISTENER_H
#define LAW_ENFORCER_PLAYERCONTACTLISTENER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "Player.h"

class PlayerContactListener : public b2ContactListener {
private:
    Player *player;
public:
    PlayerContactListener(Player *player);
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

};


#endif //LAW_ENFORCER_PLAYERCONTACTLISTENER_H
