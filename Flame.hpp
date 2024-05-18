/*
** EPITECH PROJECT, 2024
** jam-flammes
** File description:
** Flame
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class Flame {
    public:
        Flame(sf::Texture &flameTexture, int x, int y){
            flame.setTexture(flameTexture);
            flame.setPosition(x, y);
            this->x = x;
            this->y = y;
        };
        ~Flame(){};

        sf::Sprite flame;
        sf::Clock clock;
        int x;
        int y;
};