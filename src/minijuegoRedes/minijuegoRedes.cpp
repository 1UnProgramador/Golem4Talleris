#include "../../include/minijuegoTangram/minijuegoTangram.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h"
#include "../../include/logica/Juego.h"
#include <cmath>


/* const std::string dirCuadros [] = {
    "../assets/minijuegoRedes/linea.png",
    "../assets/minijuegoRedes/interseccion.png",
    "../assets/minijuegoRedes/giroIzquierda.png",
    "../assets/minijuegoRedes/giroDerecha.png",
    "../assets/minijuegoRedes/interseccionDerecha.png",
    "../assets/minijuegoRedes/interseccionIzquierda.png",
}; */

std::vector<std::vector<int>> orientacionObjetivo = {
    {270, 90, 90, 90, 0, 270, 0, 0},
    {0, 270, 90, 0, 180, 90, 0, 90},
    {0, 0, 0, 180, 0, 270, 270, 0},
    {0, 270, 270, 0, 0, 180, 90, 180},
    {180, 90, 0, 180, 270, 90, 90, 0},
    {270,  0, 0, 90, 90, 0, 270, 90},
    {0, 180, 180, 90, 90, 90, 0, 0},
    {0, 180, 90, 270, 90, 90, 270, 90}
};

std::vector<std::vector<int>> orientacionObjetivo2 = {
    {270, 0, 270, 0, 270, 0, 0, 0},
    {180, 180, 0, 180, 0, 0, 90, 180},
    {270, 90, 180, 0, 0, 0, 180, 90},
    {0, 90, 0, 0, 0, 270, 90, 0},
    {0, 270, 90, 0, 180, 0, 180, 90},
    {180,  0, 90, 180, 270, 0, 90, 0},
    {270, 90, 270, 0, 90, 180, 0, 0},
    {180, 90, 90, 180, 0, 90, 270, 90}
};

/* std::vector<std::vector<int>> orientacionDefault = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0,  0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0,  0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
}; */
std::vector<std::vector<std::string>> pieza = {
    {"tipoL", "tipoLinea", "tipoInterseccion", "tipoInterseccion", "tipoL", "tipoL", "tipoL", "tipoLineaI"},
    {"tipoLinea", "tipoL", "tipoL", "tipoLinea", "tipoL", "tipoL", "tipoInterseccion", "tipoL"},
    {"tipoInterseccion", "tipoCruz", "tipoL", "tipoL", "tipoL", "tipoL", "tipoInterseccion", "tipoL"},
    {"tipoInterseccion", "tipoInterseccion", "tipoInterseccion", "tipoL", "tipoLinea", "tipoL", "tipoInterseccion", "tipoInterseccion"},
    {"tipoL", "tipoLinea", "tipoL", "tipoL", "tipoInterseccion", "tipoLinea", "tipoL", "tipoLinea"},
    {"tipoL", "tipoL", "tipoInterseccion", "tipoLinea", "tipoLinea", "tipoL", "tipoL", "tipoL"},
    {"tipoInterseccion", "tipoInterseccion", "tipoL", "tipoInterseccion", "tipoLinea", "tipoL", "tipoInterseccion", "tipoL"},
    {"tipoLineaI", "tipoL", "tipoLinea", "tipoInterseccion", "tipoLinea", "tipoLinea", "tipoInterseccion", "tipoL"}
};
std::vector<std::vector<std::string>> pieza2 = {
    {"tipoL", "tipoL", "tipoL", "tipoL", "tipoL", "tipoL", "tipoLI", "tipoL"},
    {"tipoL", "tipoInterseccion", "tipoLinea", "tipoL", "tipoCruz", "tipoCruz", "tipoInterseccion", "tipoInterseccion"},
    {"tipoL", "tipoL", "tipoL", "tipoL", "tipoLinea", "tipoLinea", "tipoL", "tipoL"},
    {"tipoInterseccion", "tipoLinea", "tipoL", "tipoLinea", "tipoInterseccion", "tipoInterseccion", "tipoInterseccion", "tipoL"},
    {"tipoLinea", "tipoL", "tipoL", "tipoLinea", "tipoL", "tipoL", "tipoL", "tipoL"},
    {"tipoL", "tipoCruz", "tipoLinea", "tipoInterseccion", "tipoL", "tipoCruz", "tipoLinea", "tipoL"},
    {"tipoL", "tipoL", "tipoL", "tipoCruz", "tipoL", "tipoL", "tipoL", "tipoLinea"},
    {"tipoL", "tipoLinea", "tipoL", "tipoL","tipoInterseccionI", "tipoLinea", "tipoInterseccion", "tipoL"}
};

