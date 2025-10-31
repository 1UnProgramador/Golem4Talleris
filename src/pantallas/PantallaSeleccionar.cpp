#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaMenu.h"
/* #include "../../include/pantallas/informatica.h"
#include "../../include/pantallas/electricidad.h"
#include "../../include/pantallas/DisenoTecnico.h"
#include "../../include/pantallas/Metalmecanica.h" */
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

/* std::string wrapTextString(const std::string& text, const sf::Font& font, unsigned int characterSize, float maxWidth) {

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
} */

PantallaSeleccionar::PantallaSeleccionar(Juego* juego)
: Pantalla(juego), jugador(0, 0)
{
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // Fondo
    if (!tFondoNexus.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png"))
        std::cerr << "Error al cargar fondo del nexus\n";
    else {
        FondoNexus.setTexture(tFondoNexus);
        float fX = width / FondoNexus.getGlobalBounds().width;
        float fY = height / FondoNexus.getGlobalBounds().height;
        FondoNexus.setScale(fX, fY);
    }

    // Jugador
    sf::FloatRect pb = jugador.getBounds();
    jugador.setPosition((width - pb.width) / 2.f, height - pb.height * 2.5f);

    // Configuración de puertas
    std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta informatica1.png",
        "../assets/nexusxd/puerta electricidad2.png",
        "../assets/nexusxd/puerta diseno3.png",
        "../assets/nexusxd/puerta metalmecanica4.png"
    };

    coloresBrillo = {
        sf::Color(0, 200, 255, 220),
        sf::Color(255, 220, 80, 220),
        sf::Color(0, 220, 130, 220),
        sf::Color(80, 140, 255, 220)
    };

    const float factorAncho = 0.15f;
    const float factorSeparacion = 0.10f;
    float puertaW = width * factorAncho;
    float puertaH = puertaW * (200.f / 120.f);
    float separacion = width * factorSeparacion;
    float startX = (width - (puertaW * 4 + separacion * 3)) / 2.f;
    float posY = height * 0.15f;

    puertasTextures.resize(4);
    puertasSprites.resize(4);

    for (int i = 0; i < 4; ++i) {
        if (!puertasTextures[i].loadFromFile(rutas[i])) {
            std::cerr << "Warning: no se pudo cargar " << rutas[i] << "\n";
            sf::Image img; img.create(120, 200, sf::Color(150,150,150));
            puertasTextures[i].loadFromImage(img);
        }

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        float scaleX = puertaW / (float)texSize.x;
        float scaleY = puertaH / (float)texSize.y;
        puertasSprites[i].setScale(scaleX, scaleY);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
        puertasSprites[i].setColor(sf::Color::White);
    }

    // Fuente y textos
    if (!fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf"))
        std::cerr << "No se pudo cargar la fuente para los textos\n";

    // === Texto principal ===
    textoPrincipal.setFont(fuente);
    textoPrincipal.setString("Selecciona una especialidad");
    textoPrincipal.setCharacterSize(45);
    textoPrincipal.setFillColor(sf::Color::White);
    textoPrincipal.setOutlineColor(sf::Color::Black);
    textoPrincipal.setOutlineThickness(4.f);
    textoPrincipal.setStyle(sf::Text::Bold);
    sf::FloatRect tb = textoPrincipal.getLocalBounds();
    textoPrincipal.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    textoPrincipal.setPosition(width / 2.f, height * 0.05f);

    // === Nombres de las puertas ===
    std::vector<std::string> nombres = {
        "Informatica", "Electricidad", "Diseno Tecnico", "Metalmecanica"
    };

    textosPuertas.resize(4);
    for (int i = 0; i < 4; ++i) {
        textosPuertas[i].setFont(fuente);
        textosPuertas[i].setString(nombres[i]);
        textosPuertas[i].setCharacterSize(30); //tamaño texto
        textosPuertas[i].setFillColor(sf::Color::White);
        textosPuertas[i].setOutlineColor(sf::Color::Black);
        textosPuertas[i].setOutlineThickness(3.f);
        textosPuertas[i].setStyle(sf::Text::Bold);
        sf::FloatRect bounds = textosPuertas[i].getLocalBounds();
        sf::FloatRect puertaBounds = puertasSprites[i].getGlobalBounds();
        textosPuertas[i].setPosition(
            puertaBounds.left + (puertaBounds.width / 2.f) - (bounds.width / 2.f),
            puertaBounds.top - bounds.height * -0.8f
        );
    }

    ignoreInput = true;

    std::cout << "Minijuegos pasados: " << std::to_string(juego->minijuegosPasados[0]) << ", "<< std::to_string(juego->minijuegosPasados[1]) << ", "<< std::to_string(juego->minijuegosPasados[2]) << ", "<< std::to_string(juego->minijuegosPasados[3]) << ", "<< std::to_string(juego->minijuegosPasados[4]) << ", "<< std::to_string(juego->minijuegosPasados[5]) << ", "<< std::to_string(juego->minijuegosPasados[6]) << ", "<< std::to_string(juego->minijuegosPasados[7]) << ", "<< std::to_string(juego->minijuegosPasados[8]) << ", "<< std::to_string(juego->minijuegosPasados[9]) << ", "<< std::to_string(juego->minijuegosPasados[10]) << ", "<< std::to_string(juego->minijuegosPasados[11]) << "." << std::endl;

    tLogroDesbloqueado.loadFromFile("../assets/logroDesbloqueado.png");
    logroDesbloqueado.setTexture(tLogroDesbloqueado);
    logroDesbloqueado.setOrigin(logroDesbloqueado.getGlobalBounds().width / 2, logroDesbloqueado.getGlobalBounds().height / 2);
    logroDesbloqueado.setScale(5, 3);
    logroDesbloqueado.setPosition(sf::VideoMode::getDesktopMode().width - (logroDesbloqueado.getGlobalBounds().width / 2), sf::VideoMode::getDesktopMode().height - (logroDesbloqueado.getGlobalBounds().height / 2));


    tituloLogro.setFont(fuente);
    tituloLogro.setCharacterSize(20);
    tituloLogro.setPosition(logroDesbloqueado.getPosition().x - 20, logroDesbloqueado.getPosition().y - logroDesbloqueado.getGlobalBounds().height / 2);

    descripcionLogro.setFont(fuente);
    descripcionLogro.setCharacterSize(15);
    descripcionLogro.setPosition(tituloLogro.getPosition().x, tituloLogro.getPosition().y + 40);

    if ((juego->minijuegosPasados[0] && juego->minijuegosPasados[1] && juego->minijuegosPasados[2]) && !juego->logroDesbloqueado("Maestro del Bit Supremo"))
    {
        juego->desbloquearLogro("Maestro del Bit Supremo");
        tituloLogro.setString(wrapTextString("Maestro del Bit Supremo", fuente, 20, 172));
        descripcionLogro.setString(wrapTextString("Completaste el taller de informatica", fuente, 15, 172));
    } else if((juego->minijuegosPasados[3] && juego->minijuegosPasados[6] && juego->minijuegosPasados[9] && juego->minijuegosPasados[10]) && !juego->logroDesbloqueado("Senor de los Voltios"))
    {
        juego->desbloquearLogro("Senor de los Voltios");
        tituloLogro.setString(wrapTextString("Senor de los Voltios", fuente, 20, 172));
        descripcionLogro.setString(wrapTextString("Completaste el taller de electricidad", fuente, 15, 172));
    } else if((juego->minijuegosPasados[5] && juego->minijuegosPasados[7] && juego->minijuegosPasados[8] && !juego->logroDesbloqueado("Arquitecto de los Suenos")))
    {
        juego->desbloquearLogro("Arquitecto de los Suenos");
        tituloLogro.setString(wrapTextString("Arquitecto de los Suenos", fuente, 20, 172));
        descripcionLogro.setString(wrapTextString("Completaste el taller de diseno", fuente, 15, 172));
    } else if((juego->minijuegosPasados[4] && juego->minijuegosPasados[11]) && !juego->logroDesbloqueado("Forjador del Acero Eterno"))
    {
        juego->desbloquearLogro("Forjador del Acero Eterno");
        tituloLogro.setString(wrapTextString("Forjador del Acero Eterno", fuente, 20, 172));
        descripcionLogro.setString(wrapTextString("Completaste el taller de metalmecanica", fuente, 15, 172));
    }

    prueba.setSize(sf::Vector2f(tituloLogro.getGlobalBounds().width - 30, logroDesbloqueado.getGlobalBounds().height));
    /* prueba.setOrigin(prueba.getGlobalBounds().width / 2, prueba.getGlobalBounds().height / 2); */
    prueba.setPosition(tituloLogro.getPosition().x, tituloLogro.getPosition().y);
    prueba.setFillColor(sf::Color::Cyan);

    std::cout << "posicion del coso: " << std::to_string(sf::VideoMode::getDesktopMode().width - descripcionLogro.getPosition().x) << ", " << std::to_string(sf::VideoMode::getDesktopMode().height - descripcionLogro.getPosition().y) << std::endl;

    /* posActual = sf::Vector2f(-400, 50);
    posDestino = sf::Vector2f(50, 50);
    logroDesbloqueado.setPosition(posActual);
    tituloLogro.setPosition(posActual.x + 20, posActual.y + 10);
    descripcionLogro.setPosition(posActual.x + 20, posActual.y + 45);


    alphaLogro = 0;
    logroActivo = true;
    apareciendo = true;
    desapareciendo = false;
    relojLogro.restart(); */

}


void PantallaSeleccionar::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
        juego->cambiarPantalla(std::make_unique<PantallaMenu>(juego));

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased)
            ignoreInput = false;
        return;
    }

    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter) {
        if (puertaCercana != -1) {
            switch (puertaCercana) {
                case 0:
                    juego->cambiarAPrograma = 14;
                    juego->seleccionado = "imagenInformatica";
                    juego->botones = false;
                    juego->instrucciones =  "Bienvenido a la especialidad de informatica, aca se extiende durante 3 programas: Mantenimiento electronico y de computadores (P1), diseño de paginas Web (P2) y diseno grafico asistido por computador (P3). El elemento central de este taller es la tecnologia, te aseguramos que te encantara, Suerte!";
                    break;
                case 1:
                    juego->cambiarAPrograma = 15;
                    juego->seleccionado = "imagenElectricidad";
                    juego->botones = false;
                    juego->instrucciones =  "Bienvenido a la especialidad de Electricidad, aca se extiende durante 4 programas: Mecatrónica (P4), Autotrónica (P7), Electrónica y control (P10) y Redes Eléctricas (P11). El elemento central de este taller es La conversión, distribución y control inteligente de la energía eléctrica. ¡Aprende de él mientras desarrollas tu razonamiento lógico!";
                    break;
                case 2:
                    juego->cambiarAPrograma = 16;
                    juego->botones = false;
                    juego->seleccionado = "imagenDiseno";
                    juego->instrucciones =  "Bienvenido a la especialidad de Metalmecánica, aca se extiende durante 3 programas: Diseño Arquitectónico (P6), Topografía (P8) y Diseño asistido por computador  (P9). El elemento central de este taller es la representación y materialización del espacio mediante herramientas tecnológicas y análisis del territorio.";
                    break;
                case 3:
                    juego->cambiarAPrograma = 17;
                    juego->botones = false;
                    juego->seleccionado = "imagenMetalmecanica";
                    juego->instrucciones =  "Bienvenido a la especialidad de Metalmecánica, aca se extiende durante 2 programas: Mecánica industrial (P5), y Soldadura (P12). El elemento central de este taller es el dominio de los procesos que permiten dar forma, unir y optimizar componentes metálicos.";
                    break;
                default:
                    break;
            }
            juego->botones = false;
            juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
        } else {
            std::cout << "[PantallaSeleccionar] Enter pero sin puerta cercana\n";
        }
    }
}

