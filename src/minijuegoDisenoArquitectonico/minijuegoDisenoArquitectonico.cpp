#include "../../include/logica/Juego.h"
#include "../../include/minijuegoDisenoArquitectonico/minijuegoDisenoArquitectonico.h"
#include "../../include/pantallas/DisenoTecnico.h"

#include <vector>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>

minijuegoDisenoArquitectonico::minijuegoDisenoArquitectonico(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoDiseno.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tContorno.loadFromFile("../assets/minijuegoDisenoArquitectonico/contorno.png");
    contorno.setTexture(tContorno);
    contorno.setOrigin(contorno.getGlobalBounds().width / 2, contorno.getGlobalBounds().height / 2);
    contorno.setScale(4, 4);
    contorno.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);

    std::vector<std::string> nombresPiezasM = {"pieza1", "pieza2", "pieza3", "pieza4", "pieza5", "pieza6", "pieza7", "pieza8"};
    for (const auto& nombre : nombresPiezasM) {
        Pieza p;
        p.textura = std::make_shared<sf::Texture>();


        if (!p.textura->loadFromFile("../assets/minijuegoDisenoArquitectonico/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        p.sprite.setTexture(*p.textura);
        p.sprite.setOrigin(p.sprite.getGlobalBounds().width / 2, p.sprite.getGlobalBounds().height / 2);
        p.sprite.setScale(4, 4);
        /* p.sprite.setPosition(cintas.getPosition().x - 1107, cintas.getPosition().y); */
        piezas.push_back(p);
    }
    piezas[0].sprite.setPosition(contorno.getPosition().x - (contorno.getGlobalBounds().width / 2) - (piezas[0].sprite.getGlobalBounds().width / 2) - 150, contorno.getPosition().y - (contorno.getGlobalBounds().height / 2) - 150);
    piezas[0].posicionInicial = piezas[0].sprite.getPosition();
    piezas[0].posicionObjetivo = sf::Vector2f(contorno.getPosition().x + 66, contorno.getPosition().y + 64);

    piezas[1].sprite.setPosition(piezas[0].sprite.getPosition().x, piezas[0].sprite.getPosition().y + (piezas[0].sprite.getGlobalBounds().height / 2) + (piezas[1].sprite.getGlobalBounds().height / 2) + 100);
    piezas[1].posicionInicial = piezas[1].sprite.getPosition();
    piezas[1].posicionObjetivo = sf::Vector2f(contorno.getPosition().x + 98, contorno.getPosition().y + 128);

    piezas[2].sprite.setPosition(piezas[1].sprite.getPosition().x, piezas[1].sprite.getPosition().y + (piezas[1].sprite.getGlobalBounds().height / 2) + (piezas[2].sprite.getGlobalBounds().height / 2) + 100);
    piezas[2].posicionInicial = piezas[2].sprite.getPosition();
    piezas[2].posicionObjetivo = sf::Vector2f(contorno.getPosition().x - 94, contorno.getPosition().y + 160);

    piezas[3].sprite.setPosition(piezas[2].sprite.getPosition().x, piezas[2].sprite.getPosition().y + (piezas[2].sprite.getGlobalBounds().height / 2) + (piezas[3].sprite.getGlobalBounds().height / 2) + 100);
    piezas[3].posicionInicial = piezas[3].sprite.getPosition();
    piezas[3].posicionObjetivo = sf::Vector2f(contorno.getPosition().x - 94, contorno.getPosition().y + 64);


    piezas[4].sprite.setPosition(contorno.getPosition().x + (contorno.getGlobalBounds().width / 2) + (piezas[4].sprite.getGlobalBounds().width / 2) + 150, contorno.getPosition().y - (contorno.getGlobalBounds().height / 2) - 150);
    piezas[4].posicionInicial = piezas[4].sprite.getPosition();
    piezas[4].posicionObjetivo = sf::Vector2f(contorno.getPosition().x - 126, contorno.getPosition().y - 52);

    piezas[5].sprite.setPosition(piezas[4].sprite.getPosition().x, piezas[4].sprite.getPosition().y + (piezas[4].sprite.getGlobalBounds().height / 2) + (piezas[5].sprite.getGlobalBounds().height / 2) + 100);
    piezas[5].posicionInicial = piezas[5].sprite.getPosition();
    piezas[5].posicionObjetivo = sf::Vector2f(contorno.getPosition().x + 34, contorno.getPosition().y - 96);

    piezas[6].sprite.setPosition(piezas[5].sprite.getPosition().x, piezas[5].sprite.getPosition().y + (piezas[5].sprite.getGlobalBounds().height / 2) + (piezas[6].sprite.getGlobalBounds().height / 2) + 100);
    piezas[6].posicionInicial = piezas[6].sprite.getPosition();
    piezas[6].posicionObjetivo = sf::Vector2f(contorno.getPosition().x + 160, contorno.getPosition().y - 56);

    piezas[7].sprite.setPosition(piezas[6].sprite.getPosition().x, piezas[6].sprite.getPosition().y + (piezas[6].sprite.getGlobalBounds().height / 2) + (piezas[7].sprite.getGlobalBounds().height / 2));
    piezas[7].posicionInicial = piezas[7].sprite.getPosition();
    piezas[7].posicionObjetivo = sf::Vector2f(contorno.getPosition().x + 6.000061, contorno.getPosition().y + 128);


    if (juego->minijuegoFacil)
    {
        tolerancia = 50;
    } else {
        tolerancia = 5;
    }

    if (juego->minijuegoFacil)
    {
        tiempoInt = 40;
    } else {
        tiempoInt = 20;
    }


    fuente.loadFromFile("../assets/textos/Ubuntu-Bold.ttf");
    tiempo.setFont(fuente);
    tiempo.setScale(2, 2);
    tiempo.setPosition(0, 0);
    tiempoRestante.restart();
    tiempo.setString(std::to_string(tiempoInt));




}
void minijuegoDisenoArquitectonico::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::MouseButtonPressed) {
        if (evento.mouseButton.button == sf::Mouse::Left){
            for (auto &pieza : piezas)
            {
                if (pieza.sprite.getGlobalBounds().contains(posicionEnVentana) && !(pieza.posicionada))
                {
                    pieza.agarrada = true;
                }

            }

        }
    } else if(evento.type == sf::Event::MouseButtonReleased){
        if (evento.mouseButton.button == sf::Mouse::Left){
            for (auto &pieza : piezas)
            {
                float dX = std::abs(pieza.sprite.getPosition().x - pieza.posicionObjetivo.x);
                float dY = std::abs(pieza.sprite.getPosition().y - pieza.posicionObjetivo.y);
                if (dX <= tolerancia && dY <= tolerancia)
                {
                    pieza.sprite.setPosition(pieza.posicionObjetivo);
                    pieza.posicionada = true;
                } else {
                    pieza.sprite.setPosition(pieza.posicionInicial);
                }


                pieza.agarrada = false;
            }

        }
    } else if(evento.type == sf::Event::KeyPressed){
        if(evento.key.code == sf::Keyboard::Left){
            piezas[4].sprite.move(-1, 0);
        } else if(evento.key.code == sf::Keyboard::Up){
            piezas[4].sprite.move(0, -1);
        } else if(evento.key.code == sf::Keyboard::Right){
            piezas[4].sprite.move(1, 0);
        } else if(evento.key.code == sf::Keyboard::Down){
            piezas[4].sprite.move(0, 1);
        } else if(evento.key.code ==sf::Keyboard::Escape){
            juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
        }
        std::cout << "Posicion actual de la pieza: " << std::to_string(contorno.getPosition().x - piezas[4].sprite.getPosition().x) << ", " << std::to_string(contorno.getPosition().y - piezas[4].sprite.getPosition().y) << "." << std::endl;
    }
}
void minijuegoDisenoArquitectonico::actualizar(){
    tiempo.setString(std::to_string(static_cast<int>(round(tiempoInt - tiempoRestante.getElapsedTime().asSeconds()))));

    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    for (auto &pieza : piezas)
    {
        if (pieza.agarrada && !(pieza.posicionada))
        {
            pieza.sprite.setPosition(posicionEnVentana);
        }
    }
    if (tiempoRestante.getElapsedTime().asSeconds() >= tiempoInt)
    {
        juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
    }
    size_t i = 0;
    for (auto &pieza : piezas)
    {
        if (pieza.posicionada)
        {
            if(i == 7){
                juego->minijuegosPasados[5] = true;
                juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
            }
        } else {
            break;
        }

        i++;
    }


}
void minijuegoDisenoArquitectonico::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(contorno);
    for (auto &pieza : piezas)
    {
        window.draw(pieza.sprite);
    }
    window.draw(tiempo);

}