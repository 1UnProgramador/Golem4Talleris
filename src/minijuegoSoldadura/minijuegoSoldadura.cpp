#include "../../include/logica/Juego.h"
#include "../../include/minijuegoSoldadura/minijuegoSoldadura.h"
#include "../../include/pantallas/Metalmecanica.h"

#include <vector>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>

minijuegoSoldadura::minijuegoSoldadura(Juego* juego)  : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoMetalmecanica.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);


    std::vector<std::string> nombrePlacas = {"panelSoldar1", "panelSoldar2", "panelSoldar3", "panelSoldar4"};
    for (const auto& nombre : nombrePlacas) {
        PanelSoldable p;
        p.tPanel = std::make_shared<sf::Texture>();


        if (!p.tPanel->loadFromFile("../assets/minijuegoSoldadura/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        p.sPanel.setTexture(*p.tPanel);
        p.sPanel.setOrigin(p.sPanel.getGlobalBounds().width / 2, p.sPanel.getGlobalBounds().height / 2);
        p.sPanel.setScale(15, 15);
        p.sPanel.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
        paneles.push_back(p);
    }

    tSopleteActivado.loadFromFile("../assets/minijuegoSoldadura/sopleteActivado.png");
    tSopleteDesactivado.loadFromFile("../assets/minijuegoSoldadura/sopleteDesactivado.png");

    soplete.setTexture(tSopleteActivado);
    soplete.setOrigin(soplete.getGlobalBounds().width / 2, soplete.getGlobalBounds().height / 2);
    soplete.setScale(2, 2);

    tMarcaLimpia.loadFromFile("../assets/minijuegoSoldadura/soldaduraLimpia.png");
    tMarcaSucia.loadFromFile("../assets/minijuegoSoldadura/soldaduraSucia.png");

    sf::Sprite prueba;
    prueba.setTexture(tMarcaSucia);
    prueba.setOrigin(prueba.getGlobalBounds().width / 2, prueba.getGlobalBounds().height / 2);
    prueba.setScale(2, 2);

    debugging.setSize(sf::Vector2f(prueba.getGlobalBounds().width, prueba.getGlobalBounds().height));
    debugging.setFillColor(sf::Color(0, 0, 255));
    debugging.setOrigin(debugging.getGlobalBounds().width / 2, debugging.getGlobalBounds().height / 2);
    debugging.setPosition(paneles[2].sPanel.getPosition());


    float yActual = paneles[0].sPanel.getPosition().y - (paneles[0].sPanel.getGlobalBounds().height / 2) + (prueba.getGlobalBounds().height / 2);
    while (yActual < (paneles[0].sPanel.getPosition().y + (paneles[0].sPanel.getGlobalBounds().height / 2) - (prueba.getGlobalBounds().height / 3)))
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[0].sPanel.getPosition().x, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[0].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().height);
    }

    yActual = paneles[1].sPanel.getPosition().y + (paneles[1].sPanel.getGlobalBounds().height / 2) - prueba.getGlobalBounds().height / 2;
    /* float diferenciaX = paneles[1].sPanel.getPosition().x - prueba.getGlobalBounds().width / 2;
    float diferenciaX = paneles[1].sPanel.getPosition().y - prueba.getGlobalBounds().width / 2; */

    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[1].sPanel.getPosition().x - 152 + (debugging.getGlobalBounds().width / 2), yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[1].marcas.push_back(spriteMarca);
        yActual -= 0.4 * (spriteMarca.getGlobalBounds().height);
    } while (yActual > paneles[1].sPanel.getPosition().y + 89 + (debugging.getGlobalBounds().height / 2));

    float xActual = paneles[1].sPanel.getPosition().x - 152 + debugging.getGlobalBounds().width / 2;

    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[1].sPanel.getPosition().y + 89 + (debugging.getGlobalBounds().height / 2));
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[1].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual < paneles[1].sPanel.getPosition().x + (paneles[1].sPanel.getGlobalBounds().width / 2) - (prueba.getGlobalBounds().width / 4));

    yActual = paneles[1].sPanel.getPosition().y + 89;

    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[1].sPanel.getPosition().x + 89 + (debugging.getGlobalBounds().width / 2), yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[1].marcas.push_back(spriteMarca);
        yActual -= 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual > paneles[1].sPanel.getPosition().y - (paneles[1].sPanel.getGlobalBounds().width / 2) + (prueba.getGlobalBounds().width / 4));

    xActual = paneles[1].sPanel.getPosition().x + 89;

    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[1].sPanel.getPosition().y - 152 + (debugging.getGlobalBounds().height / 2));
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[1].marcas.push_back(spriteMarca);
        xActual -= 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual > paneles[1].sPanel.getPosition().x - (paneles[1].sPanel.getGlobalBounds().width / 2) + (prueba.getGlobalBounds().width / 4));


    xActual = paneles[2].sPanel.getPosition().x - (paneles[2].sPanel.getGlobalBounds().width / 2) + (prueba.getGlobalBounds().width / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[1].sPanel.getPosition().y + 119);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[2].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual <= paneles[2].sPanel.getPosition().x - 120 + (prueba.getGlobalBounds().width / 4));

    yActual = paneles[2].sPanel.getPosition().y + 119;
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[2].sPanel.getPosition().x - 120, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[2].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual <= paneles[2].sPanel.getPosition().y + (paneles[2].sPanel.getGlobalBounds().height / 2) - (prueba.getGlobalBounds().width / 4));

    yActual = paneles[2].sPanel.getPosition().y - (paneles[2].sPanel.getGlobalBounds().height / 2) + (prueba.getGlobalBounds().height / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[2].sPanel.getPosition().x + 119, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[2].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual <= paneles[2].sPanel.getPosition().y + (paneles[2].sPanel.getGlobalBounds().height / 2) - (prueba.getGlobalBounds().width / 4));

    xActual = paneles[2].sPanel.getPosition().x - (paneles[2].sPanel.getGlobalBounds().width / 2) + (prueba.getGlobalBounds().width / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[2].sPanel.getPosition().y - 120);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[2].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual <= paneles[2].sPanel.getPosition().x + 119);

    xActual = paneles[2].sPanel.getPosition().x + 120;
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[2].sPanel.getPosition().y + 120);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[2].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual <= paneles[2].sPanel.getPosition().x + (paneles[2].sPanel.getGlobalBounds().width / 2) - (prueba.getGlobalBounds().width / 2));


    xActual = paneles[3].sPanel.getPosition().x - (paneles[3].sPanel.getGlobalBounds().width / 2) + (prueba.getGlobalBounds().width / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[3].sPanel.getPosition().y - 121);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual <= paneles[3].sPanel.getPosition().x - 240);

    yActual = paneles[3].sPanel.getPosition().y - (paneles[3].sPanel.getGlobalBounds().height / 2) + (prueba.getGlobalBounds().height / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[3].sPanel.getPosition().x - 240, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual <= paneles[3].sPanel.getPosition().y - 121);

    yActual = paneles[3].sPanel.getPosition().y - (paneles[3].sPanel.getGlobalBounds().height / 2) + (prueba.getGlobalBounds().height / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[3].sPanel.getPosition().x, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual <= paneles[3].sPanel.getPosition().y - 121);

    xActual = paneles[3].sPanel.getPosition().x;
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[3].sPanel.getPosition().y - 121);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual <= paneles[3].sPanel.getPosition().x + (paneles[3].sPanel.getGlobalBounds().width / 2) - (prueba.getGlobalBounds().width / 4));

    yActual = paneles[3].sPanel.getPosition().y - (paneles[3].sPanel.getGlobalBounds().height / 2) + (prueba.getGlobalBounds().height / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[3].sPanel.getPosition().x + 240, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual <= paneles[3].sPanel.getPosition().y + (paneles[3].sPanel.getGlobalBounds().height / 2));

    xActual = paneles[3].sPanel.getPosition().x - (paneles[3].sPanel.getGlobalBounds().width / 2) + (prueba.getGlobalBounds().width / 2);
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(xActual, paneles[3].sPanel.getPosition().y + 120);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        xActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (xActual <= paneles[3].sPanel.getPosition().x + 240);

    yActual = paneles[3].sPanel.getPosition().y + 120;
    do
    {
        sf::Sprite spriteMarca;
        spriteMarca.setTexture(tMarcaSucia);
        spriteMarca.setOrigin(spriteMarca.getGlobalBounds().width / 2, spriteMarca.getGlobalBounds().height / 2);
        spriteMarca.setScale(2, 2);
        spriteMarca.setPosition(paneles[3].sPanel.getPosition().x, yActual);
        spriteMarca.setColor(sf::Color(255, 255, 255, 0));
        paneles[3].marcas.push_back(spriteMarca);
        yActual += 0.4 * (spriteMarca.getGlobalBounds().width);
    } while (yActual <= paneles[3].sPanel.getPosition().y + (paneles[3].sPanel.getGlobalBounds().height / 2) - (prueba.getGlobalBounds().height / 2));


    paneles[1].activada = true;

    if (juego->minijuegoFacil)
    {
        tiempoInt = 50;
    } else {
        tiempoInt = 30;
    }

    fuente.loadFromFile("../assets/textos/Ubuntu-Bold.ttf");
    tiempo.setFont(fuente);
    tiempo.setScale(2, 2);
    tiempo.setPosition(0, 0);
    tiempoRestante.restart();
    tiempo.setString(std::to_string(tiempoInt));
}

