#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"

minijuegoPaginaWeb::minijuegoPaginaWeb(Juego* juego) : Pantalla(juego){
    /* vistaCodigo.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2));
    vistaCodigo.reset(sf::FloatRect(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2, sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2)); */

    vistaCodigo.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
    vistaPanel.setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
    vistaPagina.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    fondoCodigo.setPosition(0, 0);
    fondoCodigo.setSize(sf::Vector2f(2000, 2000));
    fondoCodigo.setFillColor(sf::Color(255, 0, 0));

    fondoPanel.setPosition(0, 0);
    fondoPanel.setSize(sf::Vector2f(2000, 2000));
    fondoPanel.setFillColor(sf::Color(0, 255, 0));

    fondoPagina.setPosition(0, 0);
    fondoPagina.setSize(sf::Vector2f(2000, 2000));
    fondoPagina.setFillColor(sf::Color(0, 0, 255));

    objetivo.fuente.loadFromFile("../../assets/textos/Bangers-Regular.ttf");
    objetivo.Texto.setString("a");
    objetivo.backgroundColor.White;
    objetivo.textColor.Blue;
    objetivo.fontSize = 12;
    objetivo.layout = 1;


}

void minijuegoPaginaWeb::ManejarEvento(sf::Event evento){

}

void minijuegoPaginaWeb::actualizar(){

}

void minijuegoPaginaWeb::renderizar(sf::RenderWindow& window){
    window.setView(vistaCodigo);
    window.draw(fondoCodigo);

    window.setView(vistaPagina);
    window.draw(fondoPagina);

    window.setView(vistaPanel);
    window.draw(fondoPanel);

    

    window.setView(window.getDefaultView());
   /*  window.display(); */
}
