#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Personaje.h"
#include "../include/Obstaculo.h"

int main() {
    //Se inicializan las variables necesarias para el juego
    float VelocidadGolem = 15;
    short duracionCambioColor = 1;


    // Obtener la resolucion de la pantalla y guardarla en una variable
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    
    sf::Music music;
    if (!music.openFromFile("../assets/Undertale-Mettaton-EX-Theme-Death-By-Glamour.ogg"))
        return -1; 

    music.play();

    // Crear una ventana en pantalla completa
    sf::RenderWindow window(desktopMode, "Juego", sf::Style::Fullscreen);

    // Limitar el framerate del objeto creado "window"
    window.setFramerateLimit(60);

    Golem jugador(desktopMode.width / 2, desktopMode.height / 2);
    
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
    
    

    //Cronómetro para usarlo como una mouskey-herramienta (la usaremos mas tarde)
    sf::Clock Cronometro;
    sf::Clock CronometroSpawnEnemigos;

    std::vector<Obstaculo> obstaculos;

    sf::Color colorInicio = sf::Color::Black;
    sf::Color colorFinal = sf::Color(37, 99, 46, 255);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        jugador.update(desktopMode);


        if (CronometroSpawnEnemigos.getElapsedTime().asSeconds() > 0.3f)
        {
            obstaculos.emplace_back(Plataforma.getGlobalBounds().height, Plataforma.getPosition().y);
            obstaculos.emplace_back(Plataforma.getGlobalBounds().height, Plataforma.getPosition().y);
        
            CronometroSpawnEnemigos.restart();
        }

        obstaculos.erase(std::remove_if(obstaculos.begin(), obstaculos.end(), [&jugador](const Obstaculo& obs){return jugador.isCollision(obs);}), obstaculos.end());
        obstaculos.erase(std::remove_if(obstaculos.begin(), obstaculos.end(), [](const Obstaculo& obs) {return obs.getPosX() > 2000;}),obstaculos.end());

        float t = Cronometro.getElapsedTime().asSeconds() / duracionCambioColor;
        if (t > 1.0f) t = 1.0f; // Evita que se pase de 100%

        sf::Uint8 r = colorInicio.r + t * (colorFinal.r - colorInicio.r);
        sf::Uint8 g = colorInicio.g + t * (colorFinal.g - colorInicio.g);
        sf::Uint8 b = colorInicio.b + t * (colorFinal.b - colorInicio.b);
        sf::Uint8 a = colorInicio.a + t * (colorFinal.a - colorInicio.a);

        sf::Color colorActual(r, g, b, a);

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
        
        // Actualiza todos los obstáculos
        for (auto& obs : obstaculos) {
            obs.update();
        }

        

        //Se limpia la pantalla
        window.clear(colorActual);

        //Se dibujan las cosas
        window.draw(Fondo);
        window.draw(FondoCopia);
        window.draw(Plataforma);
        window.draw(jugador);
        // Dibuja todos los obstáculos
        for (auto& obs : obstaculos) {
            window.draw(obs);
        }
        



        window.display();
    }
    return 0;
}