minijuegoRedes::minijuegoRedes(Juego* juego) : Pantalla(juego){
    fallo.setSize(sf::Vector2f(2000, 2000));
    fallo.setFillColor(sf::Color(255, 0, 0, 0));
    fallo.setOrigin(fallo.getGlobalBounds().width / 2, fallo.getGlobalBounds().height / 2);
    fallo.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf");


    texturaFlecha.loadFromFile("../assets/minijuegoRedes/flecha.png");
    flecha1.setTexture(texturaFlecha);
    flecha2.setTexture(texturaFlecha);
    flecha1.setOrigin(flecha1.getGlobalBounds().width / 2, flecha1.getGlobalBounds().height / 2);
    flecha2.setOrigin(flecha2.getGlobalBounds().width / 2, flecha2.getGlobalBounds().height / 2);
    flecha1.setScale(2, 2);
    flecha2.setScale(2, 2);

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
            c.sprite.setScale(2, 2);

            float cellW = c.sprite.getGlobalBounds().width;
            float cellH = c.sprite.getGlobalBounds().height;

            float offsetX = (sf::VideoMode::getDesktopMode().width  / 2) - (pieza[j].size() / 2.f) * cellW;
            float offsetY = (sf::VideoMode::getDesktopMode().height / 2) - (pieza.size() / 2.f) * cellH;

            c.sprite.setPosition(offsetX + j * cellW, offsetY + i * cellH);

            /* c.sprite.setPosition(((sf::VideoMode::getDesktopMode().width / 2) - 2 * c.sprite.getGlobalBounds().width) + ((j % (pieza[j].size() + 1)) * c.sprite.getGlobalBounds().width), (sf::VideoMode::getDesktopMode().height / 2) - 2 * c.sprite.getGlobalBounds().height + ((i % (pieza.size() + 1))) * c.sprite.getGlobalBounds().height); */

            /* c.sprite.setRotation(c.rotacion); */

            malla[i][j] = c;

            fila.push_back(c);

            /* if(malla[i][j].tipo == "tipoLineaI"){

            } */
        }
        malla.push_back(fila);
    }
    tiempo.setFont(fuente);
    tiempo.setScale(2, 2);
    tiempo.setPosition(0, 0);
    tiempoRestante.restart();
    tiempo.setString(std::to_string(tiempoInt));
}

