#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/logica/Juego.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h"

bool dentroVista(const sf::Vector2f& pos, const sf::View& vista/* , const sf::RenderWindow& window */);

minijuegoPaginaWeb::minijuegoPaginaWeb(Juego* juego) : Pantalla(juego){
    int n = 1;
    fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf");
    texturaFlechaSeleccionar.loadFromFile("../assets/minijuegoPagina/flecha.png");
    for(auto& texto : textosBloques){
        Bloque bloque;
        bloque.texto.setString(texto);
        bloque.rectangulo.setSize(sf::Vector2f(500, 200));
        bloque.rectangulo.setPosition(50, 50 + (bloque.rectangulo.getSize().y * n));
        bloque.rectangulo.setFillColor(sf::Color(255, 0, 0));
        bloque.texto.setFont(fuente);
        bloque.texto.setString(texto);
        bloque.texto.setFillColor(sf::Color::White);
        bloque.texto.setCharacterSize(50);
        bloque.texto.setPosition(bloque.rectangulo.getPosition());
        bloque.flecha.setTexture(texturaFlechaSeleccionar);
        bloque.flecha.setScale(2, 2);
        bloques.push_back(bloque);
        n++;
    }

    /* vistaCodigo.setSize(juego->getWindow().getSize().x, juego->getWindow().getSize().x); */
    vistaCodigo.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.7f));
    /* vistaPanel.setSize(juego->getWindow().getSize().x, juego->getWindow().getSize().x); */
    vistaPanel.setViewport(sf::FloatRect(0.f, 0.7f, 0.5f, 0.3f));
    /* vistaPagina.setSize(juego->getWindow().getSize().x, juego->getWindow().getSize().x); */
    vistaPagina.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    fondoCodigo.setPosition(0, 0);
    fondoCodigo.setSize(sf::Vector2f(2000, 2000));
    fondoCodigo.setFillColor(sf::Color(49, 50, 68));

    fondoPanel.setPosition(0, 0);
    fondoPanel.setSize(sf::Vector2f(1000, 2000));
    fondoPanel.setFillColor(sf::Color(88, 91, 112));

    fondoPagina.setPosition(0, 0);
    fondoPagina.setSize(sf::Vector2f(2000, 2000));
    fondoPagina.setFillColor(sf::Color(69, 71, 90));

    pagina.setSize(sf::Vector2f(500, 200));
    pagina.setOrigin(pagina.getSize().x / 2, pagina.getSize().y / 2);
    pagina.setPosition(vistaPagina.getSize().x / 2, vistaPagina.getSize().y / 2);
    pagina.setFillColor(sf::Color(0, 255, 0));

    objetivo.Texto.setFont(fuente);
    objetivo.Texto.setString("a");
    objetivo.backgroundColor.White;
    objetivo.textColor.Blue;
    objetivo.fontSize = 12;
    objetivo.layout = 1;


}

