#include "../../include/minijuegoPonchar/minijuegoPonchar.h"
#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <string>
std::vector<sf::Vector2f> posiciones{
    {0, 0}
};
/* #include "../../assets/minijuegoPonchar/naranjaBlanco.png" */
minijuegoPonchar::minijuegoPonchar(Juego* juego) : Pantalla(juego){
    tConector.loadFromFile("../assets/minijuegoPonchar/conector.png");
    conector.setTexture(tConector);
    conector.setScale(0.5, 0.5);
    conector.setPosition(1000, 0);

    int nCable = 1;
    std::vector<std::string> nombresCables = {"naranjaBlanco", "naranja", "verdeBlanco", "azul", "azulBlanco", "verde", "cafeBlanco", "cafe"};
    for (const auto& nombre : nombresCables) {
        Cable cable;
        cable.tCable = std::make_shared<sf::Texture>();

        cable.pObjetivo.setPosition(1013 + (22) * nCable, 79);
        cable.pObjetivo.setSize(sf::Vector2f(11, 16));
        cable.pObjetivo.setFillColor(sf::Color::Red);

        if (!cable.tCable->loadFromFile("../assets/minijuegoPonchar/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        cable.pinObjetivo = nCable;
        cable.sCable.setScale(3, 3);
        cable.sCable.setTexture(*cable.tCable);
        cables.push_back(cable);
        nCable += 1;
    }
    cables.at(0).pObjetivo.move(-1, 0);
    cables.at(1).pObjetivo.move(-1, 0);
    cables.at(2).pObjetivo.move(-2, 0);
    cables.at(5).pObjetivo.move(1, 0);
    cables.at(6).pObjetivo.move(2, 0);
    cables.at(7).pObjetivo.move(2, 0);
}

void minijuegoPonchar::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
    {
        exit(0);
    }
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        juego->cambiarPantalla(std::make_unique<minijuegoPaginaWeb>(juego));
    }
    if (evento.type == sf::Event::MouseButtonPressed) {
        // Detecta si el clic está sobre algún cable
        for (int i = 0; i <= 7; i++)
        {
            (cables[i].sCable.getGlobalBounds().contains(posicionEnVentana)) ? cables[i].arrastrando = true : cables[i].arrastrando = false;
        }
    } else if (evento.type == sf::Event::MouseMoved) {
        // Si dragging == true, actualiza la posición del cable al mouse
    } else if (evento.type == sf::Event::MouseButtonReleased)
    {
        for (int i = 0; i <= 7; i++)
        {
            for (int j = 0; j <= 7; j++)
            {
                if (cables[i].sCable.getGlobalBounds().intersects(cables[j].pObjetivo.getGlobalBounds()) && cables[j].objetivoOcupado == false)
                {
                    cables[i].sCable.setPosition(cables[j].pObjetivo.getPosition().x - 5, cables[j].pObjetivo.getPosition().y);
                    cables[i].arrastrando = false;
                    cables[i].conectado = true;

                    if (cables[i].sCable.getGlobalBounds().intersects(cables[i].pObjetivo.getGlobalBounds())){
                        cables[i].correcto = true;
                    } else {
                        cables[i].correcto = false;
                    }
                    cables[j].objetivoOcupado = true;
                    break;
                }
            }
            if (!cables[i].conectado) {
                cables[i].sCable.setPosition(100 + (20) * i, sf::VideoMode::getDesktopMode().height - cables[i].sCable.getGlobalBounds().height);
                cables[i].arrastrando = false;
                cables[i].conectado = false;
            }
        }
    }
}


void minijuegoPonchar::actualizar(){
    for (auto &cable : cables)
    {
        if (cable.objetivoOcupado == true)
        {
            for (auto &cableB : cables)
            {
                if (!cable.pObjetivo.getGlobalBounds().intersects(cableB.sCable.getGlobalBounds())){
                    cable.objetivoOcupado = false;
                }
            }

        }
        if (cable.objetivoOcupado){
            cable.pObjetivo.setFillColor(sf::Color::Green);
        }
    }

    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    for (int i = 0; i <= 7; i++)
    {
        if (cables[i].arrastrando) {
            cables[i].sCable.setPosition(posicionEnVentana);
        } else if (!cables[i].conectado)
        {
            cables[i].sCable.setPosition(100 + (20) * (i + 1), sf::VideoMode::getDesktopMode().height - cables[i].sCable.getGlobalBounds().height);
        }

    }

}

void minijuegoPonchar::renderizar(sf::RenderWindow& window){
    window.draw(conector);
    /* window.draw(fondo2);
    window.draw(fondo3);
    window.draw(fondo4); */
    for (auto &cable : cables){
        window.draw(cable.pObjetivo);
    }
    for (auto &cable : cables){
        window.draw(cable);
    }
}
