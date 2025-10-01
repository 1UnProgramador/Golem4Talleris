#include "../../include/logica/Juego.h"
#include "../../include/minijuegoAutotronica/minijuegoAutotronica.h"
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
    std::vector<std::string> nombresObjetos = {"silenciadorE2", "frenoE2", "bateriaE2"};
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

    objetos[0].sprite.setPosition(420, 254);

    posicionesObjetos.push_back(objetos[0].sprite.getPosition());
    /* silenciador.setTexture(tSilenciador); */
    /* silenciador.setPosition(420, 254); */

    objetos[1].sprite.setPosition(788, 241);

    posicionesObjetos.push_back(objetos[1].sprite.getPosition());
    /* freno.setTexture(tFreno); */
    /* freno.setPosition(788, 241); */

    objetos[2].sprite.setPosition(803, 200);

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

    objetosE1.push_back(silenciador);
    objetosE1[0].sprite.setPosition(objetos[0].sprite.getPosition().x - 1, objetos[0].sprite.getPosition().y + 2);
    objetosE1.push_back(freno);
    objetosE1[1].sprite.setPosition(objetos[1].sprite.getPosition().x, objetos[1].sprite.getPosition().y + 5);
    objetosE1.push_back(bateria);
    objetosE1[2].sprite.setPosition(objetos[2].sprite.getPosition());


    float separacion = 100;
    Opcion opcionA;
    opcionA.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionA.cuadro.setFillColor(sf::Color::Cyan);
    opcionA.cuadro.setOrigin(opcionA.cuadro.getLocalBounds().width / 2, opcionA.cuadro.getLocalBounds().height / 2);
    opcionA.cuadro.setPosition(carro.getPosition().x - (separacion / 2) - (opcionA.cuadro.getLocalBounds().width) - separacion - (opcionA.cuadro.getLocalBounds().width / 2), carro.getPosition().y + carro.getLocalBounds().height);

    Opcion opcionB;
    opcionB.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionB.cuadro.setFillColor(sf::Color::Cyan);
    opcionB.cuadro.setOrigin(opcionB.cuadro.getLocalBounds().width / 2, opcionB.cuadro.getLocalBounds().height / 2);
    opcionB.cuadro.setPosition(carro.getPosition().x - (separacion / 2) - (opcionA.cuadro.getLocalBounds().width / 2), opcionA.cuadro.getPosition().y);

    Opcion opcionC;
    opcionC.cuadro.setSize(sf::Vector2f(objetos[0].sprite.getLocalBounds().width + 50, objetos[0].sprite.getLocalBounds().height + 50));
    opcionC.cuadro.setFillColor(sf::Color::Cyan);
    opcionC.cuadro.setOrigin(opcionC.cuadro.getLocalBounds().width / 2, opcionC.cuadro.getLocalBounds().height / 2);
    opcionC.cuadro.setPosition(carro.getPosition().x + (separacion / 2) + (opcionA.cuadro.getLocalBounds().width / 2), opcionA.cuadro.getPosition().y);

    Opcion opcionD;
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
        int i = 0;
        for (auto &objeto : objetos){
            (objeto.sprite.getGlobalBounds().contains(posicionEnVentana)) ? objeto.seleccionado = true : objeto.seleccionado = false;
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
            } /* else {
                objeto.seleccionado = false;
            } */
            i++;
        }
        i = 0;
        /* for (int i = 0; i <= 7; i++)
        {
            (bateria.getGlobalBounds().contains(posicionEnVentana)) ? arrastrando = true : arrastrando = false;
        } */
    } else if(evento.type == sf::Event::MouseButtonReleased){
        /* arrastrando = false; */
    } else if(evento.type == sf::Event::KeyPressed){
        /* if (evento.key.code == sf::Keyboard::Up) {
            bateria.move(0, -1);
        } else if (evento.key.code == sf::Keyboard::Down) {
            bateria.move(0, 1);
        } else if (evento.key.code == sf::Keyboard::Left) {
            bateria.move(-1, 0);
        } else if (evento.key.code == sf::Keyboard::Right) {
            bateria.move(1, 0);
        }
        std::cout << "Posicion X: " << std::to_string(bateria.getPosition().x) << std::endl;
        std::cout << "Posicion Y: " << std::to_string(bateria.getPosition().y) << std::endl;
        */
    }
}
void minijuegoAutotronica::actualizar(){
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);
    /* if(arrastrando){
        bateria.setPosition(posicionEnVentana);
        std::cout << "posicion: " << std::to_string(bateria.getPosition().x) << ", " << std::to_string(bateria.getPosition().y) << std::endl;
    } */
}
void minijuegoAutotronica::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(carro);
    int i = 0;
    for (auto &objeto : objetos){
        if(!objeto.seleccionado){
            window.draw(objeto.sprite);
        }
        window.draw(opciones[i].cuadro);
        if(objeto.arreglado){

        }
        i++;
    }

    /* window.draw(objetosE1[0].sprite);
    window.draw(objetosE1[1].sprite);
    window.draw(objetosE1[2].sprite); */

    window.draw(cuadro);
    window.draw(objetoSeleccionado);
}