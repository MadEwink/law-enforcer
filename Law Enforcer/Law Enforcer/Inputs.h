//
// Created by mad on 01/06/19.
//

#ifndef LAW_ENFORCER_INPUTS_H
#define LAW_ENFORCER_INPUTS_H

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

typedef enum {
    left,
    right,
    jump,
    dash,
    attack,
    pause,
    NB_ACTION_KEY
}action_key;

class Inputs {
private:
    bool is_pressed[NB_ACTION_KEY];
    std::map<sf::Keyboard::Key, action_key> key_map;
public:
    Inputs();
    void update(sf::Event event);
    bool get_pressed(action_key key) const;
};


#endif //LAW_ENFORCER_INPUTS_H
