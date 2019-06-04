//
// Created by mad on 02/06/19.
//

#ifndef LAW_ENFORCER_GLOBAL_DEFINITIONS_H
#define LAW_ENFORCER_GLOBAL_DEFINITIONS_H

#include <SFML/System.hpp>
#include "Box2D/Common/b2Math.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PIXELS_BY_METER 80

sf::Vector2f convert_coords(b2Vec2 coordonnees_b2d, int offset_x=0, int offset_y=0);

#endif //LAW_ENFORCER_GLOBAL_DEFINITIONS_H
