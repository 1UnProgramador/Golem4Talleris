#include <SFML/Graphics.hpp>
#include "../include/Personaje.h"

int main() {
    //Se inicializan las variables necesarias para el juego
    float VelocidadGolem = 10;

    // Obtener la resolucion de la pantalla y guardarla en una variable
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Crear una ventana en pantalla completa
    sf::RenderWindow window(desktopMode, "Juego", sf::Style::Fullscreen);

    // Limitar el framerate del objeto creado "window"
    window.setFramerateLimit(60);

    Golem Golem(desktopMode.width / 2, desktopMode.height / 2);
    
    sf::Sprite Plataforma;
    sf::Texture TPlataforma;

    sf::Sprite Fondo;
    sf::Sprite FondoCopia;
    sf::Texture TFondo;


    TPlataforma.loadFromFile("../assets/PLATAFORMATEMPORAL.png");
    Plataforma.setTexture(TPlataforma);

    TFondo.loadFromFile("../assets/FONDOTEMPORAL.png");
    Fondo.setTexture(TFondo);
    FondoCopia.setTexture(TFondo);

    //Indicar la Posicion de los objetos
    Plataforma.setPosition((desktopMode.width / 2) - 379, (desktopMode.height / 2) - 309);
    FondoCopia.setPosition(0, -FondoCopia.getGlobalBounds().height);
    


    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Golem.update(desktopMode);


        //El fondo se mueve
        Fondo.move(0, VelocidadGolem);
        FondoCopia.move(0, VelocidadGolem);

        if (Fondo.getPosition().y > desktopMode.height)
        {
            Fondo.setPosition(0, -FondoCopia.getGlobalBounds().height);
        }
        if (FondoCopia.getPosition().y > desktopMode.height)
        {
            FondoCopia.setPosition(0, -FondoCopia.getGlobalBounds().height);
        }
        
        

        //Se limpia la pantalla
        window.clear();

        //Se dibujan las cosas
        window.draw(Fondo);
        window.draw(FondoCopia);
        window.draw(Plataforma);
        window.draw(Golem);


        window.display();
    }
    return 0;
}



