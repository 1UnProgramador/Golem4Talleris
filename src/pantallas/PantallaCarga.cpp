#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

#include "../../include/pantallas/PantallaCarga.h"

#include "../../include/pantallas/PantallaSeleccionar.h"

#include "../../include/pantallas/informatica.h"
#include "../../include/pantallas/electricidad.h"
#include "../../include/pantallas/Metalmecanica.h"
#include "../../include/pantallas/DisenoTecnico.h"

#include "../../include/logica/Juego.h"

#include "../../include/minijuegoPonchar/minijuegoPonchar.h"
#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/minijuegoTangram/minijuegoTangram.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"
#include "../../include/minijuegoDisenoArquitectonico/minijuegoDisenoArquitectonico.h"
#include "../../include/minijuegoAutotronica/minijuegoAutotronica.h"
#include "../../include/minijuegoTopografia/minijuegoTopografia.h"
#include "../../include/minijuegorandomxd/minijuegorandomxd.h"
#include "../../include/minijuegoElectronicaYControl/minijuegoElectronicaYControl.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h"
#include "../../include/minijuegoSoldadura/minijuegoSoldadura.h"


std::string wrapTextString(const std::string& text, const sf::Font& font, unsigned int characterSize, float maxWidth) {

    sf::Text tempText("", font, characterSize);
    std::istringstream stream(text);
    std::string word;
    std::string line;
    std::string wrappedText;

    while (std::getline(stream, word, ' ')) {
        std::string testLine = line + (line.empty() ? "" : " ") + word;
        tempText.setString(testLine);

        // Si sobrepasa el ancho, salta de línea
        if (tempText.getLocalBounds().width > maxWidth) {
            wrappedText += line + "\n";
            line = word;
        } else {
            line = testLine;
        }
    }

    wrappedText += line; // última línea
    return wrappedText;
}

std::wstring utf8_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(str);
}
const std::string Instrumentalizacion [] = {
    "¿Sabias que en P1 se aprende a interconectar redes?",
    "Por otra parte en P2, aparte de programar paginas podras hacer bases de datos con SQL",
    "En P3 haras simulaciones de demoliciones realistas junto a algunos rompecabezas",
    "En P4 podrás armar tu propio robot haciendo uso de electronica y electricidad",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12"
};

PantallaCarga::PantallaCarga(Juego* juego) : Pantalla(juego){

    tFondo.loadFromFile("../assets/fondo.png");
    tFondo.setRepeated(true);
    tFondo.setSmooth(false);

    fondo.setTexture(tFondo);
    w = juego->getWindow().getSize().x;
    h = juego->getWindow().getSize().y;

    fondo.setTextureRect(sf::IntRect(0, 0, w, h));

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);


    fondo.setPosition(0, 0);


    if (!fuente.loadFromFile("../assets/textos/Ubuntu-Bold.ttf")) {
        std::cerr << "No se pudo cargar la fuente";
    }
    /* fuente.loadFromFile(); */
    imagen.loadFromFile("../assets/pantallaCarga/" + juego->seleccionado + ".jpg");
    sImagen.setTexture(imagen);


    cBorde.setSize(sf::Vector2f(550, 650));
    cRelleno.setSize(sf::Vector2f(544, 644));
    cBorde.setFillColor(sf::Color(255, 255, 255));
    cRelleno.setFillColor(sf::Color(0, 0, 0));
    cBorde.setOrigin(cBorde.getGlobalBounds().width / 2, cBorde.getGlobalBounds().height / 2);
    cRelleno.setOrigin(cRelleno.getGlobalBounds().width / 2, cRelleno.getGlobalBounds().height / 2);
    cRelleno.setPosition((sf::VideoMode::getDesktopMode().width / 2.0f ), (sf::VideoMode::getDesktopMode().height / 2.0f) - 50);
    cBorde.setPosition(sf::VideoMode::getDesktopMode().width / 2.0f , (sf::VideoMode::getDesktopMode().height / 2.0f) - 50);


    float ffX = cRelleno.getGlobalBounds().width / sImagen.getGlobalBounds().width;
    float ffY = (cRelleno.getGlobalBounds().height / 2) / sImagen.getGlobalBounds().height;

    sImagen.setScale(ffX, ffY);
    sImagen.setOrigin(sImagen.getLocalBounds().width / 2, 0);
    sImagen.setPosition(cRelleno.getPosition().x, (cRelleno.getPosition().y - (cRelleno.getGlobalBounds().height / 2)) + 5 /* + (sImagen.getGlobalBounds().height) + 5 */);

    bienvenida.setFont(fuente);
    bienvenida.setString(utf8_to_wstring(wrapTextString(juego->instrucciones, fuente, 30, cRelleno.getGlobalBounds().width)));
    bienvenida.setCharacterSize(30);
    bienvenida.setOrigin(bienvenida.getGlobalBounds().width / 2, 0);
    bienvenida.setPosition(cRelleno.getPosition().x, sImagen.getPosition(). y + sImagen.getGlobalBounds().height);

    int size = sizeof(Instrumentalizacion)/sizeof(*Instrumentalizacion);
    srand(time(NULL));
    texto.setFont(fuente);
    texto.setString("Dato curioso: " + Instrumentalizacion[rand()%size]);
    texto.setCharacterSize(40);
    texto.setOrigin(texto.getLocalBounds().left + texto.getLocalBounds().width / 2.0f , texto.getLocalBounds().top + texto.getLocalBounds().height / 2.0f);
    barraCarga.setSize({50, 50});
    barraCarga.setFillColor(sf::Color(0, 0, 255));
    barraCarga.setPosition(0, sf::VideoMode::getDesktopMode().height - barraCarga.getGlobalBounds().height);
    texto.setPosition(sf::VideoMode::getDesktopMode().width / 2.0f, barraCarga.getPosition().y - texto.getGlobalBounds().height);

    int separacion = 100;
    if (juego->botones)
    {
        botonFacil.loadFromFile("../assets/menu/facil.png");
        botonFacilSeleccionado.loadFromFile("../assets/menu/facilSeleccionado.png");
        bFacil.setTexture(botonFacilSeleccionado);
        bFacil.setOrigin(bFacil.getGlobalBounds().width / 2, bFacil.getGlobalBounds().height / 2);
        bFacil.setScale(6, 6);
        bFacil.setPosition((cBorde.getPosition().x - (cBorde.getGlobalBounds().width / 2)) - separacion - (bFacil.getGlobalBounds().width / 2), sf::VideoMode::getDesktopMode().height / 2.0f);

        botonDificil.loadFromFile("../assets/menu/dificil.png");
        botonDificilSeleccionado.loadFromFile("../assets/menu/dificilSeleccionado.png");
        bDificil.setTexture(botonDificil);
        bDificil.setOrigin(bDificil.getGlobalBounds().width / 2, bDificil.getGlobalBounds().height / 2);
        bDificil.setScale(6, 6);
        bDificil.setPosition((cBorde.getPosition().x + (cBorde.getGlobalBounds().width / 2)) + separacion + (bDificil.getGlobalBounds().width / 2), sf::VideoMode::getDesktopMode().height / 2.0f);
    }
}

