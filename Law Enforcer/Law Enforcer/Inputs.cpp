//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Inputs.h"

Inputs::Inputs()
{
    for (int key = 0 ; key < NB_ACTION_KEY ; key++)
    {
        is_pressed[key] = false;
    }
    key_map[sf::Keyboard::Left] = left;
    key_map[sf::Keyboard::Right] = right;
    key_map[sf::Keyboard::Space] = jump;
    key_map[sf::Keyboard::Up] = jump;
}

void Inputs::update(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        for (const auto &i : key_map)
        {
            if (i.first == event.key.code) is_pressed[i.second] = true;
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        for (const auto &i : key_map)
        {
            if (i.first == event.key.code) is_pressed[i.second] = false;
        }
    }
}

bool Inputs::get_pressed(action_key key) const { return is_pressed[key]; }