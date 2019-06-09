//
// Created by mad on 09/06/19.
//

#ifndef LAW_ENFORCER_LEVELCONTACTLISTENER_H
#define LAW_ENFORCER_LEVELCONTACTLISTENER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include "Player.h"
#include "Boss.h"

class LevelContactListener : public b2ContactListener {
private:
    Player *player;
    Boss *boss;
public:
    LevelContactListener(Player *player, Boss *boss);
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};


#endif //LAW_ENFORCER_LEVELCONTACTLISTENER_H