void minijuegoSoldadura::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed){
        if(evento.key.code == sf::Keyboard::Escape){
            juego->cambiarPantalla(std::make_unique<Metalmecanica>(juego));
        } else if(evento.key.code == sf::Keyboard::W){
            debugging.move(0, -1);
        } else if(evento.key.code == sf::Keyboard::A){
            debugging.move(-1, 0);
        } else if(evento.key.code == sf::Keyboard::S){
            debugging.move(0, 1);
        } else if(evento.key.code == sf::Keyboard::D){
            debugging.move(1, 0);
        }
        std::cout << "Posicion actual: " << std::to_string(paneles[3].sPanel.getPosition().x - debugging.getPosition().x) << ", " << std::to_string(paneles[3].sPanel.getPosition().y - debugging.getPosition().y) << std::endl;
    } else if(evento.type == sf::Event::MouseButtonPressed){
        if(evento.mouseButton.button == sf::Mouse::Left){
            for (auto &panel : paneles)
            {
                if (panel.activada)
                {
                    for (auto &sprite : panel.marcas){
                        if (sprite.getGlobalBounds().contains(posicionEnVentana)){
                            sprite.setColor(sf::Color(255, 255, 255, 255));
                            soldando = true;
                        }
                    }
                    size_t i = 0;
                    for (auto &sprite : panel.marcas){
                        if (sprite.getColor().a == 255){
                            if (i == panel.marcas.size() - 1)
                            {
                                paneles[panelActual].activada = false;
                                panelActual++;
                                paneles[panelActual].activada = true;
                            }
                        } else {
                            break;
                        }
                        i++;
                    }
                }
            }


        }
    } else if(evento.type == sf::Event::MouseButtonReleased){
        if(evento.mouseButton.button == sf::Mouse::Left){
            soldando = false;
        }
    }
}

