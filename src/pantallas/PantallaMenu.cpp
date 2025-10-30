#include "../../include/pantallas/PantallaMenu.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/pantallaCreditos.h"
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/logica/Juego.h"
#include <memory>


PantallaMenu::PantallaMenu(Juego* juego) : Pantalla(juego) {
    // Fondo
    tFondoMenu.loadFromFile("../assets/menu/dibujo fondo menu.jpg");
    FondoMenu.setTexture(tFondoMenu);

    float fX = sf::VideoMode::getDesktopMode().width / FondoMenu.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / FondoMenu.getGlobalBounds().height;
    FondoMenu.setScale(fX, fY);

   // --- Titulo xd ---
    tTitulo.loadFromFile("../assets/menu/titulo juego.png");
    Titulo.setTexture(tTitulo);
    Titulo.setOrigin(Titulo.getGlobalBounds().width / 2, Titulo.getGlobalBounds().height / 2);
    Titulo.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 5);
    Titulo.setScale(1, 1);

    // --- Botón Play ---
    tPlay.loadFromFile("../assets/menu/boton play.png");
    tPlayselec.loadFromFile("../assets/menu/boton play selec.png");
    play.setTexture(tPlay);
    play.setOrigin(play.getGlobalBounds().width / 2, play.getGlobalBounds().height / 2);
    play.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.6);
    play.setScale(4.5, 4.5);

    // --- Botón Extra ---
    tExtra.loadFromFile("../assets/menu/boton extra.png");
    tExtraselec.loadFromFile("../assets/menu/boton extra selec.png");
    Extra.setTexture(tExtra);
    Extra.setOrigin(Extra.getGlobalBounds().width / 2, Extra.getGlobalBounds().height / 2);
    Extra.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.4);
    Extra.setScale(4.5, 4.5);

    // --- Botón Exit ---
    tExit.loadFromFile("../assets/menu/boton exit.png");
    tExitselec.loadFromFile("../assets/menu/boton exit selec.png");
    Exit.setTexture(tExit);
    Exit.setOrigin(Exit.getGlobalBounds().width / 2, Exit.getGlobalBounds().height / 2);
    Exit.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.25);
    Exit.setScale(4.5, 4.5);
}

void PantallaMenu::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Up) {
            opcionSeleccionada--;
            if (opcionSeleccionada < 0) opcionSeleccionada = 2;
        }
        else if (evento.key.code == sf::Keyboard::Down) {
            opcionSeleccionada++;
            if (opcionSeleccionada > 2) opcionSeleccionada = 0;
        }
        else if (evento.key.code == sf::Keyboard::Enter) {
            if (opcionSeleccionada == 0) {
                juego->seleccionado = "imagenDefault";
                juego->cambiarAPrograma = 13;
                juego->instrucciones = "¡Hola y bienvenido a Gollem4Talleris!\n\nTécnica en juego, futuro en marcha. ¡Estas a punto de explorar las especialidades del ITS!";
                juego->botones = false;
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
            }
            else if (opcionSeleccionada == 1) {
                juego->cambiarPantalla(std::make_unique<pantallaCreditos>(juego));
            }
            else if (opcionSeleccionada == 2) {
                juego->getWindow().close();
            }
        }
    }
}

void PantallaMenu::actualizar() {
    // Cambiar textura según selección
    if (opcionSeleccionada == 0) play.setTexture(tPlayselec);
    else play.setTexture(tPlay);

    if (opcionSeleccionada == 1) Extra.setTexture(tExtraselec);
    else Extra.setTexture(tExtra);

    if (opcionSeleccionada == 2) Exit.setTexture(tExitselec);
    else Exit.setTexture(tExit);
}

void PantallaMenu::renderizar(sf::RenderWindow& window) {
    window.draw(FondoMenu);
    window.draw(Titulo);
    window.draw(play);
    window.draw(Extra);
    window.draw(Exit);
    window.draw(texto);
}
