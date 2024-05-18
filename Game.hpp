/*
** EPITECH PROJECT, 2024
** jam-flammes
** File description:
** Game
*/

#pragma once
#include "Flame.hpp"
#include <cstdlib>
#include <vector>

class Position {
    public:
        Position(int x, int y) : x(x), y(y) {};
        ~Position(){};
        int x;
        int y;
};

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        void init();
        void update();
        void render();

        sf::RenderWindow window;
        sf::Sprite background;
        sf::Texture bgTexture;
        sf::Texture flameTexture;
        std::vector<Flame> flames;
        std::vector<Position> flamePossiblePositions;
};