#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/pantallas/informatica.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include "../../src/logica/assetManager.h"
#include <cmath>

bool dentroVista(const sf::Vector2f& pos, const sf::View& vista/* , const sf::RenderWindow& window */);

minijuegoPaginaWeb::minijuegoPaginaWeb(Juego* juego) : Pantalla(juego){
    tFondo.loadFromMemory(fondoInformatica_png, fondoInformatica_png_len);
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);
    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;
    fondo.setScale(fX, fY);


    std::vector<std::string> nombres = {"contornoWeb", "compraAzul", "compraRojo", "imagen"};
    for (const auto& nombre : nombres) {
        Pieza p;
        p.textura = std::make_shared<sf::Texture>();

        if (nombre == "compraAzul")
        {
            if (!p.textura->loadFromMemory(compraAzul_png, compraAzul_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "compraRojo")
        {
            if (!p.textura->loadFromMemory(compraRojo_png, compraRojo_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "contornoWeb")
        {
            if (!p.textura->loadFromMemory(contornoWeb_png, contornoWeb_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "imagen")
        {
            if (!p.textura->loadFromMemory(imagen_png, imagen_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        }


        p.sprite.setTexture(*p.textura);
        p.sprite.setOrigin(p.sprite.getGlobalBounds().width / 2, p.sprite.getGlobalBounds().height / 2);
        p.sprite.setScale(7, 7);
        /* p.sprite.setPosition(cintas.getPosition().x - 1107, cintas.getPosition().y); */
        piezas.push_back(p);
    }

    piezas[0].sprite.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    piezas[0].posicionInicial = piezas[0].sprite.getPosition();
    piezas[0].posicionObjetivo = sf::Vector2f(-1000, -1000);


    piezas[1].sprite.setPosition(100 + piezas[1].sprite.getGlobalBounds().width, (piezas[1].sprite.getGlobalBounds().height / 2) + 10);
    piezas[1].posicionInicial = piezas[1].sprite.getPosition();
    piezas[1].posicionObjetivo = sf::Vector2f(piezas[0].sprite.getPosition().x - 287, piezas[0].sprite.getPosition().y + 73.5);
    /* piezas[1].sprite.setPosition(piezas[1].posicionObjetivo); */

    piezas[2].sprite.setPosition(piezas[1].sprite.getPosition().x + piezas[1].sprite.getGlobalBounds().width + piezas[2].sprite.getGlobalBounds().width, (piezas[2].sprite.getGlobalBounds().height / 2) + 10);
    piezas[2].posicionInicial = piezas[2].sprite.getPosition();
    piezas[2].posicionObjetivo = sf::Vector2f(piezas[0].sprite.getPosition().x + 294, piezas[0].sprite.getPosition().y + 73.5);
    /* piezas[2].sprite.setPosition(piezas[2].posicionObjetivo); */

    piezas[3].sprite.setPosition(piezas[2].sprite.getPosition().x + piezas[2].sprite.getGlobalBounds().width + piezas[3].sprite.getGlobalBounds().width, (piezas[3].sprite.getGlobalBounds().height / 2) + 10);
    piezas[3].posicionInicial = piezas[3].sprite.getPosition();
    piezas[3].posicionObjetivo = sf::Vector2f(piezas[0].sprite.getPosition().x + 294, piezas[0].sprite.getPosition().y - 42);
    /* piezas[3].sprite.setPosition(piezas[3].posicionObjetivo); */

    if (juego->minijuegoFacil)
    {
        tiempoInt = 30;
    } else {
        tiempoInt = 20;
    }
    fuente.loadFromMemory(Ubuntu_Bold_ttf, Ubuntu_Bold_ttf_len);
    tiempo.setFont(fuente);
    tiempo.setScale(2, 2);
    tiempo.setPosition(0, 0);
    tiempoRestante.restart();
    tiempo.setString(std::to_string(tiempoInt));
}

void minijuegoPaginaWeb::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed)
    {
        if(evento.key.code == sf::Keyboard::Escape){
            juego->cambiarPantalla(std::make_unique<Informatica>(juego));
        } else if (evento.key.code == sf::Keyboard::W)
        {
            piezas[3].sprite.move(0, -1);
        } else if (evento.key.code == sf::Keyboard::A)
        {
            piezas[3].sprite.move(-1, 0);
        } else if (evento.key.code == sf::Keyboard::S)
        {
            piezas[3].sprite.move(0, 1);
        } else if (evento.key.code == sf::Keyboard::D)
        {
            piezas[3].sprite.move(1, 0);
        }
        std::cout << "Posicion en: " << std::to_string(piezas[0].sprite.getPosition().x - piezas[3].sprite.getPosition().x) << ", " << std::to_string(piezas[0].sprite.getPosition().y - piezas[3].sprite.getPosition().y) << std::endl;

    } else if (evento.type == sf::Event::MouseButtonPressed) {
        if(evento.mouseButton.button == sf::Mouse::Left){
            int i = 0;
            for (auto &p : piezas)
            {
                if(i != 0){
                    if (p.sprite.getGlobalBounds().contains(posicionEnVentana) && !p.posicionada)
                    {
                        p.agarrada = true;
                    }
                }
                i++;
            }
        }


    } else if (evento.type == sf::Event::MouseButtonReleased) {
        int i = 0;
        for (auto &p : piezas)
        {
            if (i != 0)
            {
                p.agarrada = false;
                if (!p.posicionada)
                {
                    float dX = p.posicionObjetivo.x - p.sprite.getPosition().x;
                    float dY = p.posicionObjetivo.y - p.sprite.getPosition().y;
                    if (dX <= 50 && dY <= 50)
                    {
                        p.posicionada = true;
                        p.sprite.setPosition(p.posicionObjetivo);
                        int k = 0;
                        for (auto &p : piezas)
                        {
                            if (k != 0)
                            {
                                if (p.posicionada)
                                {
                                    if (k == 3)
                                    {
                                        juego->minijuegosPasados[1] = true;
                                        juego->cambiarPantalla(std::make_unique<Informatica>(juego));
                                    }

                                } else {
                                    break;
                                }

                            }

                            k++;
                        }

                    } else {
                        p.sprite.setPosition(p.posicionInicial);
                    }

                }
            }

            i++;
        }

    }

}

void minijuegoPaginaWeb::actualizar(){
    tiempo.setString(std::to_string(static_cast<int>(round(tiempoInt - tiempoRestante.getElapsedTime().asSeconds()))));
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    int i = 0;
    for (auto &p : piezas)
    {
        if (i != 0)
        {
            if (p.agarrada)
            {
                p.sprite.setPosition(posicionEnVentana);
            }
        }

        i++;
    }
    if (tiempoRestante.getElapsedTime().asSeconds() >= tiempoInt)
    {
        juego->cambiarPantalla(std::make_unique<Informatica>(juego));
    }
}

void minijuegoPaginaWeb::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    for (auto &p : piezas)
    {
        window.draw(p.sprite);
    }

    window.draw(tiempo);

}