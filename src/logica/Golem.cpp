#include "../../include/logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include "assetManager.h"
/* texturaQuieto.loadFromMemory("../assets/JugadorGolem/estado-reposo/JGT.png");
    texturaMovLados.loadFromMemory("../assets/JugadorGolem/estado-moviendose-lados/JGML.png");
    texturaMovAbajo.loadFromMemory("../assets/JugadorGolem/estado-moviendose-abajo/JGMA.png");
    texturaMovArriba.loadFromMemory("../assets/JugadorGolem/estado-moviendose-arriba/JGMUp.png"); */

Golem::Golem(float pInicialX, float pInicialY) {
    texturaQuieto.loadFromMemory(JGT_png, JGT_png_len);
    texturaMovLados.loadFromMemory(JGML_png, JGML_png_len);
    texturaMovAbajo.loadFromMemory(JGMA_png, JGMA_png_len);
    texturaMovArriba.loadFromMemory(JGMUp_png, JGMUp_png_len);

    sprite.setTexture(texturaQuieto);
    sprite.setPosition(pInicialX, pInicialY);
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
    sprite.setScale(3, 3);
    sprite.setTextureRect(sf::IntRect(1 * frameWidth, 0, frameWidth, frameHeight));
}

void Golem::update(sf::VideoMode desktopMode) {
    // Movimiento y animación
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.setTexture(texturaMovArriba);
        sprite.setScale(3, 3);
        tFrames = 10;
        if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion) {
            currentFrame = (currentFrame + 1) % tFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            relojAnimacion.restart();
        }
        sprite.move(0, -velocidad);
        posicionY -= velocidad;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.setTexture(texturaMovLados);
        sprite.setScale(-3, 3);
        tFrames = 12;
        if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion) {
            currentFrame = (currentFrame + 1) % tFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            relojAnimacion.restart();
        }
        sprite.move(-velocidad, 0);
        posicionX -= velocidad;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.setTexture(texturaMovLados);
        sprite.setScale(3, 3);
        tFrames = 12;
        if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion) {
            currentFrame = (currentFrame + 1) % tFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            relojAnimacion.restart();
        }
        sprite.move(velocidad, 0);
        posicionX += velocidad;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.setTexture(texturaMovAbajo);
        sprite.setScale(3, 3);
        tFrames = 10;
        if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion) {
            currentFrame = (currentFrame + 1) % tFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            relojAnimacion.restart();
        }
        sprite.move(0, velocidad);
        posicionY += velocidad;
    } else {
        sprite.setTexture(texturaQuieto);
        sprite.setScale(3, 3);
        tFrames = 6;
        if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion) {
            currentFrame = (currentFrame + 1) % tFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            relojAnimacion.restart();
        }
    }

    // --- LÍMITES DE MOVIMIENTO ---
    float limiteSuperior = desktopMode.height * 0.35f;

    if ((sprite.getPosition().x - sprite.getGlobalBounds().width / 2.f) < 0) {
        sprite.setPosition(sprite.getGlobalBounds().width / 2.f, sprite.getPosition().y);
    }
    else if ((sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f) > desktopMode.width) {
        sprite.setPosition(desktopMode.width - sprite.getGlobalBounds().width / 2.f, sprite.getPosition().y);
    }
    else if ((sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f) > desktopMode.height) {
        sprite.setPosition(sprite.getPosition().x, desktopMode.height - sprite.getGlobalBounds().height / 2.f);
    }
    else if ((sprite.getPosition().y - sprite.getGlobalBounds().height / 2.f) < limiteSuperior) {
        sprite.setPosition(sprite.getPosition().x, limiteSuperior + sprite.getGlobalBounds().height / 2.f);
    }
}

void Golem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

sf::FloatRect Golem::getBounds() const {
    return sprite.getGlobalBounds();
}

void Golem::setPosition(int x, int y) {
    sprite.setPosition(x, y);
}

int Golem::getFramewidth() {
    return frameWidth;
}

int Golem::getFrameHeight() {
    return frameHeight;
}

int Golem::getCurrentFrame() {
    return currentFrame;
}

void Golem::setCurrentFrame(int x) {
    currentFrame = x;
}

int Golem::totalFrames() {
    return tFrames;
}