void minijuegoPaginaWeb::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
    {
        exit(0);
    } else if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        juego->cambiarPantalla(std::make_unique<minijuegoRedes>(juego));
    } else if(evento.type == sf::Event::MouseWheelScrolled && fondoPanel.getGlobalBounds().contains(mouseEnPanel)){
        if(evento.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel){
            if (evento.mouseWheelScroll.delta > 0 && moviemientoPanel != 0)
            {
                //desplazamiento hacia arriba
                vistaPanel.move(0, -30);
                moviemientoPanel -= 30;
            } else if (evento.mouseWheelScroll.delta < 0)
            {
                vistaPanel.move(0, 30);
                moviemientoPanel +=30;
            }
        }
    } else if(evento.type == sf::Event::MouseButtonPressed){
        for(int i = 0; i <= 5; i++){
            if (bloques[i].rectangulo.getGlobalBounds().contains(mouseEnPanel))
            {
                if (!bloques[i].seleccionado)
                {
                    bloques[i].arrastrando = true;
                    Bloque bloque = bloques[i];

                    bloque.rectangulo.setPosition(mouseEnPanel - bloque.grabOffset);
                    bloque.texto.setPosition(bloque.rectangulo.getPosition());
                    bloque.grabOffset = mouseEnPanel - bloque.rectangulo.getPosition();
                    /* bloque.rectangulo.setPosition(mouseEnPantalla); */



                    copiaBloques.push_back(bloque);
                    bloques[i].seleccionado = true;
                    bloques[i].rectangulo.setFillColor(sf::Color(0, 255, 0));
                } else {
                    /* for(auto& bloqueCopia : copiaBloques){
                        if (bloques[i] == bloqueCopia)
                        {
                            copiaBloques.erase(bloqueCopia);

                        }

                    } */
                    bloques[i].seleccionado = false;
                    bloques[i].arrastrando = false;
                    bloques[i].rectangulo.setFillColor(sf::Color(255, 0, 0));
                }
            }
            for(auto& bloqueCopia : copiaBloques){
                if(bloqueCopia.rectangulo.getGlobalBounds().contains(mouseEnPanel)){
                    bloqueCopia.arrastrando = true;
                    bloqueCopia.grabOffset = mouseEnPanel - bloqueCopia.rectangulo.getPosition();

                } else if (bloqueCopia.rectangulo.getGlobalBounds().contains(mouseEnCodigo)){
                    bloqueCopia.arrastrando = true;
                    bloqueCopia.grabOffset = mouseEnCodigo - bloqueCopia.rectangulo.getPosition();
                }
            }
        }
    } else if(evento.type == sf::Event::MouseButtonReleased){
        for(auto& bloqueCopiaA : copiaBloques){
            for(auto& bloqueCopiaB : copiaBloques){
                if(&bloqueCopiaA == &bloqueCopiaB) continue;
                if(bloqueCopiaA.rectangulo.getGlobalBounds().intersects(bloqueCopiaB.rectangulo.getGlobalBounds()) && !bloqueCopiaA.conectadoU){
                    if(bloqueCopiaA.rectangulo.getPosition().y < bloqueCopiaB.rectangulo.getPosition().y){
                        bloqueCopiaA.rectangulo.setPosition(bloqueCopiaB.rectangulo.getPosition().x, bloqueCopiaB.rectangulo.getPosition().y + bloqueCopiaB.rectangulo.getGlobalBounds().height);
                        bloqueCopiaA.texto.setPosition(bloqueCopiaA.rectangulo.getPosition());
                        bloqueCopiaA.conectadoU = true;
                    } else {
                        bloqueCopiaB.rectangulo.setPosition(bloqueCopiaA.rectangulo.getPosition().x, bloqueCopiaA.rectangulo.getPosition().y + bloqueCopiaA.rectangulo.getGlobalBounds().height);
                        bloqueCopiaB.texto.setPosition(bloqueCopiaB.rectangulo.getPosition());
                        bloqueCopiaB.conectadoU = true;
                    }
                }
            }
            bloqueCopiaA.arrastrando = false;
            if(bloqueCopiaA.pantalla == 2){
                bloqueCopiaA.pantalla = 3;
            }
        }
    }
}

