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
        // Initialisation de la barre de progression
    progressBarBackground.setSize(sf::Vector2f(726, 20));
    progressBarBackground.setFillColor(sf::Color::White);
    progressBarBackground.setPosition(0, 960);

    progressBar.setSize(sf::Vector2f(0, 20)); // Commence avec une largeur de 0
    progressBar.setFillColor(sf::Color::Green);
    progressBar.setPosition(0, 960);

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
    //float progress = score * progressSpeed / 50;
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

    // Mettre à jour la barre de progression
    float progress = score * progressSpeed;
    if (progress > 726) progress = 726; // Limiter la largeur à 726 pixels (taille de la fenêtre)
    progressBar.setSize(sf::Vector2f(progress, 20));
}

void Game::render()
{
    this->window.clear();
    this->window.draw(background);
    for (long unsigned i = 0; i < flames.size(); i++) {
        this->window.draw(flames[i].flame);
    }
    this->window.draw(progressBarBackground);
    this->window.draw(progressBar);

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

            float currentWidth = progressBar.getSize().x;
            currentWidth -= 50; // Diminuez de 50 pixels par clic (ajustez selon vos besoins)
            if (currentWidth < 0) {
                currentWidth = 0; // Empêcher la largeur de devenir négative
            }
            progressBar.setSize(sf::Vector2f(currentWidth, 20));
            progressSpeed += 0.1f;


            score += 10;
            clickSound.play();
            isSoundPlaying = true;
            soundClock.restart();
            int j = rand() % 9;
            flames.push_back(Flame(flameTexture, flamePossiblePositions[j].x, flamePossiblePositions[j].y));
        }
    }
}