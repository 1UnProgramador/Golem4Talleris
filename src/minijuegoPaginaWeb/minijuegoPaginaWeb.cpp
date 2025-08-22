#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/logica/Juego.h"

minijuegoPaginaWeb::minijuegoPaginaWeb(Juego* juego) : Pantalla(juego){
    int n = 1;
    fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf");
    std::vector<std::string> textosBloques = {"fuente", "texto", "color de fondo", "color de texto", "tamano de fuente", "centrado titulo"};
    for(const auto& texto : textosBloques){
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
        bloques.push_back(bloque);
        n++;
    }

    vistaCodigo.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.7f));
    vistaPanel.setViewport(sf::FloatRect(0.f, 0.7f, 0.5f, 0.3f));
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
    if(evento.type == sf::Event::MouseWheelScrolled && fondoPanel.getGlobalBounds().contains(mouseEnPanel)){
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
                bloques[i].seleccionado = true;
                bloques[i].rectangulo.setFillColor(sf::Color(0, 255, 0));
            }
        }
    }
}

void minijuegoPaginaWeb::actualizar(){
    //posicion verdadera del mouse
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());

    //posicion "refinada" en cada pantalla
    mouseEnPanel = juego->getWindow().mapPixelToCoords(posicionMouse, vistaPanel);
    mouseEnCodigo = juego->getWindow().mapPixelToCoords(posicionMouse, vistaCodigo);
    mouseEnPagina   = juego->getWindow().mapPixelToCoords(posicionMouse, vistaPagina);

    juego->getWindow().setView(juego->getWindow().getDefaultView());
}

void minijuegoPaginaWeb::renderizar(sf::RenderWindow& window){
    window.setView(vistaCodigo);
    window.draw(fondoCodigo);

    window.setView(vistaPagina);
    window.draw(fondoPagina);
    window.draw(pagina);

    window.setView(vistaPanel);
    window.draw(fondoPanel);
    for(const auto& bloque : bloques){
        window.draw(bloque.rectangulo);
        window.draw(bloque.texto);
    }


    window.setView(window.getDefaultView());
   /*  window.display(); */
}
