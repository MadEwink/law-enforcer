//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_PLATFORM_H
#define LAW_ENFORCER_PLATFORM_H

#include "LevelObject.h"

class Platform : public LevelObject {
private:
    float32 size;
    sf::Sprite sprite;
public:
    Platform(b2Vec2 coordonnees, float32 size);
    Platform(pugi::xml_node node);
    void draw(sf::RenderWindow &window) override;
    void update() override;
};


#endif //LAW_ENFORCER_PLATFORM_H
