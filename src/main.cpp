#include <SFML/Graphics.hpp>
int main() {
    //Se inicializan las variables necesarias para el juego
    float VelocidadGolem = 10;

    // Obtener la resolucion de la pantalla y guardarla en una variable
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Crear una ventana en pantalla completa
    sf::RenderWindow window(desktopMode, "Juego", sf::Style::Fullscreen);

    // Limitar el framerate del objeto creado "window"
    window.setFramerateLimit(60);

    //Se llaman a los sprites y sus texturas
    sf::Sprite Golem;
    sf::Texture TGolem;

    sf::Sprite Plataforma;
    sf::Texture TPlataforma;

    TGolem.loadFromFile("../assets/PJTEMPORAL.png");
    Golem.setTexture(TGolem);

    TPlataforma.loadFromFile("../assets/FONDOTEMPORAL.png");
    Plataforma.setTexture(TPlataforma);

    //Indicar la Posicion de los objetos
    Golem.setPosition((desktopMode.width)/2, (desktopMode.height)/2);
    Plataforma.setPosition((desktopMode.width/2)-379, (desktopMode.height/2)-309);


    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Se verifica si hay alguna tecla presionada
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            Golem.move(0, -VelocidadGolem);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Golem.move(-VelocidadGolem, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Golem.move(VelocidadGolem, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            Golem.move(0, VelocidadGolem);
        }

        //No se puede salir de la plataforma
        if (Golem.getPosition().x < (desktopMode.width/2)-379){
            Golem.setPosition((desktopMode.width/2)-379, Golem.getPosition().y);
        }
        if (Golem.getPosition().x > (desktopMode.width/2)+379){
            Golem.setPosition((desktopMode.width/2)+379, Golem.getPosition().y);
        }
        if (Golem.getPosition().y < (desktopMode.height/2)-309){
            Golem.setPosition(Golem.getPosition().x, (desktopMode.height/2)-309);
        }
        if (Golem.getPosition().y > (desktopMode.height/2)+309){
            Golem.setPosition(Golem.getPosition().x, (desktopMode.height/2)+309);
        }
        

        //Se limpia la pantalla
        window.clear();

        //Se dibujan las cosas
        window.draw(Plataforma);
        window.draw(Golem);


        window.display();
    }
    return 0;
}