void minijuegoPaginaWeb::actualizar(){
    //posicion verdadera del mouse
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    mouseEnPantalla = juego->getWindow().mapPixelToCoords(posicionMouse);

    //posicion "refinada" en cada pantalla
    mouseEnPanel = juego->getWindow().mapPixelToCoords(posicionMouse, vistaPanel);
    mouseEnCodigo = juego->getWindow().mapPixelToCoords(posicionMouse, vistaCodigo);
    mouseEnPagina   = juego->getWindow().mapPixelToCoords(posicionMouse, vistaPagina);

    juego->getWindow().setView(juego->getWindow().getDefaultView());

    for(auto& bloqueCopia : copiaBloques){
        bloqueCopia.flecha.setPosition(bloqueCopia.rectangulo.getPosition().x + bloqueCopia.rectangulo.getSize().x - bloqueCopia.flecha.getGlobalBounds().width - 10, bloqueCopia.rectangulo.getPosition().y + (bloqueCopia.rectangulo.getSize().y - bloqueCopia.flecha.getGlobalBounds().height) / 2);
        if (bloqueCopia.arrastrando)
        {

            /* if(bloqueCopia.arrastrando){
                bloqueCopia.rectangulo.setPosition(mouseEnPantalla - bloqueCopia.grabOffset);
                bloqueCopia.texto.setPosition(bloqueCopia.rectangulo.getPosition());
            } */
            sf::Vector2u ventana = juego->getWindow().getSize();
            if(mouseEnPantalla.x < ventana.x / 2 && mouseEnPantalla.y <  ventana.y * 0.7){
                //VistaCodiigo
                /* bloqueCopia.rectangulo.setPosition(mouseEnPantalla);
                bloqueCopia.texto.setPosition(bloqueCopia.rectangulo.getPosition()); */
                bloqueCopia.pantalla = 1;
                mouseEnPantallaRelativa = juego->getWindow().mapPixelToCoords(posicionMouse, vistaCodigo);
                bloqueCopia.rectangulo.setSize(sf::Vector2f(500, 90));
            } else if(mouseEnPantalla.x < ventana.x / 2 && mouseEnPantalla.y >=  ventana.y * 0.7){
                //VistaPanel
                /*  bloqueCopia.rectangulo.setPosition(mouseEnPantalla);
                bloqueCopia.texto.setPosition(bloqueCopia.rectangulo.getPosition()); */
                bloqueCopia.pantalla = 2;
                mouseEnPantallaRelativa = juego->getWindow().mapPixelToCoords(posicionMouse, vistaPanel);
                bloqueCopia.rectangulo.setSize(sf::Vector2f(500, 200));
            } else {
                //VistaPágina
                /* bloqueCopia.rectangulo.setPosition(mouseEnPantalla);
                bloqueCopia.texto.setPosition(bloqueCopia.rectangulo.getPosition()); */
                bloqueCopia.pantalla = 3;
                mouseEnPantallaRelativa = juego->getWindow().mapPixelToCoords(posicionMouse, vistaPagina);
            }
            bloqueCopia.rectangulo.setPosition(mouseEnPantallaRelativa - bloqueCopia.grabOffset);
            bloqueCopia.texto.setPosition(bloqueCopia.rectangulo.getPosition());

            /* for(auto& bloqueCopiaB : copiaBloques){
                if(&bloqueCopia == &bloqueCopiaB) continue;
                if(bloqueCopia.rectangulo.getGlobalBounds().intersects(bloqueCopiaB.rectangulo.getGlobalBounds()) && bloqueCopia.conectadoU){

                }
            } */

        }
    }
}

void minijuegoPaginaWeb::renderizar(sf::RenderWindow& window){
    window.setView(vistaPagina);
    window.draw(fondoPagina);
    window.draw(pagina);

    /* for(auto& bloqueCopia : copiaBloques){
        if (dentroVista(bloqueCopia.rectangulo.getPosition(), vistaPagina) && bloqueCopia.pantalla == 3){
            window.draw(bloqueCopia.rectangulo);
            window.draw(bloqueCopia.texto);
            window.draw(bloqueCopia.flecha);
        }
    } */


    window.setView(vistaCodigo);
    window.draw(fondoCodigo);

    for(auto& bloqueCopia : copiaBloques){
        if (dentroVista(bloqueCopia.rectangulo.getPosition(), vistaCodigo) && bloqueCopia.pantalla == 1){
            window.draw(bloqueCopia.rectangulo);
            window.draw(bloqueCopia.texto);
            window.draw(bloqueCopia.flecha);
        }
    }


    window.setView(vistaPanel);
    window.draw(fondoPanel);
    for(auto& bloque : bloques){
        window.draw(bloque.rectangulo);
        window.draw(bloque.texto);
    }

    for(auto& bloqueCopia : copiaBloques){
        if (dentroVista(bloqueCopia.rectangulo.getPosition(), vistaPanel) && bloqueCopia.pantalla == 2){
            window.draw(bloqueCopia.rectangulo);
            window.draw(bloqueCopia.texto);
            window.draw(bloqueCopia.flecha);
        }
    }





    window.setView(window.getDefaultView());
}

// booleano para saber si una posicion está dentrto de una vista
bool dentroVista(const sf::Vector2f& worldPos, const sf::View& v) {
    sf::Vector2f topLeft = v.getCenter() - v.getSize() * 0.5f;
    sf::FloatRect worldRect(topLeft, v.getSize());
    return worldRect.contains(worldPos);
}