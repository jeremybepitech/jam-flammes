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
        void displayLost();
        void checkFlameClick(const sf::Vector2i& mousePos);

        sf::RenderWindow window;
        sf::Clock gameClock;
        sf::Sprite background;
        sf::Texture bgTexture;
        sf::Texture flameTexture;
        sf::Texture laurentTexture;
        std::vector<Flame> flames;
        std::vector<Position> flamePossiblePositions;
        sf::Texture medalTexture;
        // Score && bruit game
        int score = 0;
        sf::SoundBuffer clickBuffer;
        sf::Sound clickSound;
        sf::Clock soundClock;
        bool isSoundPlaying;
        sf::RectangleShape progressBarBackground; // Fond de la barre de progression
        sf::RectangleShape progressBar; // Barre de progression
        float progressSpeed = 0.1; // Vitesse de remplissage de la barre
        bool isLost = false;
};