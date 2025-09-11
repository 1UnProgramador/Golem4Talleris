#include "../../include/minijuegoRedes/minijuegoRedes.h"
#include "../../include/logica/Juego.h"

const std::string dirCuadros [] = {
    "../assets/minijuegoRedes/linea.png",
    "../assets/minijuegoRedes/interseccion.png",
    "../assets/minijuegoRedes/giroIzquierda.png",
    "../assets/minijuegoRedes/giroDerecha.png",
    "../assets/minijuegoRedes/interseccionDerecha.png",
    "../assets/minijuegoRedes/interseccionIzquierda.png",
};

std::vector<std::vector<int>> orientacionObjetivo = {
    {270, 90, 90, 90},
    {0,  180, 90, 0},
    {180, 0, 90, 0},
    {270, 90, 90, 90}
};

std::vector<std::vector<int>> orientacionDefault = {
    {0, 0, 0, 0},
    {0,  0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
/* std::vector<std::vector<int>> piezaObjetivo = {
    {TIPO_L, TIPO_T, TIPO_I},
    {TIPO_T, TIPO_CRUZ, TIPO_L},
    {TIPO_I, TIPO_L, TIPO_T}
}; */

minijuegoRedes::minijuegoRedes(Juego* juego) : Pantalla(juego){
    int n = 1;
    for (int i = 0; i < orientacionDefault.size(); i++)
    {
        /* code */
    }


    for(auto& direccion : dirCuadros){
        for (int i = 1; i <= 5; i++)
        {
            cuadro cuadrito;
            cuadrito.textura = std::make_shared<sf::Texture>();
            cuadrito.textura->loadFromFile(direccion);
            cuadrito.sprite.setTexture(*cuadrito.textura);
            cuadrito.sprite.setOrigin(cuadrito.sprite.getGlobalBounds().width / 2, cuadrito.sprite.getGlobalBounds().height / 2);
            cuadrito.sprite.setScale(3, 3);
            /* cuadrito.sprite.setPosition(125 * n, 500); */
            cuadros.push_back(cuadrito);
            n++;
        }
    }
    for (int i = 15; i <= 18; i++)
    {
        cuadros.at(i).sprite.rotate(90);
    }

    /* float  anchoCuadros = cuadros.at(0).sprite.getGlobalBounds().width; */
    cuadros.at(10).sprite.setPosition((sf::VideoMode::getDesktopMode().width / 2.0f) - (2.5 * cuadros.at(10).sprite.getGlobalBounds().width), (sf::VideoMode::getDesktopMode().height / 2.0f) + (2.5 * cuadros.at(10).sprite.getGlobalBounds().height));
    cuadros.at(0).sprite.setPosition(cuadros.at(10).sprite.getPosition().x + (cuadros.at(0).sprite.getGlobalBounds().width), cuadros.at(10).sprite.getPosition().y);
    cuadros.at(1).sprite.setPosition(cuadros.at(0).sprite.getPosition().x + cuadros.at(0).sprite.getGlobalBounds().width, cuadros.at(0).sprite.getPosition().y);
    cuadros.at(15).sprite.setPosition(cuadros.at(1).sprite.getPosition().x + cuadros.at(1).sprite.getGlobalBounds().width, cuadros.at(1).sprite.getPosition().y);

    cuadros.at(16).sprite.setPosition(cuadros.at(15).sprite.getPosition().x, cuadros.at(15).sprite.getPosition().y - cuadros.at(15).sprite.getGlobalBounds().height);
    cuadros.at(2).sprite.setPosition(cuadros.at(1).sprite.getPosition().x, cuadros.at(1).sprite.getPosition().y - cuadros.at(1).sprite.getGlobalBounds().height);
    cuadros.at(17).sprite.setPosition(cuadros.at(0).sprite.getPosition().x, cuadros.at(0).sprite.getPosition().y - cuadros.at(0).sprite.getGlobalBounds().height);
    cuadros.at(3).sprite.setPosition(cuadros.at(10).sprite.getPosition().x, cuadros.at(10).sprite.getPosition().y - cuadros.at(10).sprite.getGlobalBounds().height);

    cuadros.at(25).sprite.setPosition(cuadros.at(16).sprite.getPosition().x, cuadros.at(16).sprite.getPosition().y - cuadros.at(16).sprite.getGlobalBounds().height);
    cuadros.at(11).sprite.setPosition(cuadros.at(2).sprite.getPosition().x, cuadros.at(2).sprite.getPosition().y - cuadros.at(2).sprite.getGlobalBounds().height);
    cuadros.at(5).sprite.setPosition(cuadros.at(17).sprite.getPosition().x, cuadros.at(17).sprite.getPosition().y - cuadros.at(17).sprite.getGlobalBounds().height);
    cuadros.at(12).sprite.setPosition(cuadros.at(3).sprite.getPosition().x, cuadros.at(3).sprite.getPosition().y - cuadros.at(3).sprite.getGlobalBounds().height);

    cuadros.at(13).sprite.setPosition(cuadros.at(12).sprite.getPosition().x, cuadros.at(12).sprite.getPosition().y - cuadros.at(12).sprite.getGlobalBounds().height);
    cuadros.at(20).sprite.setPosition(cuadros.at(5).sprite.getPosition().x, cuadros.at(5).sprite.getPosition().y - cuadros.at(5).sprite.getGlobalBounds().height);
    cuadros.at(21).sprite.setPosition(cuadros.at(11).sprite.getPosition().x, cuadros.at(11).sprite.getPosition().y - cuadros.at(11).sprite.getGlobalBounds().height);
    cuadros.at(14).sprite.setPosition(cuadros.at(25).sprite.getPosition().x, cuadros.at(25).sprite.getPosition().y - cuadros.at(25).sprite.getGlobalBounds().height);
}

void minijuegoRedes::ManejarEvento(sf::Event evento){
    for (auto &cuadro : cuadros)
    {
        if(cuadro.sprite.getGlobalBounds().contains(posicionEnVentana)){
            if(evento.type == sf::Event::MouseButtonPressed  && evento.mouseButton.button == sf::Mouse::Left){
                cuadro.sprite.rotate(90);
                cuadro.rotacion++;
            } else if (evento.type == sf::Event::MouseButtonPressed  && evento.mouseButton.button == sf::Mouse::Right){
                cuadro.sprite.rotate(-90);
                cuadro.rotacion--;
            }
        }
    }


}

void minijuegoRedes::actualizar(){
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);
    /* cuadros.at(0).sprite.rotate(90); */
}

void minijuegoRedes::renderizar(sf::RenderWindow& window){
    for(auto& cuadrito : cuadros){
        window.draw(cuadrito.sprite);
    }
}