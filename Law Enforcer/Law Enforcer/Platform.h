//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_PLATFORM_H
#define LAW_ENFORCER_PLATFORM_H

#include "LevelObject.h"
#include "Inputs.h"

class Platform : public LevelObject {
private:
    b2Vec2 size;
    sf::Sprite sprite;
public:
    Platform(b2World &world, b2Vec2 coordonnees, b2Vec2 size, float32 friction);
    Platform(pugi::xml_node node);
    void draw(sf::RenderWindow &window) override;
    void update(const Inputs &inputs) override;
};


#endif //LAW_ENFORCER_PLATFORM_H
