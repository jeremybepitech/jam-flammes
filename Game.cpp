/*
** EPITECH PROJECT, 2024
** jam-flammes
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    srand(time(NULL));
    this->init();
}

Game::~Game()
{
}

void Game::init()
{
    this->window.create(sf::VideoMode(726, 980), "Jam Flammes");
    bgTexture.loadFromFile("background.png");
    background.setTexture(bgTexture);
    flameTexture.loadFromFile("flame.png");

    flamePossiblePositions.push_back(Position(80, 250));
    flamePossiblePositions.push_back(Position(80, 550));
    flamePossiblePositions.push_back(Position(80, 800));
    flamePossiblePositions.push_back(Position(340, 170));
    flamePossiblePositions.push_back(Position(340, 550));
    flamePossiblePositions.push_back(Position(340, 800));
    flamePossiblePositions.push_back(Position(630, 250));
    flamePossiblePositions.push_back(Position(630, 550));
    flamePossiblePositions.push_back(Position(630, 800));

    int i = rand() % 9;
    flames.push_back(Flame(flameTexture, flamePossiblePositions[i].x, flamePossiblePositions[i].y));
}

void Game::run()
{
    while (this->window.isOpen()) {
        this->update();
        this->render();
    }
}

void Game::update()
{
    sf::Event event;
    for (long unsigned i = 0; i < flames.size(); i++) {
        if (flames[i].clock.getElapsedTime().asSeconds() > 1) {
            flames.erase(flames.begin() + i);
            int j = rand() % 9;
            flames.push_back(Flame(flameTexture, flamePossiblePositions[j].x, flamePossiblePositions[j].y));
        }
    }
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window.close();
    }
}

void Game::render()
{
    this->window.clear();
    this->window.draw(background);
    for (long unsigned i = 0; i < flames.size(); i++) {
        this->window.draw(flames[i].flame);
    }
    this->window.display();
}