//
// Created by mad on 01/06/19.
//

#include <iostream>
#include "Level.h"

Level::Level() {
    Platform random_platform({-1,-1}, 3);
    platforms.emplace_back(random_platform);
    platforms.emplace_back(Platform({1,-3}, 2));
}

void Level::draw(sf::RenderWindow &window) {
    for (Platform platform : platforms)
    {
        platform.draw(window);
    }
}