void minijuegoRedes::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::MouseButtonPressed) {
        bufferClick.loadFromFile("../assets/minijuegoRedes/click.mp3");
        click.setBuffer(bufferClick);
        for (size_t i = 0; i < pieza.size(); i++)
        {
            for (size_t j = 0; j < pieza[i].size(); j++)
            {
                if(malla[i][j].tipo == "tipoLineaI" || malla[i][j].tipo == "tipoInterseccionI" || malla[i][j].tipo == "tipoLI"){

                } else {
                    if(malla[i][j].sprite.getGlobalBounds().contains(posicionEnVentana)){
                        if(evento.type == sf::Event::MouseButtonPressed  && evento.mouseButton.button ==    sf::Mouse::Left){
                            malla[i][j].sprite.rotate(90);
                            click.play();

                            /* malla[i][j].rotacion++; */
                        } else if (evento.type == sf::Event::MouseButtonPressed  && evento.mouseButton. button == sf::Mouse::Right){
                            malla[i][j].sprite.rotate(-90);
                            click.play();

                        }
                        if (malla[i][j].tipo == "tipoLinea" && (malla[i][j].sprite.getRotation() == orientacionObjetivo[i][j] * 2))
                        {
                            malla[i][j].sprite.setRotation(orientacionObjetivo[i][j]);
                        } else if (malla[i][j].tipo == "tipoCruz" && (malla[i][j].sprite.getRotation() == 0 || malla[i][j].sprite.getRotation() == 90 || malla[i][j].sprite.getRotation() == 180 || malla[i][j].sprite.getRotation() == 270))
                        {
                            malla[i][j].sprite.setRotation(orientacionObjetivo[i][j]);
                        }

                    }
                }
            }

        }
    }

    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter)
    {
        bool iguales = true;

        // 1. Comprobar TODA la malla contra el objetivo
        for (size_t i = 0; i < pieza.size() && iguales; i++)
        {
            for (size_t j = 0; j < pieza[i].size(); j++)
            {
                if (malla[i][j].sprite.getRotation() != orientacionObjetivo[i][j])
                {
                    iguales = false;
                    break; // ya no hace falta seguir
                }
            }
        }

        // 2. Si son iguales
        if (iguales)
        {
            // Primera fase → pasar a pieza2
            if (pieza != pieza2)
            {
                orientacionObjetivo = orientacionObjetivo2;
                pieza = pieza2;

                malla.clear();
                malla.resize(pieza.size());
                for (size_t i = 0; i < pieza.size(); i++)
                {
                    malla[i].resize(pieza[i].size());
                    for (size_t j = 0; j < pieza[i].size(); j++)
                    {
                        cuadro c;
                        c.tipo = pieza[i][j];

                        c.textura = std::make_shared<sf::Texture>();
                        c.textura->loadFromFile("../assets/minijuegoRedes/" + c.tipo + ".png");

                        c.sprite.setTexture(*c.textura);
                        c.sprite.setOrigin(c.sprite.getGlobalBounds().width / 2.f,
                                        c.sprite.getGlobalBounds().height / 2.f);
                        c.sprite.setScale(2.f, 2.f);

                        float cellW = c.sprite.getGlobalBounds().width;
                        float cellH = c.sprite.getGlobalBounds().height;

                        float offsetX = (sf::VideoMode::getDesktopMode().width  / 2.f) - (pieza[i].size() / 2.f) * cellW;
                        float offsetY = (sf::VideoMode::getDesktopMode().height / 2.f) - (pieza.size() / 2.f) * cellH;

                        c.sprite.setPosition(offsetX + j * cellW, offsetY + i * cellH);

                        malla[i][j] = c;  // ¡ya está!
                    }
                }

                tiempoRestante.restart();
                tiempo.setString(std::to_string(tiempoInt));
            }
            // Segunda fase → cambiar de pantalla
            else
            {
                juego->cambiarPantalla(std::make_unique<minijuegoTangram>(juego));
            }
        }
        else
        {
            falloEvento = 1;
            fallo.setFillColor(sf::Color(255, 0, 0, 255));
        }
    }

}

void minijuegoRedes::actualizar(){
    tiempo.setString(std::to_string(static_cast<int>(round(tiempoInt - tiempoRestante.getElapsedTime().asSeconds()))));
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);
    /* cuadros.at(0).sprite.rotate(90); */
    if (falloEvento == 1)
    {
        float totalAnimacion = 2.0f;
        float decrementoAlpha = 255.0f / totalAnimacion;
        float deltaTime = clock.restart().asSeconds();
        sf::Color colorActual = fallo.getFillColor();

        if (colorActual.a > 0) {
            colorActual.a -= decrementoAlpha * deltaTime;
            if (colorActual.a < 0) {
                colorActual.a = 0;
                falloEvento = 0;
            }
            fallo.setFillColor(colorActual); // Aplicamos el nuevo color
        }
    }
    if (tiempoRestante.getElapsedTime().asSeconds() >= tiempoInt)
    {
        /* que lo devuelva cuando Sam haga la pantalla */
        tiempoRestante.restart();
        tiempo.setString(std::to_string(tiempoInt));
    }


}

void minijuegoRedes::renderizar(sf::RenderWindow& window){

    for (size_t i = 0; i < pieza.size(); i++)
    {
        for (size_t j = 0; j < pieza[i].size(); j++)
        {
            window.draw(malla[i][j].sprite);
        }

    }
    /* window.draw(flecha1);
    window.draw(flecha2); */
    window.draw(fallo);
    window.draw(tiempo);
    /* for(auto& cuadrito : cuadros){
        window.draw(cuadrito.sprite);
    } */
}