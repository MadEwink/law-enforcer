//
// Created by mad on 02/06/19.
//

#ifndef LAW_ENFORCER_GLOBAL_DEFINITIONS_H
#define LAW_ENFORCER_GLOBAL_DEFINITIONS_H

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#define PIXELS_BY_METER 60.0

#define WORLD_WIDTH 13.0
#define WORLD_HEIGHT 10.0

#define SCREEN_WIDTH WORLD_WIDTH*PIXELS_BY_METER
#define SCREEN_HEIGHT WORLD_HEIGHT*PIXELS_BY_METER

enum {p_groundbox, e_groundbox, e_footsensor};

sf::Vector2f convert_coords(b2Vec2 coordonnees_b2d, int offset_x=0, int offset_y=0);

#endif //LAW_ENFORCER_GLOBAL_DEFINITIONS_H
