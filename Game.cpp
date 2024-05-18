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

// Initialisation des textures et des positions possibles des flammes
void Game::init()
{
    this->window.create(sf::VideoMode(726, 980), "Jam Flammes");
    bgTexture.loadFromFile("background.png");
    background.setTexture(bgTexture);
    flameTexture.loadFromFile("flame.png");
    clickBuffer.loadFromFile("click.wav");
    clickSound.setBuffer(clickBuffer);

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

// Gestion des événements et des flammes
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
        if (event.type == sf::Event::Closed) {
            std::cout << "Score: " << score << std::endl;
            this->window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    checkFlameClick(mousePos);
            }
        }
    }
    if (isSoundPlaying && soundClock.getElapsedTime().asSeconds() >= 0.5f) {
        clickSound.stop();
        isSoundPlaying = false;
    }
}

void Game::render()
{
    this->window.clear();
    this->window.draw(background);
    for (long unsigned i = 0; i < flames.size(); i++) {
        this->window.draw(flames[i].flame);
    }
    // sf::Text scoreText;
    // sf::Font font;
    // if (!font.loadFromFile("Roboto-Medium.ttf")) {
    //     // Gérer l'erreur de chargement de la police
    // }
    // scoreText.setFont(font);
    // scoreText.setString("Score: " + std::to_string(score));
    // scoreText.setCharacterSize(24); // Taille du texte
    // scoreText.setFillColor(sf::Color::White); // Couleur du texte
    // scoreText.setPosition(10, 10); // Position du texte dans la fenêtre
    this->window.display();
}

// Vérification si la souris est sur une flamme
void Game::checkFlameClick(const sf::Vector2i& mousePos)
{
    for (long unsigned i = 0; i < flames.size(); i++) {
        if (flames[i].flame.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            flames.erase(flames.begin() + i);
            score += 10;
            clickSound.play();
            isSoundPlaying = true;
            soundClock.restart();
            int j = rand() % 9;
            flames.push_back(Flame(flameTexture, flamePossiblePositions[j].x, flamePossiblePositions[j].y));
        }
    }
}