void PantallaSeleccionar::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());
    int nuevaPuerta = -1;
    float mejorDist = 1e9f;
    sf::FloatRect jugadorBounds = jugador.getBounds();
    float jCenterX = jugadorBounds.left + jugadorBounds.width * 0.5f;
    float jCenterY = jugadorBounds.top + jugadorBounds.height * 0.5f;

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();
        const float expand = std::max(3.f, b.width * 0.02f);
        b.left -= expand; b.top -= expand;
        b.width += expand * 2.f; b.height += expand * 2.f;
        if (!jugadorBounds.intersects(b)) {
            puertasSprites[i].setColor(sf::Color::White);
            continue;
        }
        float pCenterX = b.left + b.width * 0.5f;
        float pCenterY = b.top + b.height * 0.5f;
        float dx = pCenterX - jCenterX;
        float dy = pCenterY - jCenterY;
        float dist = std::sqrt(dx*dx + dy*dy);
        if (dist < mejorDist) {
            mejorDist = dist;
            nuevaPuerta = i;
        }
    }

    for (int i = 0; i < (int)puertasSprites.size(); ++i)
        puertasSprites[i].setColor(i == nuevaPuerta ? coloresBrillo[i] : sf::Color::White);

    puertaCercana = nuevaPuerta;
}

void PantallaSeleccionar::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(FondoNexus);

    // Texto principal
    window.draw(textoPrincipal);

    // Puertas y textos
    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        window.draw(puertasSprites[i]);
        window.draw(textosPuertas[i]);
    }

    window.draw(jugador);
    window.draw(logroDesbloqueado);

    /* window.draw(prueba); */
    window.draw(tituloLogro);
    window.draw(descripcionLogro);
}
