//
// Created by mad on 01/06/19.
//

#include "LevelObject.h"
#include "global_definitions.h"

LevelObject::LevelObject(b2Vec2 coordonnees):
    coordonnees(coordonnees),
    coordonnees_sfml(convert_coords(this->coordonnees))
{
}

b2Vec2 LevelObject::get_coordinates() const { return body->GetPosition(); }
