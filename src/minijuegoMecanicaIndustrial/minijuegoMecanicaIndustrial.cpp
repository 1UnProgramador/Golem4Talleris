#include "../../include/logica/Juego.h"
#include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"

#include <vector>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>

minijuegoMecanicaIndustrial::minijuegoMecanicaIndustrial(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tPantalla.loadFromFile("../assets/minijuegoMecanicaIndustrial/pantalla.png");
    sPantalla.setTexture(tPantalla);
    sPantalla.setOrigin(sPantalla.getGlobalBounds().width / 2, sPantalla.getGlobalBounds().height / 2);
    sPantalla.setPosition(sf::VideoMode::getDesktopMode().width / 2, (sf::VideoMode::getDesktopMode().height / 2));
    sPantalla.setScale(9, 9);
    sPantalla.move(0, -1 * (sPantalla.getGlobalBounds().height));

    tCintas.loadFromFile("../assets/minijuegoMecanicaIndustrial/cintas.png");
    cintas.setTexture(tCintas);
    cintas.setOrigin(cintas.getGlobalBounds().width / 2, cintas.getGlobalBounds().height / 2);
    cintas.setScale(3, 3);
    cintas.setPosition(sPantalla.getPosition().x + 350, sPantalla.getPosition().y + (sPantalla.getGlobalBounds().height / 2) + (cintas.getGlobalBounds().height / 2) + 130);
    cintas.setTextureRect(sf::IntRect(0 * frameWidth, 0, frameWidth, frameHeight));

    cintas2.setTexture(tCintas);
    cintas2.setOrigin(cintas2.getGlobalBounds().width / 2, cintas2.getGlobalBounds().height / 2);
    cintas2.setScale(3, 3);
    cintas2.setPosition(cintas.getPosition().x + 324, cintas.getPosition().y);
    cintas2.setTextureRect(sf::IntRect(0 * frameWidth, 0, frameWidth, frameHeight));

    cintas3.setTexture(tCintas);
    cintas3.setOrigin(cintas3.getGlobalBounds().width / 2, cintas3.getGlobalBounds().height / 2);
    cintas3.setScale(3, 3);
    cintas3.setPosition(cintas2.getPosition().x + 324, cintas2.getPosition().y);
    cintas3.setTextureRect(sf::IntRect(0 * frameWidth, 0, frameWidth, frameHeight));

    cintas4.setTexture(tCintas);
    cintas4.setOrigin(cintas4.getGlobalBounds().width / 2, cintas4.getGlobalBounds().height / 2);
    cintas4.setScale(3, 3);
    cintas4.setPosition(cintas3.getPosition().x + 324, cintas3.getPosition().y);
    cintas4.setTextureRect(sf::IntRect(0 * frameWidth, 0, frameWidth, frameHeight));

    cintas5.setTexture(tCintas);
    cintas5.setOrigin(cintas5.getGlobalBounds().width / 2, cintas5.getGlobalBounds().height / 2);
    cintas5.setScale(3, 3);
    cintas5.setPosition(cintas4.getPosition().x + 324, cintas4.getPosition().y);
    cintas5.setTextureRect(sf::IntRect(0 * frameWidth, 0, frameWidth, frameHeight));

    cintas6.setTexture(tCintas);
    cintas6.setOrigin(cintas6.getGlobalBounds().width / 2, cintas6.getGlobalBounds().height / 2);
    cintas6.setScale(3, 3);
    cintas6.setPosition(cintas5.getPosition().x + 324, cintas5.getPosition().y);
    cintas6.setTextureRect(sf::IntRect(0 * frameWidth, 0, frameWidth, frameHeight));

    tPistonDesactivado.loadFromFile("../assets/minijuegoMecanicaIndustrial/pistonDesactivado.png");
    pistonDesactivado.setTexture(tPistonDesactivado);
    pistonDesactivado.setOrigin(pistonDesactivado.getGlobalBounds().width / 2, pistonDesactivado.getGlobalBounds().height / 2);
    pistonDesactivado.setPosition(sf::VideoMode::getDesktopMode().width / 2, (sf::VideoMode::getDesktopMode().height / 2));

    tPistonActivado.loadFromFile("../assets/minijuegoMecanicaIndustrial/pistonActivado.png");
    pistonActivado.setTexture(tPistonActivado);
    pistonActivado.setOrigin(pistonActivado.getGlobalBounds().width / 2, pistonActivado.getGlobalBounds().height / 2);
    pistonActivado.setPosition(pistonDesactivado.getPosition().x, pistonDesactivado.getPosition().y);

    std::vector<std::string> nombresPiezas = {"L", "T", "Z"};
    for (const auto& nombre : nombresPiezas) {
        Pieza p;
        p.tPiezas = std::make_shared<sf::Texture>();


        if (!p.tPiezas->loadFromFile("../assets/minijuegoMecanicaIndustrial/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        p.sPieza.setTexture(*p.tPiezas);
        p.sPieza.setOrigin(p.sPieza.getGlobalBounds().width / 2, p.sPieza.getGlobalBounds().height / 2);
        p.sPieza.setScale(0.7, 0.7);
        p.sPieza.setPosition(cintas.getPosition().x - 1107, cintas.getPosition().y);
        piezasBuenas.push_back(p);
    }
    std::vector<std::string> nombresPiezasM = {"LM", "TM", "ZM"};
    for (const auto& nombre : nombresPiezasM) {
        Pieza p;
        p.tPiezas = std::make_shared<sf::Texture>();


        if (!p.tPiezas->loadFromFile("../assets/minijuegoMecanicaIndustrial/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        p.sPieza.setTexture(*p.tPiezas);
        p.sPieza.setOrigin(p.sPieza.getGlobalBounds().width / 2, p.sPieza.getGlobalBounds().height / 2);
        p.sPieza.setScale(0.7, 0.7);
        p.sPieza.setPosition(cintas.getPosition().x - 1107, cintas.getPosition().y);
        piezasMalas.push_back(p);
    }
}
void minijuegoMecanicaIndustrial::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed) {
        if(evento.key.code == sf::Keyboard::Left){
            /* cintas4.move(-1, 0);
            std::cout << "Distancia: " << std::to_string(cintas4.getPosition().x - cintas3.getPosition().x) << std::endl; */
            piezasBuenas[0].sPieza.move(-1, 0);
            std::cout << "Distancia: " << std::to_string(cintas.getPosition().x - piezasBuenas[0].sPieza.getPosition().x);
        } else if(evento.key.code == sf::Keyboard::Right){
            piezasBuenas[0].sPieza.move(1, 0);
            std::cout << "Distancia: " << std::to_string(cintas.getPosition().x - piezasBuenas[0].sPieza.getPosition().x);
            /* cintas4.move(1, 0);
            std::cout << "Distancia: " << std::to_string(cintas4.getPosition().x - cintas3.getPosition().x) << std::endl; */
        } else if(evento.key.code == sf::Keyboard::Space){
            activado = true;
            for (auto &pieza : piezasGeneradas)
            {
                if(pieza.sPieza.getGlobalBounds().intersects(pistonActivado.getGlobalBounds())){
                    pieza.piezaGolpeada = true;
                }
            }

        }
    } else if(evento.type == sf::Event::KeyReleased){
        if(evento.key.code == sf::Keyboard::Space){
            activado = false;
        }
    }
}
void minijuegoMecanicaIndustrial::actualizar(){
    if (relojAnimacion.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
    if (relojAnimacion.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas2.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
    if (relojAnimacion.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas3.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
    if (relojAnimacion.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas4.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
    if (relojAnimacion.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas5.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
    if (relojAnimacion.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas6.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        relojAnimacion.restart();
    }

    if (relojPiezas.getElapsedTime().asSeconds() >= delayTime) {
        Pieza pieza;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);
        int numero = dist(gen);

        if(numero >= 1 && numero <= 3){
            pieza = piezasBuenas[numero];
        } else if (numero >= 4 && numero <= 6){
            pieza = piezasMalas[numero - 3];
        }
        piezasGeneradas.push_back(pieza);
        std::cout << "Pieza Creada";
        relojPiezas.restart();
    }
    int indice = 0;
    for (auto &pieza : piezasGeneradas)
    {
        if(pieza.piezaGolpeada){
            pieza.sPieza.move(0, velocidad * 2);
        } else {
            pieza.sPieza.move(velocidad, 0);
        }
        if(pieza.sPieza.getPosition().x > sf::VideoMode::getDesktopMode().width || pieza.sPieza.getPosition().y > sf::VideoMode::getDesktopMode().height){
            piezasGeneradas.erase(piezasGeneradas.begin() + indice);
            std::cout << "Pieza destruida";
        }
        indice++;
    }

}
void minijuegoMecanicaIndustrial::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(sPantalla);
    window.draw(cintas);
    window.draw(cintas2);
    window.draw(cintas3);
    window.draw(cintas4);
    window.draw(cintas5);
    window.draw(cintas6);
    if (activado){
        window.draw(pistonActivado);
    } else {
        window.draw(pistonDesactivado);
    }
    for (auto &pieza : piezasGeneradas)
    {
        window.draw(pieza.sPieza);
    }


}