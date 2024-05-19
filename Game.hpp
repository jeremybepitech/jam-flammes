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
#include <fstream>

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

    struct ScoreEntry {
        std::string name;
        int score;
    };
        void init();
        void update();
        void render();
        void displayLost();
        void checkFlameClick(const sf::Vector2i& mousePos);
        void displayMenu();
        void loadHighScores();
        void saveHighScores();

        sf::RenderWindow window;
        sf::Clock gameClock;
        sf::Sprite background;
        sf::Sprite menu;
        sf::Texture bgTexture;
        sf::Texture menuTexture;
        sf::Texture flameTexture;
        sf::Texture laurentTexture;
        std::vector<Flame> flames;
        std::vector<Position> flamePossiblePositions;
        sf::Texture medalTexture;
        sf::Music menuMusic; // Ajout de la musique d'ambiance
        sf::Music gameMusic; // Ajout de la musique d'ambiance
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
        std::string playerName;
        std::vector<ScoreEntry> highScores;
};