void PantallaCarga::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed){
        if(evento.key.code == sf::Keyboard::Enter){
            int opcion = juego->cambiarAPrograma;
            switch (opcion)
            {
            case 1:
                juego->cambiarPantalla(std::make_unique<minijuegoPonchar>(juego));
                break;
            case 2:
                juego->cambiarPantalla(std::make_unique<minijuegoPaginaWeb>(juego));
                break;
            case 3:
                juego->cambiarPantalla(std::make_unique<minijuegoTangram>(juego));
                break;
            case 4:
                juego->cambiarPantalla(std::make_unique<minijuegoMecatronica>(juego));
                break;
            case 5:
                juego->cambiarPantalla(std::make_unique<minijuegoMecanicaIndustrial>(juego));
                break;
            case 6:
                juego->cambiarPantalla(std::make_unique<minijuegoDisenoArquitectonico>(juego));
                break;
            case 7:
                juego->cambiarPantalla(std::make_unique<minijuegoAutotronica>(juego));
                break;
            case 8:
                juego->cambiarPantalla(std::make_unique<Topografia>(juego));
                break;
            case 9:
                juego->cambiarPantalla(std::make_unique<minijuegorandomxd>(juego));
                break;
            case 10:
                juego->cambiarPantalla(std::make_unique<minijuegoElectronicaYControl>(juego));
                break;
            case 11:
                juego->cambiarPantalla(std::make_unique<minijuegoRedes>(juego));
                break;
            case 12:
                juego->cambiarPantalla(std::make_unique<minijuegoSoldadura>(juego));
                break;
            case 13:
                juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
                break;

            case 14:
                juego->cambiarPantalla(std::make_unique<Informatica>(juego));
                break;
            case 15:
                juego->cambiarPantalla(std::make_unique<Electricidad>(juego));
                break;
            case 16:
                juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
                break;
            case 17:
                juego->cambiarPantalla(std::make_unique<Metalmecanica>(juego));
                break;

            default:
                break;
            }

        } else if(evento.key.code == sf::Keyboard::Right || evento.key.code == sf::Keyboard::D){
            if (facil)
            {
                facil = false;
                juego->minijuegoFacil = false;
                bFacil.setTexture(botonFacil);
                bDificil.setTexture(botonDificilSeleccionado);
            } else {
                facil = true;
                juego->minijuegoFacil = true;
                bFacil.setTexture(botonFacilSeleccionado);
                bDificil.setTexture(botonDificil);
            }

        }else if(evento.key.code == sf::Keyboard::Left || evento.key.code == sf::Keyboard::A){
            if (facil)
            {
                facil = false;
                juego->minijuegoFacil = false;
                bFacil.setTexture(botonFacil);
                bDificil.setTexture(botonDificilSeleccionado);
            } else {
                facil = true;
                juego->minijuegoFacil = true;
                bFacil.setTexture(botonFacilSeleccionado);
                bDificil.setTexture(botonDificil);
            }
        }



    }
}

void PantallaCarga::actualizar(){


    offsetX = (offsetX + speedX) % tFondo.getSize().x;
    offsetY = (offsetY + speedY) % tFondo.getSize().y;
    if (offsetX < 0) offsetX += tFondo.getSize().x;
    if (offsetY < 0) offsetY += tFondo.getSize().y;

    // aplicar el desplazamiento al textureRect
    fondo.setTextureRect(sf::IntRect(offsetX, offsetY, w, h));

}

void PantallaCarga::renderizar(sf::RenderWindow& window){
    window.draw(fondo);


    window.draw(texto);
    window.draw(barraCarga);
    window.draw(cBorde);
    window.draw(cRelleno);
    window.draw(sImagen);
    window.draw(bienvenida);
    float time=eje.getElapsedTime().asSeconds()/10.0;
    barraCarga.setSize({window.getSize().x*time, 50});
    if(time>=1.0){
        /* juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego)); */
        barraCarga.setFillColor(sf::Color::Transparent);
    }
    if (juego->botones)
    {
        window.draw(bFacil);
        window.draw(bDificil);
    }

}