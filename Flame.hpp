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
        Flame(sf::Texture &flameTexture, sf::Texture &laurentTexture, int x, int y){
            if (rand() % 10 == 0) {
                flame.setTexture(laurentTexture);
                isLaurent = true;
            } else {
                flame.setTexture(flameTexture);
            }
            flame.setPosition(x, y);
            //flame.setScale(2.0f, 2.0f);
            this->x = x;
            this->y = y;
        };
        ~Flame(){};
        bool getIsLaurent() {
            return isLaurent;
        }

        sf::Sprite flame;
        sf::Clock clock;
        int x;
        int y;
        bool isLaurent = false;

        // void setScale(float scaleX, float scaleY) {
        //     flame.setScale(scaleX, scaleY);
        // }
};