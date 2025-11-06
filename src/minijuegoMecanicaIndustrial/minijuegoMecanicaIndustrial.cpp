#include "../../include/logica/Juego.h"
#include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"
#include "../../include/pantallas/Metalmecanica.h"

#include <vector>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>

#include "../../src/logica/assetManager.h"

minijuegoMecanicaIndustrial::minijuegoMecanicaIndustrial(Juego* juego) : Pantalla(juego){


    tFondo.loadFromMemory(fondoMetalmecanica_png, fondoMetalmecanica_png_len);
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tPantalla.loadFromMemory(pantalla_png, pantalla_png_len);
    sPantalla.setTexture(tPantalla);
    sPantalla.setOrigin(sPantalla.getGlobalBounds().width / 2, sPantalla.getGlobalBounds().height / 2);
    sPantalla.setPosition(sf::VideoMode::getDesktopMode().width / 2, (sf::VideoMode::getDesktopMode().height / 2));
    sPantalla.setScale(9, 9);
    sPantalla.move(0, -1 * (sPantalla.getGlobalBounds().height));

    tCintas.loadFromMemory(cintas_png, cintas_png_len);
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

    tPistonDesactivado.loadFromMemory(pistonDesActivado_png, pistonDesActivado_png_len);
    pistonDesactivado.setTexture(tPistonDesactivado);
    pistonDesactivado.setOrigin(pistonDesactivado.getGlobalBounds().width / 2, pistonDesactivado.getGlobalBounds().height / 2);
    pistonDesactivado.setPosition(sf::VideoMode::getDesktopMode().width / 2, (sf::VideoMode::getDesktopMode().height / 2));

    tPistonActivado.loadFromMemory(pistonActivado_png, pistonActivado_png_len);
    pistonActivado.setTexture(tPistonActivado);
    pistonActivado.setOrigin(pistonActivado.getGlobalBounds().width / 2, pistonActivado.getGlobalBounds().height / 2);
    pistonActivado.setPosition(pistonDesactivado.getPosition().x, pistonDesactivado.getPosition().y);

    std::vector<std::string> nombresPiezas = {"L", "T", "Z"};
    for (const auto& nombre : nombresPiezas) {
        Pieza p;
        p.tPiezas = std::make_shared<sf::Texture>();

        if (nombre == "L")
        {
            if (!p.tPiezas->loadFromMemory(L_png, L_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "T")
        {
            if (!p.tPiezas->loadFromMemory(T_png, T_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "Z")
        {
            if (!p.tPiezas->loadFromMemory(Z_png, Z_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
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


        if (nombre == "LM")
        {
            if (!p.tPiezas->loadFromMemory(LM_png, LM_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "TM")
        {
            if (!p.tPiezas->loadFromMemory(TM_png, TM_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        } else if (nombre == "ZM")
        {
            if (!p.tPiezas->loadFromMemory(ZM_png, ZM_png_len)) {
                std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
            }
        }
        p.sPieza.setTexture(*p.tPiezas);
        p.sPieza.setOrigin(p.sPieza.getGlobalBounds().width / 2, p.sPieza.getGlobalBounds().height / 2);
        p.sPieza.setScale(0.7, 0.7);
        p.sPieza.setPosition(cintas.getPosition().x - 1107, cintas.getPosition().y);
        piezasMalas.push_back(p);
    }
    std::vector<std::string> listaCorazones = {"1", "2", "3"};
    int i = 0;
    int separacion = 150;
    for (const auto& corazon : listaCorazones) {
        Corazon c;

        c.tCorazon = std::make_shared<sf::Texture>();


        if (!c.tCorazon->loadFromMemory(corazon_png, corazon_png_len)) {
            std::cerr << "No se pudo cargar .png" << std::endl;
        }
        c.sCorazon.setTexture(*c.tCorazon);
        c.sCorazon.setOrigin(c.sCorazon.getGlobalBounds().width / 2, c.sCorazon.getGlobalBounds().height / 2);
        c.sCorazon.setScale(0.2, 0.2);
        c.sCorazon.setPosition((c.sCorazon.getGlobalBounds().width / 2) + (c.sCorazon.getGlobalBounds().height / 2) + (separacion * i) , c.sCorazon.getGlobalBounds().height / 2);
        corazones.push_back(c);
        i++;
    }
    cambioPieza.restart();
    piezasBuenas[0].sPieza.setPosition(sPantalla.getPosition().x, sPantalla.getPosition().y);
    piezasBuenas[1].sPieza.setPosition(piezasBuenas[0].sPieza.getPosition().x, piezasBuenas[0].sPieza.getPosition().y);
    piezasBuenas[2].sPieza.setPosition(piezasBuenas[0].sPieza.getPosition().x, piezasBuenas[0].sPieza.getPosition().y);
    piezasBuenas[0].activada = true;

    tBoteBasurero.loadFromMemory(caneca4_png, caneca4_png_len);
    boteBasurero.setTexture(tBoteBasurero);
    boteBasurero.setOrigin(boteBasurero.getGlobalBounds().width / 2, boteBasurero.getGlobalBounds().height / 2);
    boteBasurero.setScale(3, 3);
    boteBasurero.setPosition(pistonActivado.getPosition().x, sf::VideoMode::getDesktopMode().height - boteBasurero.getGlobalBounds().height);

    fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len);
    texto.setFont(fuente);
    texto.setString("Actualmente tienes: 0 Puntos!");
    texto.setCharacterSize(40);
    texto.setOrigin(texto.getGlobalBounds().width / 2, texto.getGlobalBounds().height / 2);
    texto.setPosition(sPantalla.getPosition().x, sPantalla.getPosition().y - (sPantalla.getGlobalBounds().height / 2) - (texto.getGlobalBounds().height) - 25);

    if (juego->minijuegoFacil)
    {
        necesarios = 5;
    } else {
        necesarios = 15;
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

        } else if(evento.key.code == sf::Keyboard::Escape){
            juego->cambiarPantalla(std::make_unique<Metalmecanica>(juego));
        }
    } else if(evento.type == sf::Event::KeyReleased){
        if(evento.key.code == sf::Keyboard::Space){
            activado = false;
        }
    }
}
void minijuegoMecanicaIndustrial::actualizar(){
    if(corazones.empty()){
        juego->cambiarPantalla(std::make_unique<Metalmecanica>(juego));
    }
    if (puntos >= necesarios){
        juego->minijuegosPasados[4] = true;
        juego->cambiarPantalla(std::make_unique<Metalmecanica>(juego));
    }

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

    if (cambioPieza.getElapsedTime().asSeconds() >= numeroPiezas * delayTime){
        if(piezasBuenas[0].activada){
            piezasBuenas[0].activada = false;
            piezasBuenas[1].activada = true;
            cambioPieza.restart();
        } else if(piezasBuenas[1].activada){
            piezasBuenas[1].activada = false;
            piezasBuenas[2].activada = true;
            cambioPieza.restart();
        }
    }

    if (relojPiezas.getElapsedTime().asSeconds() >= delayTime) {
        Pieza pieza;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 5);
        int numero = dist(gen);

        if(numero >= 0 && numero <= 2){
            pieza = piezasBuenas[numero];
            pieza.piezaBuena = true;
        } else if (numero >= 3 && numero <= 5){
            pieza = piezasMalas[numero - 3];
            pieza.piezaBuena = false;
        }
        pieza.sPieza.setPosition(cintas.getPosition().x - 1107, cintas.getPosition().y);
        piezasGeneradas.push_back(pieza);
        std::cout << "Pieza Creada";
        relojPiezas.restart();
    }

    for (size_t i = 0; i < piezasGeneradas.size(); ) {
    auto &pieza = piezasGeneradas[i];

    if (pieza.piezaGolpeada)
        pieza.sPieza.move(0, velocidad * 2);
    else
        pieza.sPieza.move(velocidad, 0);

    if (pieza.sPieza.getPosition().x > sf::VideoMode::getDesktopMode().width || pieza.sPieza.getPosition().y > sf::VideoMode::getDesktopMode().height || pieza.sPieza.getGlobalBounds().intersects(boteBasurero.getGlobalBounds())) {

        if(pieza.sPieza.getPosition().x > sf::VideoMode::getDesktopMode().width){
            if (pieza.activada)
            {
                puntos++;
                std::cout << "puntos: " << std::to_string(puntos) << std::endl;
                texto.setString("Actualmente tienes: " + std::to_string(puntos) + " Puntos!");
            } else {
                if (!corazones.empty()) {
                    corazones.erase(corazones.end() - 1);
                }
            }
        } else if(pieza.sPieza.getPosition().y > sf::VideoMode::getDesktopMode().height || pieza.sPieza.getGlobalBounds().intersects(boteBasurero.getGlobalBounds())){
            if (pieza.activada)
            {
                if (!corazones.empty()) {
                    corazones.erase(corazones.end() - 1);
                }
            } else {

            }

        }

        piezasGeneradas.erase(piezasGeneradas.begin() + i);
        std::cout << "Pieza destruida";


    } else {
        i++;
    }
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
    for (auto &pieza : piezasBuenas)
    {
        if(pieza.activada){
            window.draw(pieza.sPieza);
        }
    }
    window.draw(boteBasurero);
    for (auto &corazon : corazones)
    {
        window.draw(corazon.sCorazon);
    }
    window.draw(texto);
}