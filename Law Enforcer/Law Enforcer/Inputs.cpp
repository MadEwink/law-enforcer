//
// Created by mad on 01/06/19.
//

#include "Inputs.h"

Inputs::Inputs()
{
    for (int key = 0 ; key < NB_ACTION_KEY ; key++)
    {
        is_pressed[key] = false;
        pressed_this_frame[key] = false;
    }
    key_map[sf::Keyboard::Left] = left;
    key_map[sf::Keyboard::Right] = right;
    key_map[sf::Keyboard::Up] = jump;
    key_map[sf::Keyboard::LShift] = modifier;
}

void Inputs::update(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        for (const auto &i : key_map)
        {
            //if (i.first == event.key.code)
            if (sf::Keyboard::isKeyPressed(i.first))
            {
                if (!is_pressed[i.second])
                    pressed_this_frame[i.second] = true;
                else
                    pressed_this_frame[i.second] = false;
                is_pressed[i.second] = true;
            }
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        for (const auto &i : key_map)
        {
            //if (i.first == event.key.code)
            if (!sf::Keyboard::isKeyPressed(i.first))
            {
                is_pressed[i.second] = false;
            }
        }
    }
}

bool Inputs::get_pressed(action_key key) const { return is_pressed[key]; }
bool Inputs::get_this_frame(action_key key) const { return  pressed_this_frame[key]; }