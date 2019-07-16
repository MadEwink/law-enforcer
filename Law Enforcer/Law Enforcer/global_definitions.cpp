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

void loadFixture(b2Body* body, pugi::xml_node node)
{
    b2FixtureDef fixtureDef;
    fixtureDef.density = node.child("density").attribute("value").as_float(0);
    fixtureDef.friction = node.child("friction").attribute("value").as_float(0);
    fixtureDef.isSensor = node.child("isSensor").attribute("value").as_bool(false);
    fixtureDef.restitution = node.child("restitution").attribute("value").as_float(0);
    fixtureDef.userData = (void*)node.child("userData").attribute("value").as_int(0);
    if (node.child("shape").attribute("value").as_string("Rectangle") == "Circle")
    {
        b2CircleShape shape;
        shape.m_p = {node.child("position").attribute("x").as_float(0),
                     node.child("position").attribute("y").as_float(0)};
        shape.m_radius = {node.child("size").attribute("r").as_float(0)};
        fixtureDef.shape = &shape;
        body->CreateFixture(&fixtureDef);
    } else {
        b2PolygonShape shape;
        shape.SetAsBox(node.child("size").attribute("x").as_float(0),
                       node.child("size").attribute("y").as_float(0),
                       {node.child("position").attribute("x").as_float(0),
                        node.child("position").attribute("y").as_float(0)},0);
        fixtureDef.shape = &shape;
        body->CreateFixture(&fixtureDef);
    }
}

