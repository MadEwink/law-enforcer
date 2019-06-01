//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_INPUTS_H
#define LAW_ENFORCER_INPUTS_H

#include <map>
#include <SFML/Window/Keyboard.hpp>

typedef enum {
    left,
    right,
    jump,
    dash,
    attack,
    pause
}action_key;

class Inputs {
private:
    std::map<action_key, bool> is_pressed;
    std::map<sf::Keyboard, action_key> key_map;
};


#endif //LAW_ENFORCER_INPUTS_H
