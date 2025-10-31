#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PantallaSeleccionar : public Pantalla {
private:
    Golem jugador;

    std::vector<sf::Texture> puertasTextures;
    std::vector<sf::Sprite>  puertasSprites;
    std::vector<sf::Color>   coloresBrillo;

    int puertaCercana = -1;
    bool ignoreInput = true; // evita accion inmediata tras cambiar pantalla

    sf::Texture tFondoNexus;
    sf::Sprite  FondoNexus;

    sf::Texture tLogroDesbloqueado; // Textura original (ahora será la del logro detectado)
    sf::Sprite  logroDesbloqueado;


    sf::Texture tLogroInformatica;
    sf::Texture tLogroElectricidad;
    sf::Texture tLogroDiseno;
    sf::Texture tLogroMetalmecanica;

    sf::Font fuente;
    sf::Text textoPrincipal;
    std::vector<sf::Text> textosPuertas;

    sf::Text tituloLogro;
    sf::Text descripcionLogro;
    sf::RectangleShape prueba;

    sf::Clock relojLogro;
    bool logroActivo = false;
    bool apareciendo = false;
    bool desapareciendo = false;
    float alphaLogro = 0.f;

    sf::Vector2f posActual;
    sf::Vector2f posDestino;
public:
    PantallaSeleccionar(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};