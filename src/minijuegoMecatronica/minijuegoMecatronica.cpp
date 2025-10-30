#include "../../include/logica/Juego.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"

#include "../../include/pantallas/electricidad.h"


#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

minijuegoMecatronica::minijuegoMecatronica(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);



    tLente.loadFromFile("../assets/minijuegoMecatronica/lente.png");
    lente.setTexture(tLente);
    lente.setOrigin(lente.getGlobalBounds().width / 2, lente.getGlobalBounds().height / 2);
    lente.setScale(3, 3);



    tPalo.loadFromFile("../assets/minijuegoMecatronica/palo.png");
    palo.setTexture(tPalo);

    palo.setOrigin(palo.getGlobalBounds().width / 2, palo.getGlobalBounds().height / 2);
    palo.setScale(4, 4);
    palo.setPosition(sf::VideoMode::getDesktopMode().width / 2, (palo.getGlobalBounds().height / 2) - 15);


    tGarra.loadFromFile("../assets/minijuegoMecatronica/garra.png");
    garra.setTexture(tGarra);
    garra.setOrigin(garra.getGlobalBounds().width / 2, garra.getGlobalBounds().width / 2);
    garra.setScale(4, 4);

    garra.setPosition(palo.getPosition().x, palo.getPosition().y + (garra.getGlobalBounds().height / 2) - 20);




    tB1.loadFromFile("../assets/minijuegoMecatronica/caneca1.png");
    tB2.loadFromFile("../assets/minijuegoMecatronica/caneca2.png");
    tB3.loadFromFile("../assets/minijuegoMecatronica/caneca3.png");
    tB4.loadFromFile("../assets/minijuegoMecatronica/caneca4.png");

    b1.setTexture(tB1);
    b1.setScale(3, 3);
    b2.setTexture(tB2);
    b2.setScale(3, 3);
    b3.setTexture(tB3);
    b3.setScale(3, 3);
    b4.setTexture(tB4);
    b4.setScale(3, 3);

    float separacion = 200;
    b1.setPosition(100, sf::VideoMode::getDesktopMode().height - b1.getGlobalBounds().height);
    b2.setPosition(b1.getPosition().x + b1.getGlobalBounds().width + separacion, sf::VideoMode::getDesktopMode().height - b2.getGlobalBounds().height);
    b3.setPosition(b2.getPosition().x + b2.getGlobalBounds().width + separacion, sf::VideoMode::getDesktopMode().height - b3.getGlobalBounds().height);
    b4.setPosition(b3.getPosition().x + b3.getGlobalBounds().width + separacion, sf::VideoMode::getDesktopMode().height - b4.getGlobalBounds().height);


    lente.setPosition(b2.getPosition().x + b2.getGlobalBounds().width + (separacion / 2), garra.getPosition().y + (garra.getGlobalBounds().height / 2) + (lente.getGlobalBounds().height / 2) + 50);

    std::vector<std::string> nombresObjetos = {"botella", "caja", "bateria", "cascara", "lata"};
    for (const auto& nombre : nombresObjetos) {
        Objeto o;
        o.tObjeto = std::make_shared<sf::Texture>();


        if (!o.tObjeto->loadFromFile("../assets/minijuegoMecatronica/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        o.sObjeto.setTexture(*o.tObjeto);
        o.sObjeto.setOrigin(o.sObjeto.getGlobalBounds().width / 2, o.sObjeto.getGlobalBounds().height / 2);
        o.sObjeto.setScale(2, 2);
        o.sObjeto.setPosition(sf::VideoMode::getDesktopMode().width - 200, lente.getPosition().y - 80);
        posicionesObjetos.push_back(o.sObjeto.getPosition());
        objetos.push_back(o);
    }
    std::vector<std::string> nombresLeds = {"apagado", "azul", "rojo", "verde"};
    for (const auto& nombre : nombresLeds) {
        led l;
        l.tLed = std::make_shared<sf::Texture>();


        if (!l.tLed->loadFromFile("../assets/minijuegoMecatronica/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        l.sLed.setTexture(*l.tLed);
        l.sLed.setOrigin(l.sLed.getGlobalBounds().width / 2, l.sLed.getGlobalBounds().height / 2);
        l.sLed.setScale(2, 2);
        l.sLed.setPosition(lente.getPosition().x, lente.getPosition().y);
        posicionesObjetos.push_back(l.sLed.getPosition());
        leds.push_back(l);
    }
    objetos[0].sObjeto.setScale(2.2, 2.2);
    objetos[0].actual = true;
    objetos[1].sObjeto.setScale(1.8, 1.8);

    if (juego->minijuegoFacil)
    {
        tiempoInt = 60;
    } else {
        tiempoInt = 15;
    }

    fuente.loadFromFile("../assets/textos/Ubuntu-Bold.ttf");
    tiempo.setFont(fuente);
    tiempo.setScale(2, 2);
    tiempo.setPosition(0, 0);
    tiempoRestante.restart();
    tiempo.setString(std::to_string(tiempoInt));
}
void minijuegoMecatronica::ManejarEvento(sf::Event evento){
    if(evento.type == sf::Event::MouseMoved){
        garra.setPosition(posicionEnVentana.x, garra.getPosition().y);
        palo.setPosition(posicionEnVentana.x, palo.getPosition().y);
        for(auto &led : leds){
            led.activo = false;
        }
        for (auto &objeto : objetos)
        {
            if (objeto.sObjeto.getGlobalBounds().intersects(lente.getGlobalBounds()))
            {
                if (i == 0){
                    leds[1].activo = true;
                } else if(i == 1){
                    leds[0].activo = true;
                } else if(i == 2){
                    leds[2].activo = true;
                } else if(i == 3){
                    leds[3].activo = true;
                } else if(i == 4){
                    leds[1].activo = true;
                }
            }

        }
    } else if(evento.type == sf::Event::MouseButtonPressed){
        if (evento.mouseButton.button == sf::Mouse::Left){
            for (auto &objeto : objetos)
            {
                if (objeto.agarrado)
                {
                    objeto.agarrado = false;
                    objeto.cayendo = true;
                } else if (objeto.actual && objeto.sObjeto.getGlobalBounds().intersects(garra.getGlobalBounds()))
                {
                    objeto.agarrado = true;
                }
            }
        }

    } else if(evento.key.code == sf::Keyboard::Escape){
        juego->cambiarPantalla(std::make_unique<Electricidad>(juego));
    }
}
void minijuegoMecatronica::actualizar(){
    tiempo.setString(std::to_string(static_cast<int>(round(tiempoInt - tiempoRestante.getElapsedTime().asSeconds()))));

    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    for (auto &objeto : objetos)
    {

        if(objeto.agarrado){
            objeto.sObjeto.setPosition(garra.getPosition().x, objeto.sObjeto.getPosition().y);
        }
        if(objeto.cayendo){
            if(objeto.sObjeto.getGlobalBounds().intersects(b3.getGlobalBounds()) && i == 0){
                i++;
                objeto.reciclado = true;
                objeto.actual = false;
                objeto.sObjeto.setPosition(-500, -500);
                objetos[i].actual = true;
                std::cout << i;
                break;
            } else if(objeto.sObjeto.getGlobalBounds().intersects(b4.getGlobalBounds()) && i == 1){
                i++;
                objeto.reciclado = true;
                objeto.actual = false;
                objeto.sObjeto.setPosition(-500, -500);
                objetos[i].actual = true;
                std::cout << i;
                break;
            } else if(objeto.sObjeto.getGlobalBounds().intersects(b2.getGlobalBounds()) && i == 2){
                i++;
                objeto.reciclado = true;
                objeto.actual = false;
                objeto.sObjeto.setPosition(-500, -500);
                objetos[i].actual = true;
                std::cout << i;
                break;
            } else if(objeto.sObjeto.getGlobalBounds().intersects(b1.getGlobalBounds()) && i == 3){
                i++;
                objeto.reciclado = true;
                objeto.actual = false;
                objeto.sObjeto.setPosition(-500, -500);
                objetos[i].actual = true;
                std::cout << i;
                break;
            } else if(objeto.sObjeto.getGlobalBounds().intersects(b3.getGlobalBounds()) && i == 4){

                objeto.reciclado = true;
                objeto.actual = false;
                objeto.sObjeto.setPosition(-500, -500);
                juego->cambiarPantalla(std::make_unique<Electricidad>(juego));
                std::cout << i;
                break;
            } else if(objeto.sObjeto.getGlobalBounds().top > sf::VideoMode::getDesktopMode().height){
                objeto.agarrado = false;
                objeto.cayendo = false;
                objeto.sObjeto.setRotation(350);
                objeto.sObjeto.setPosition(posicionesObjetos[i]);
            }
            objeto.sObjeto.move(0, 12);
            objeto.sObjeto.rotate(10);
        }
    }

    if (tiempoRestante.getElapsedTime().asSeconds() >= tiempoInt)
    {
        juego->cambiarPantalla(std::make_unique<Electricidad>(juego));
    }
}
void minijuegoMecatronica::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(b1);
    window.draw(b2);
    window.draw(b3);
    window.draw(b4);


    /* window.draw(leds[0].sLed);
    window.draw(leds[1].sLed);
    window.draw(leds[2].sLed);
    window.draw(leds[3].sLed); */

    window.draw(lente);
    for(auto &led : leds){
        if(led.activo){
            window.draw(led.sLed);
        }
    }

    for (auto &objeto : objetos)
    {
        if (objeto.actual && !objeto.reciclado){
            window.draw(objeto.sObjeto);
        }
    }

    window.draw(palo);
    window.draw(garra);
    window.draw(tiempo);
}