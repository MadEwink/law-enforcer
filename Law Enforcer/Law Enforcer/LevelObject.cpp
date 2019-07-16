//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "LevelObject.h"
#include "global_definitions.h"

LevelObject::LevelObject(pugi::xml_node node) :
    coordonnees({node.child("coordinates").attribute("x").as_float(0),
                 node.child("coordinates").attribute("y").as_float(0)}),
    coordonnees_sfml(convert_coords(this->coordonnees))
{}

LevelObject::LevelObject(b2Vec2 coordonnees):
    coordonnees(coordonnees),
    coordonnees_sfml(convert_coords(this->coordonnees))
{
}

b2Vec2 LevelObject::get_coordinates() const { return body->GetPosition(); }
