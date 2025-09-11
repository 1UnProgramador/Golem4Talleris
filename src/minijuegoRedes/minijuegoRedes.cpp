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

/* std::vector<std::vector<int>> orientacionObjetivo = {
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
}; */
std::vector<std::vector<std::string>> pieza = {
    {"tipoL", "tipoLinea", "tipoInterseccion", "tipoInterseccion", "tipoL", "tipoL", "tipoL", "tipoLinea"},
    {"tipoLinea", "tipoL", "tipoL", "tipoLinea", "tipoL", "tipoL", "tipoInterseccion", "tipoL"},
    {"tipoInterseccion", "tipoCruz", "tipoL", "tipoL", "tipoL", "tipoL", "tipoInterseccion", "tipoL"},
    {"tipoInterseccion", "tipoInterseccion", "tipoInterseccion", "tipoL", "tipoLinea", "tipoL", "tipoInterseccion", "tipoInterseccion"},
    {"tipoL", "tipoLinea", "tipoL", "tipoL", "tipoInterseccion", "tipoLinea", "tipoL", "tipoLinea"},
    {"tipoL", "tipoL", "tipoInterseccion", "tipoLinea", "tipoLinea", "tipoL", "tipoL", "tipoL"},
    {"tipoInterseccion", "tipoInterseccion", "tipoL", "tipoInterseccion", "tipoLinea", "tipoL", "tipoInterseccion", "tipoL"},
    {"tipoLinea", "tipoL", "tipoLinea", "tipoInterseccion", "tipoLinea", "tipoLinea", "tipoInterseccion", "tipoL"}
};

minijuegoRedes::minijuegoRedes(Juego* juego) : Pantalla(juego){
    
    
    malla.resize(pieza.size());
    for (size_t i = 0; i < pieza.size(); i++)
    {
        malla[i].resize(pieza[i].size());
        std::vector<cuadro> fila;
        for (size_t j = 0; j < pieza[i].size(); j++)
        {
            cuadro c;
            c.tipo = pieza[i][j];
            /* c.rotacionObjetivo = orientacionObjetivo[i][j];
            c.rotacion = orientacionDefault[i][j]; */

            c.textura = std::make_shared<sf::Texture>();
            c.textura->loadFromFile("../assets/minijuegoRedes/"+ c.tipo +".png");

            c.sprite.setTexture(*c.textura);
            c.sprite.setOrigin(c.sprite.getGlobalBounds().width / 2, c.sprite.getGlobalBounds().height / 2);
            c.sprite.setScale(3, 3);
            
            float cellW = c.sprite.getGlobalBounds().width;
            float cellH = c.sprite.getGlobalBounds().height;

            float offsetX = (sf::VideoMode::getDesktopMode().width  / 2) - (pieza[j].size() / 2.f) * cellW;
            float offsetY = (sf::VideoMode::getDesktopMode().height / 2) - (pieza.size() / 2.f) * cellH;

            c.sprite.setPosition(offsetX + j * cellW, offsetY + i * cellH);

            /* c.sprite.setPosition(((sf::VideoMode::getDesktopMode().width / 2) - 2 * c.sprite.getGlobalBounds().width) + ((j % (pieza[j].size() + 1)) * c.sprite.getGlobalBounds().width), (sf::VideoMode::getDesktopMode().height / 2) - 2 * c.sprite.getGlobalBounds().height + ((i % (pieza.size() + 1))) * c.sprite.getGlobalBounds().height); */

            /* c.sprite.setRotation(c.rotacion); */

            malla[i][j] = c;

            fila.push_back(c);
        }
        malla.push_back(fila);
    }


}

void minijuegoRedes::ManejarEvento(sf::Event evento){
    for (size_t i = 0; i < pieza.size(); i++)
    {
        for (size_t j = 0; j < pieza[i].size(); j++)
        {
            if(malla[i][j].sprite.getGlobalBounds().contains(posicionEnVentana)){
            if(evento.type == sf::Event::MouseButtonPressed  && evento.mouseButton.button == sf::Mouse::Left){
                malla[i][j].sprite.rotate(90);
                /* malla[i][j].rotacion++; */
            } else if (evento.type == sf::Event::MouseButtonPressed  && evento.mouseButton.button == sf::Mouse::Right){
                malla[i][j].sprite.rotate(-90);
                /* malla[i][j].rotacion--; */
            }
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
    for (size_t i = 0; i < pieza.size(); i++)
    {
        for (size_t j = 0; j < pieza[i].size(); j++)
        {
            window.draw(malla[i][j].sprite);
        }

    }
    /* for(auto& cuadrito : cuadros){
        window.draw(cuadrito.sprite);
    } */
}