void minijuegoSoldadura::actualizar(){
    tiempo.setString(std::to_string(static_cast<int>(round(tiempoInt - tiempoRestante.getElapsedTime().asSeconds()))));

    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    if(soldando){
        soplete.setPosition(posicionEnVentana.x + soplete.getGlobalBounds().width / 2, posicionEnVentana.y + 20);
        for (auto &panel : paneles)
        {
            if (panel.activada)
            {
                for (auto &sprite : panel.marcas){
                    if (sprite.getGlobalBounds().contains(posicionEnVentana)){
                        sprite.setColor(sf::Color(255, 255, 255, 255));
                        soldando = true;
                    }
                }
                size_t i = 0;
                for (auto &sprite : panel.marcas){
                    if (sprite.getColor().a == 255){
                        if (i == panel.marcas.size() - 1)
                        {
                            paneles[panelActual].activada = false;
                            panelActual++;
                            paneles[panelActual].activada = true;
                        }
                    } else {
                        break;
                    }
                    i++;
                }
            }
        }
    } else {
        soplete.setPosition(-1000,-1000);
    }

    if (tiempoRestante.getElapsedTime().asSeconds() >= tiempoInt)
    {
        juego->cambiarPantalla(std::make_unique<Metalmecanica>(juego));
    }
}

void minijuegoSoldadura::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    for (auto &panel : paneles)
    {
        if (panel.activada)
        {
            window.draw(panel.sPanel);
            for (auto &sprite : panel.marcas)
            {
                window.draw(sprite);
            }
        }

    }


    window.draw(soplete);
    window.draw(tiempo);
}