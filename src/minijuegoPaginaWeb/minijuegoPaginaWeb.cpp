#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"

minijuegoPaginaWeb::minijuegoPaginaWeb(Juego* juego) : Pantalla(juego){
    /* vistaCodigo.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2));
    vistaCodigo.reset(sf::FloatRect(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2, sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2)); */


    vistaCodigo.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    vistaPagina.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    mundo.setPosition(50, 50);
    mundo.setSize(sf::Vector2f(3000, 30));
    mundo.setFillColor(sf::Color(100, 200, 100));
    jugador.setRadius(20);
    jugador.setFillColor(sf::Color::Red);
    jugador.setPosition(50, 50);

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
    window.draw(mundo);
    /* window.draw(jugador); */

    window.setView(vistaPagina);
    /* window.draw(mundo); */
    window.draw(jugador);

    window.setView(window.getDefaultView());
   /*  window.display(); */
}
