#include "../../include/pantallas/PantallaMenu.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/pantallaCreditos.h"
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/logica/Juego.h"
#include "../../src/logica/assetManager.h"
#include <memory>


PantallaMenu::PantallaMenu(Juego* juego) : Pantalla(juego) {
    MusicManager::getInstancia().reproducir(musicaHub_wav, musicaHub_wav_len, "menu", true, 70.f);
    sonido.openFromMemory(sonido3_wav, sonido3_wav_len);
    sonido.setVolume(100.f);
    // Fondo
    tFondoMenu.loadFromMemory(dibujoFondoMenu_jpg, dibujoFondoMenu_jpg_len);
    FondoMenu.setTexture(tFondoMenu);

    float fX = sf::VideoMode::getDesktopMode().width / FondoMenu.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / FondoMenu.getGlobalBounds().height;
    FondoMenu.setScale(fX, fY);

   // --- Titulo xd ---
    tTitulo.loadFromMemory(tituloJuego_png, tituloJuego_png_len);
    Titulo.setTexture(tTitulo);
    Titulo.setOrigin(Titulo.getGlobalBounds().width / 2, Titulo.getGlobalBounds().height / 2);
    Titulo.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 5);
    Titulo.setScale(1, 1);

    // --- Botón Play ---
    tPlay.loadFromMemory(botonPlay_png, botonPlay_png_len);
    tPlayselec.loadFromMemory(botonPlaySelec_png, botonPlaySelec_png_len);
    play.setTexture(tPlay);
    play.setOrigin(play.getGlobalBounds().width / 2, play.getGlobalBounds().height / 2);
    play.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.6);
    play.setScale(4.5, 4.5);

    // --- Botón Extra ---
    tExtra.loadFromMemory(botonExtra_png, botonExtra_png_len);
    tExtraselec.loadFromMemory(botonExtraSelec_png, botonExtra_png_len);
    Extra.setTexture(tExtra);
    Extra.setOrigin(Extra.getGlobalBounds().width / 2, Extra.getGlobalBounds().height / 2);
    Extra.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.4);
    Extra.setScale(4.5, 4.5);

    // --- Botón Exit ---
    tExit.loadFromMemory(botonExit_png, botonExit_png_len);
    tExitselec.loadFromMemory(botonExitSelec_png, botonExitSelec_png_len);
    Exit.setTexture(tExit);
    Exit.setOrigin(Exit.getGlobalBounds().width / 2, Exit.getGlobalBounds().height / 2);
    Exit.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.25);
    Exit.setScale(4.5, 4.5);
}

void PantallaMenu::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
            opcionSeleccionada--;
            sonido.play();
            if (opcionSeleccionada < 0) opcionSeleccionada = 2;
        }
        else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
            opcionSeleccionada++;
            sonido.play();
            if (opcionSeleccionada > 2) opcionSeleccionada = 0;
        }
        else if (evento.key.code == sf::Keyboard::Enter) {
            if (opcionSeleccionada == 0) {
                juego->seleccionado = "imagenDefault";
                juego->cambiarAPrograma = 13;

                juego->backspace = false;
                juego->enter = false;
                juego->esc = true;
                juego->flechas = true;
                juego->mouse = false;
                juego->space = false;
                juego->wasd = true;

                juego->instrucciones = "¡Hola y bienvenido a Gollem4Talleris!\nTécnica en juego, futuro en marcha. ¡Estas a punto de explorar las especialidades del ITS!\nNota: en las pantallas de carga aparecerán al lado los controles del minijuego que elijas";
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
