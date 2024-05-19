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
    laurentTexture.loadFromFile("laurent.png");
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
    flames.push_back(Flame(flameTexture, laurentTexture, flamePossiblePositions[i].x, flamePossiblePositions[i].y));
}

void Game::displayLost()
{
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Score: " << score << std::endl;
            this->window.close();
        }
    }
    sf::Font font;
    if (!font.loadFromFile("SegaSonic.TTF")) {
        // Gérer l'erreur de chargement de la police
    }
    sf::Text lostText;
    lostText.setFont(font);
    lostText.setString("Vous avez perdu !\n" + std::to_string(score) + " points");
    lostText.setCharacterSize(20); // Taille du texte
    lostText.setFillColor(sf::Color::Green); // Couleur du texte
    lostText.setPosition(260, 400); // Position du texte dans la fenêtre
    sf::Sprite medal;
    medal.setTexture(medalTexture);
    medal.setPosition(320, 500);
    this->window.clear();
    this->window.draw(background);
    this->window.draw(lostText);
    this->window.draw(medal);
    this->window.display();
}

void Game::run()
{
    while (this->window.isOpen()) {
        if (isLost) {
            displayLost();
        } else {
            this->update();
            this->render();
        }
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
            flames.push_back(Flame(flameTexture, laurentTexture, flamePossiblePositions[j].x, flamePossiblePositions[j].y));
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
    if (gameClock.getElapsedTime().asSeconds() > 0.5) {
        float currentWidth = progressBar.getSize().x;
        currentWidth += 40 * progressSpeed;
        if (currentWidth > 726) {
            isLost = true;
            if (score > 300) {
                medalTexture.loadFromFile("gold.png");
            } else if (score > 150) {
                medalTexture.loadFromFile("silver.png");
            } else {
                medalTexture.loadFromFile("bronze.png");
            }
        }
        if (currentWidth > 240)
            progressBar.setFillColor(sf::Color::Yellow);
        if (currentWidth > 480)
            progressBar.setFillColor(sf::Color::Red);
        progressBar.setSize(sf::Vector2f(currentWidth, 20));
        gameClock.restart();
    }
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
    this->window.display();
}

// Vérification si la souris est sur une flamme
void Game::checkFlameClick(const sf::Vector2i& mousePos)
{
    for (long unsigned i = 0; i < flames.size(); i++) {
        if (flames[i].flame.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            flames.erase(flames.begin() + i);

            float currentWidth = progressBar.getSize().x;
            if (flames[i].getIsLaurent()) {
                currentWidth += 50 * progressSpeed;
                score -= 20;
            } else {
                currentWidth -= 50 * progressSpeed;
                score += 10;
            }
            if (currentWidth < 0) {
                currentWidth = 0;
            }
            progressBar.setSize(sf::Vector2f(currentWidth, 20));
            progressSpeed += 0.1f;


            clickSound.play();
            isSoundPlaying = true;
            soundClock.restart();
            int j = rand() % 9;
            flames.push_back(Flame(flameTexture, laurentTexture, flamePossiblePositions[j].x, flamePossiblePositions[j].y));
        }
    }
}