//
// Created by mad on 02/06/19.
//

#include "pch.h"
#include "global_definitions.h"

sf::Vector2f convert_coords(b2Vec2 coordonnees_b2d, int offset_x, int offset_y){
    float x = SCREEN_WIDTH/2 + coordonnees_b2d.x*PIXELS_BY_METER + offset_x;
    float y = SCREEN_HEIGHT/2 - coordonnees_b2d.y*PIXELS_BY_METER + offset_y;
    return {x,y};
}