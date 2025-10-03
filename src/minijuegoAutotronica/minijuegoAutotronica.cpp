#include "../../include/logica/Juego.h"
#include "../../include/minijuegoAutotronica/minijuegoAutotronica.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>
std::vector<sf::Vector2f> posicionesObjetos;

std::vector<std::string> nombresObjetosE1 = {
    "silenciadorE1", "frenoE1", "bateriaE1"
};

std::vector<std::string> nombresObjetosE3 = {
    "silenciadorE3", "frenoE3", "bateriaE3"
};

minijuegoAutotronica::minijuegoAutotronica(Juego* juego) : Pantalla(juego){
    std::vector<std::string> nombresObjetos = {"silenciadorE2", "frenoE2", "bateriaE2", "lucesE2"};
    std::vector<std::string> nombresOpciones = {"energia", "fusible", "llaveInglesa"};
    for (const auto& nombre : nombresObjetos) {
        Objeto o;
        o.textura = std::make_shared<sf::Texture>();

        if (!o.textura->loadFromFile("../assets/minijuegoAutotronica/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        o.sprite.setTexture(*o.textura); // se desreferencia al puntero
        objetos.push_back(o);
    }

    /* for (const auto& nombre : nombresObjetosE1) {
        Objeto1 o;
        o.textura = std::make_shared<sf::Texture>();

        if (!o.textura->loadFromFile("../assets/minijuegoAutotronica/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        o.sprite.setTexture(*o.textura); // se desreferencia al puntero
        objetosE1.push_back(o);
    } */

    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tCarro.loadFromFile("../assets/minijuegoAutotronica/carro.png");
    carro.setTexture(tCarro);
    carro.setOrigin(carro.getLocalBounds().width / 2, carro.getLocalBounds().height / 2);
    carro.setPosition(sf::VideoMode::getDesktopMode().width / 2, (sf::VideoMode::getDesktopMode().height /2) - carro.getGlobalBounds().height / 2);

    /* objetoSeleccionado.setPosition(carro.getPosition().x, carro.getPosition().y + 100); */

    objetos[0].sprite.setPosition(carro.getPosition().x - 263, carro.getPosition().y + 65);

    posicionesObjetos.push_back(objetos[0].sprite.getPosition());
    /* silenciador.setTexture(tSilenciador); */
    /* silenciador.setPosition(420, 254); */

    objetos[1].sprite.setPosition(carro.getPosition().x + 105, carro.getPosition().y + 52);

    posicionesObjetos.push_back(objetos[1].sprite.getPosition());
    /* freno.setTexture(tFreno); */
    /* freno.setPosition(788, 241); */

    objetos[2].sprite.setPosition(carro.getPosition().x + 120, carro.getPosition().y + 11);
    objetos[3].sprite.setPosition(carro.getPosition().x + 191, carro.getPosition().y + 30);

    posicionesObjetos.push_back(objetos[2].sprite.getPosition());
    /* bateria.setTexture(tBateria);
    bateria.setPosition(803, 200); */
    Objeto silenciador;
    silenciador.textura = std::make_shared<sf::Texture>();
    silenciador.textura->loadFromFile("../assets/minijuegoAutotronica/silenciadorE1.png");
    silenciador.sprite.setTexture(*silenciador.textura);
    silenciador.sprite.setPosition(objetos[0].sprite.getPosition());

    Objeto freno;
    freno.textura = std::make_shared<sf::Texture>();
    freno.textura->loadFromFile("../assets/minijuegoAutotronica/frenoE1.png");
    freno.sprite.setTexture(*freno.textura);
    freno.sprite.setPosition(objetos[1].sprite.getPosition());

    Objeto bateria;
    bateria.textura = std::make_shared<sf::Texture>();
    bateria.textura->loadFromFile("../assets/minijuegoAutotronica/bateriaE1.png");
    bateria.sprite.setTexture(*bateria.textura);
    bateria.sprite.setPosition(objetos[2].sprite.getPosition());

    Objeto luces;
    luces.textura = std::make_shared<sf::Texture>();
    luces.textura->loadFromFile("../assets/minijuegoAutotronica/lucesE1.png");
    luces.sprite.setTexture(*luces.textura);
    luces.sprite.setPosition(objetos[3].sprite.getPosition());

    objetosE1.push_back(silenciador);
    objetosE1[0].sprite.setPosition(objetos[0].sprite.getPosition().x, objetos[0].sprite.getPosition().y + 2);
    objetosE1.push_back(freno);
    objetosE1[1].sprite.setPosition(objetos[1].sprite.getPosition().x, objetos[1].sprite.getPosition().y + 6);
    objetosE1.push_back(bateria);
    objetosE1[2].sprite.setPosition(objetos[2].sprite.getPosition().x, objetos[2].sprite.getPosition().y - 1);
    objetosE1.push_back(luces);
    objetosE1[3].sprite.setPosition(objetos[3].sprite.getPosition().x, objetos[3].sprite.getPosition().y + 2);


    float separacion = 100;
    Opcion opcionA;
    opcionA.seleccionado = false;
    opcionA.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionA.cuadro.setFillColor(sf::Color::Cyan);
    opcionA.cuadro.setOrigin(opcionA.cuadro.getLocalBounds().width / 2, opcionA.cuadro.getLocalBounds().height / 2);
    opcionA.cuadro.setPosition(carro.getPosition().x - (separacion / 2) - (opcionA.cuadro.getLocalBounds().width) - separacion - (opcionA.cuadro.getLocalBounds().width / 2), carro.getPosition().y + carro.getLocalBounds().height);
    opcionA.textura = std::make_shared<sf::Texture>();
    opcionA.textura->loadFromFile("../assets/minijuegoAutotronica/energia.png");
    opcionA.sprite.setTexture(*opcionA.textura);
    opcionA.sprite.setOrigin(opcionA.sprite.getLocalBounds().width / 2, opcionA.sprite.getLocalBounds().height / 2);
    opcionA.sprite.setPosition(opcionA.cuadro.getPosition());

    Opcion opcionB;
    opcionB.seleccionado = false;
    opcionB.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionB.cuadro.setFillColor(sf::Color::Cyan);
    opcionB.cuadro.setOrigin(opcionB.cuadro.getLocalBounds().width / 2, opcionB.cuadro.getLocalBounds().height / 2);
    opcionB.cuadro.setPosition(carro.getPosition().x - (separacion / 2) - (opcionA.cuadro.getLocalBounds().width / 2), opcionA.cuadro.getPosition().y);
    opcionB.textura = std::make_shared<sf::Texture>();
    opcionB.textura->loadFromFile("../assets/minijuegoAutotronica/fusible.png");
    opcionB.sprite.setTexture(*opcionB.textura);
    opcionB.sprite.setOrigin(opcionB.sprite.getLocalBounds().width / 2, opcionB.sprite.getLocalBounds().height / 2);
    opcionB.sprite.setPosition(opcionB.cuadro.getPosition());

    Opcion opcionC;
    opcionC.seleccionado = false;
    opcionC.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionC.cuadro.setFillColor(sf::Color::Cyan);
    opcionC.cuadro.setOrigin(opcionC.cuadro.getLocalBounds().width / 2, opcionC.cuadro.getLocalBounds().height / 2);
    opcionC.cuadro.setPosition(carro.getPosition().x + (separacion / 2) + (opcionA.cuadro.getLocalBounds().width / 2), opcionA.cuadro.getPosition().y);
    opcionC.textura = std::make_shared<sf::Texture>();
    opcionC.textura->loadFromFile("../assets/minijuegoAutotronica/llaveInglesa.png");
    opcionC.sprite.setTexture(*opcionC.textura);
    opcionC.sprite.setOrigin(opcionC.sprite.getLocalBounds().width / 2, opcionC.sprite.getLocalBounds().height / 2);
    opcionC.sprite.setPosition(opcionC.cuadro.getPosition());

    Opcion opcionD;
    opcionD.seleccionado = false;
    opcionD.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionD.cuadro.setFillColor(sf::Color::Cyan);
    opcionD.cuadro.setOrigin(opcionD.cuadro.getLocalBounds().width / 2, opcionD.cuadro.getLocalBounds().height / 2);
    opcionD.cuadro.setPosition(carro.getPosition().x + (separacion / 2) + opcionA.cuadro.getLocalBounds().width + separacion + (opcionA.cuadro.getLocalBounds().width / 2), opcionA.cuadro.getPosition().y);

    opciones.push_back(opcionA);
    opciones.push_back(opcionB);
    opciones.push_back(opcionC);
    opciones.push_back(opcionD);
}
void minijuegoAutotronica::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
        for (auto &opcion : opciones){
            if (opcion.cuadro.getGlobalBounds().contains(posicionEnVentana)) {
                opcion.seleccionado = true;
                opcion.cuadro.setFillColor(sf::Color::Blue);
            } else {
                opcion.seleccionado = false;
                opcion.cuadro.setFillColor(sf::Color::Cyan);
            }
        }
        int i = 0;
        bool contactoFigura;
        for (auto &objeto : objetos){
            if (objeto.sprite.getGlobalBounds().contains(posicionEnVentana)){
                contactoFigura = true;
                break;
            } else {
                contactoFigura = false;
            }
        }
        for (auto &objeto : objetos){
            if (contactoFigura){
                if (objeto.sprite.getGlobalBounds().contains(posicionEnVentana)){
                    objeto.seleccionado = true;
                } else {
                    objeto.seleccionado = false;
                }
            } /* else {
                if (objeto.seleccionado){

                }
            } */
            if (objeto.seleccionado)
            {
                texturaTemporal = *objeto.sprite.getTexture();
                objetoSeleccionado.setTexture(texturaTemporal, true);
                objetoSeleccionado.setScale(objeto.sprite.getScale().x * 1.5, objeto.sprite.getScale().y * 1.5);
                objetoSeleccionado.setOrigin(objetoSeleccionado.getLocalBounds().width / 2, objetoSeleccionado.getLocalBounds().height / 2);
                objetoSeleccionado.setPosition(carro.getPosition().x, carro.getPosition().y + 210);
                cuadro.setSize(sf::Vector2f(objetoSeleccionado.getLocalBounds().width + 50, objetoSeleccionado.getLocalBounds().height + 50));

                cuadro.setOrigin(cuadro.getGlobalBounds().width / 2, cuadro.getGlobalBounds().height / 2);
                cuadro.setPosition(objetoSeleccionado.getPosition().x, objetoSeleccionado.getPosition().y);
                cuadro.setFillColor(sf::Color::Cyan);
            } else {
                objeto.seleccionado = false;
            }
            i++;
        }
        i = 0;

        /* (objetos[3].sprite.getGlobalBounds().contains(posicionEnVentana)) ? arrastrando = true : arrastrando = false; */

    } else if(evento.type == sf::Event::MouseButtonReleased){
        /* arrastrando = false; */
    } else if(evento.type == sf::Event::KeyPressed){
        if (evento.key.code == sf::Keyboard::Enter){
            if (opciones[0].seleccionado && objetos[2].seleccionado){
                objetos[2].arreglado = true;
            } else if(opciones[1].seleccionado && objetos[3].seleccionado){
                objetos[3].arreglado = true;
            } else if(opciones[2].seleccionado && objetos[1].seleccionado){
                objetos[1].arreglado = true;
            } else if(opciones[3].seleccionado && objetos[0].seleccionado){
                objetos[0].arreglado = true;
            }
        }
        int i=0;
        for (auto &objeto : objetos){
            if(!objeto.arreglado){
                break;
            } else {
                if (i == 3)
                {
                    juego->cambiarPantalla(std::make_unique<minijuegoMecatronica>(juego));
                }

            }
            i++;
        }
        i = 0;
        /* if (evento.key.code == sf::Keyboard::Up) {
            objetos[3].sprite.move(0, -1);
        } else if (evento.key.code == sf::Keyboard::Down) {
            objetos[3].sprite.move(0, 1);
        } else if (evento.key.code == sf::Keyboard::Left) {
            objetos[3].sprite.move(-1, 0);
        } else if (evento.key.code == sf::Keyboard::Right) {
            objetos[3].sprite.move(1, 0);
        }
        std::cout << "Posicion X: " << std::to_string(objetos[3].sprite.getPosition().x) << std::endl;
        std::cout << "Posicion Y: " << std::to_string(objetos[3].sprite.getPosition().y) << std::endl; */

    }
}
void minijuegoAutotronica::actualizar(){
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);


    /* if(arrastrando){
        objetos[3].sprite.setPosition(posicionEnVentana);
        std::cout << "posicion: " << std::to_string(objetos[3].sprite.getPosition().x) << ", " << std::to_string(objetos[3].sprite.getPosition().y) << std::endl;
    } */
}
void minijuegoAutotronica::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(carro);

    int i = 0;
    for (auto &objeto : objetos){
        if(!objeto.seleccionado){
            window.draw(objeto.sprite);
        } else {
            window.draw(opciones[0].cuadro);
            window.draw(opciones[1].cuadro);
            window.draw(opciones[2].cuadro);
            window.draw(opciones[3].cuadro);
            window.draw(opciones[0].sprite);
            window.draw(opciones[1].sprite);
            window.draw(opciones[2].sprite);
            window.draw(opciones[3].sprite);
        }

        if(objeto.arreglado){
            window.draw(objetosE1[i].sprite);
        }
        i++;
    }
    i = 0;;
    /* window.draw(objetosE1[0].sprite);
    window.draw(objetosE1[1].sprite);
    window.draw(objetosE1[2].sprite); */
    /* window.draw(objetosE1[3].sprite); */
    window.draw(cuadro);
    window.draw(objetoSeleccionado);
}