#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaMenu.h"
/* #include "../../include/pantallas/informatica.h"
#include "../../include/pantallas/electricidad.h"
#include "../../include/pantallas/DisenoTecnico.h"
#include "../../include/pantallas/Metalmecanica.h" */
#include "../../include/pantallas/pantallaCreditos.h"
#include "../../src/logica/assetManager.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

PantallaSeleccionar::PantallaSeleccionar(Juego* juego)
: Pantalla(juego), jugador(0, 0)
{
    sonidoLogro.openFromMemory(sonidoLogro_wav, sonidoLogro_wav_len);
    MusicManager::getInstancia().reproducir(musicaHub_wav, musicaHub_wav_len, "menu", true, 70.f);
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // Fondo
    if (!tFondoNexus.loadFromMemory(fondoNexus_png, fondoNexus_png_len))
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
    /* std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta informatica1.png",
        "../assets/nexusxd/puerta electricidad2.png",
        "../assets/nexusxd/puerta diseno3.png",
        "../assets/nexusxd/puerta metalmecanica4.png"
    }; */

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
        if (i == 0)
        {
            if (!puertasTextures[i].loadFromMemory(puertaInformatica1_png, puertaInformatica1_png_len)) {
                std::cerr << "Warning: no se pudo cargar imagen\n";
                /* sf::Image img; img.create(120, 200, sf::Color(150,150,150)); */
                /* puertasTextures[i].loadFromImage(img); */
            }
        } else if (i == 1)
        {
            if (!puertasTextures[i].loadFromMemory(puertaElectricidad2_png, puertaElectricidad2_png_len)) {
                std::cerr << "Warning: no se pudo cargar imagen\n";
                /* sf::Image img; img.create(120, 200, sf::Color(150,150,150)); */
                /* puertasTextures[i].loadFromImage(img); */
            }
        } else if (i == 2)
        {
            if (!puertasTextures[i].loadFromMemory(puertaDiseno3_png, puertaDiseno3_png_len)) {
                std::cerr << "Warning: no se pudo cargar imagen\n";
                /* sf::Image img; img.create(120, 200, sf::Color(150,150,150)); */
                /* puertasTextures[i].loadFromImage(img); */
            }
        } else if (i == 3){
            if (!puertasTextures[i].loadFromMemory(puertaMetalmecanica4_png, puertaMetalmecanica4_png_len)) {
                std::cerr << "Warning: no se pudo cargar imagen\n";
                /* sf::Image img; img.create(120, 200, sf::Color(150,150,150)); */
                /* puertasTextures[i].loadFromImage(img); */
            }
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
    if (!fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len))
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
        "Informática", "Electricidad", "Diseño Técnico", "Metalmecánica"
    };

    textosPuertas.resize(4);
    for (int i = 0; i < 4; ++i) {
        textosPuertas[i].setFont(fuente);
        textosPuertas[i].setString(utf8_to_wstring(wrapTextString(nombres[i], fuente, 30, 200)));
        textosPuertas[i].setCharacterSize(30); //tamaño texto

        if ((juego->minijuegosPasados[0] && juego->minijuegosPasados[1] && juego->minijuegosPasados[2]) && i == 0)
        {
            textosPuertas[i].setFillColor(sf::Color(0, 102, 204));
        } else if ((juego->minijuegosPasados[3] && juego->minijuegosPasados[6] && juego->minijuegosPasados[9] && juego->minijuegosPasados[10]) && i == 1)
        {
            textosPuertas[i].setFillColor(sf::Color(255, 204, 0));
        } else if ((juego->minijuegosPasados[5] && juego->minijuegosPasados[7] && juego->minijuegosPasados[8]) && i == 2)
        {
            textosPuertas[i].setFillColor(sf::Color(204, 51, 153));
        } else if ((juego->minijuegosPasados[4] && juego->minijuegosPasados[11] ) && i == 3)
        {
            textosPuertas[i].setFillColor(sf::Color(96, 96, 96));
        }

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

    // === Carga de las texturas de logro ===
    if (!tLogroDesbloqueado.loadFromMemory(logroDesbloqueado_png, logroDesbloqueado_png_len))
        std::cerr << "Error al cargar textura logroDesbloqueado base\n";
    if (!tLogroInformatica.loadFromMemory(logroDesbloqueadoinformatica_png, logroDesbloqueadoinformatica_png_len))
        std::cerr << "Error al cargar textura logroInformatica\n";
    if (!tLogroElectricidad.loadFromMemory(logroDesbloqueadoelectricidad_png, logroDesbloqueadoelectricidad_png_len))
        std::cerr << "Error al cargar textura logroElectricidad\n";
    if (!tLogroDiseno.loadFromMemory(logroDesbloqueadodiseno_png, logroDesbloqueadodiseno_png_len))
        std::cerr << "Error al cargar textura logroDiseno\n";
    if (!tLogroMetalmecanica.loadFromMemory(logroDesbloqueadometalmecanica_png, logroDesbloqueadometalmecanica_png_len))
        std::cerr << "Error al cargar textura logroMetalmecanica\n";
    if (!tLogroGeneral.loadFromMemory(LogroDesbloqueadoGeneral_jpg, LogroDesbloqueadoGeneral_jpg_len))
        std::cerr << "Error al cargar textura logroMetalmecanica\n";
    // ======================================


    logroDesbloqueado.setTexture(tLogroDesbloqueado);
    logroDesbloqueado.setOrigin(logroDesbloqueado.getGlobalBounds().width / 2, logroDesbloqueado.getGlobalBounds().height / 2);
    logroDesbloqueado.setScale(5, 3);

    logroDesbloqueado.setPosition(sf::VideoMode::getDesktopMode().width - (logroDesbloqueado.getGlobalBounds().width / 2), sf::VideoMode::getDesktopMode().height + (logroDesbloqueado.getGlobalBounds().height / 2));


    tituloLogro.setFont(fuente);
    tituloLogro.setOrigin(tituloLogro.getGlobalBounds().width / 2, tituloLogro.getGlobalBounds().height / 2);
    tituloLogro.setCharacterSize(20);

    descripcionLogro.setFont(fuente);
    descripcionLogro.setOrigin(descripcionLogro.getGlobalBounds().width / 2, descripcionLogro.getGlobalBounds().height / 2);
    descripcionLogro.setCharacterSize(15);

    if ((juego->minijuegosPasados[0] && juego->minijuegosPasados[1] && juego->minijuegosPasados[2]) && !juego->logroDesbloqueado("Maestro del Bit Supremo"))
    {
        sonidoLogro.play();
        juego->desbloquearLogro("Maestro del Bit Supremo");
        tituloLogro.setString(wrapTextString("Maestro del Bit Supremo", fuente, 20, 172));
        tituloLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y - 40);
        tituloLogro.setFillColor(sf::Color(0, 102, 204));
        descripcionLogro.setString(wrapTextString("Completaste el taller de informatica", fuente, 15, 172));
        descripcionLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y + 4);
        logroDesbloqueado.setTexture(tLogroInformatica);
    } else if((juego->minijuegosPasados[3] && juego->minijuegosPasados[6] && juego->minijuegosPasados[9] && juego->minijuegosPasados[10]) && !juego->logroDesbloqueado("Senor de los Voltios"))
    {
        sonidoLogro.play();
        juego->desbloquearLogro("Senor de los Voltios");
        tituloLogro.setString(wrapTextString("Senor de los Voltios", fuente, 20, 172));
        tituloLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y - 40);
        tituloLogro.setFillColor(sf::Color(255, 204, 0));
        descripcionLogro.setString(wrapTextString("Completaste el taller de electricidad", fuente, 15, 172));
        descripcionLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y + 4);
        logroDesbloqueado.setTexture(tLogroElectricidad);
    } else if((juego->minijuegosPasados[5] && juego->minijuegosPasados[7] && juego->minijuegosPasados[8] && !juego->logroDesbloqueado("Arquitecto de los Suenos")))
    {
        sonidoLogro.play();
        juego->desbloquearLogro("Arquitecto de los Suenos");
        tituloLogro.setString(wrapTextString("Arquitecto de los Suenos", fuente, 20, 172));
        tituloLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y - 40);
        tituloLogro.setFillColor(sf::Color(204, 51, 153));
        descripcionLogro.setString(wrapTextString("Completaste el taller de diseno", fuente, 15, 160));
        descripcionLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y + 4);
        logroDesbloqueado.setTexture(tLogroDiseno);
    } else if((juego->minijuegosPasados[4] && juego->minijuegosPasados[11]) && !juego->logroDesbloqueado("Forjador del Acero Eterno"))
    {
        sonidoLogro.play();
        juego->desbloquearLogro("Forjador del Acero Eterno");
        tituloLogro.setString(wrapTextString("Forjador del Acero Eterno", fuente, 20, 172));
        tituloLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y - 40);
        tituloLogro.setFillColor(sf::Color(96, 96, 96));
        descripcionLogro.setString(wrapTextString("Completaste el taller de metalmecanica", fuente, 15, 172));
        descripcionLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y + 4);
        logroDesbloqueado.setTexture(tLogroMetalmecanica);
    }
    cambioPantalla.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    cambioPantalla.setPosition(0, 0);
    cambioPantalla.setFillColor(sf::Color(0, 0, 0, 0));
}

void PantallaSeleccionar::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed){
        if (evento.key.code == sf::Keyboard::Escape)
        {
            juego->cambiarPantalla(std::make_unique<PantallaMenu>(juego));
        } /* else if (evento.key.code == sf::Keyboard::W)
        {
            descripcionLogro.move(0, -1);
        } else if (evento.key.code == sf::Keyboard::A)
        {
            descripcionLogro.move(-1, 0);
        } else if (evento.key.code == sf::Keyboard::S)
        {
            descripcionLogro.move(0, 1);
        } else if (evento.key.code == sf::Keyboard::D)
        {
            descripcionLogro.move(1, 0);
        }
        std::cout << "Posicion: " << std::to_string(logroDesbloqueado.getPosition().x - descripcionLogro.getPosition().x) << ", " << std::to_string(logroDesbloqueado.getPosition().y - descripcionLogro.getPosition().y) << std::endl; */

    }





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

                    juego->backspace = false;
                    juego->enter = false;
                    juego->esc = true;
                    juego->flechas = true;
                    juego->mouse = false;
                    juego->space = false;
                    juego->wasd = true;

                    juego->botones = false;
                    juego->instrucciones =  "Bienvenido a la especialidad de informatica, aca se extiende durante 3 programas: Mantenimiento electronico y de computadores (P1), diseño de paginas Web (P2) y diseno grafico asistido por computador (P3). El elemento central de este taller es la tecnologia, te aseguramos que te encantara, Suerte!";
                    break;
                case 1:
                    juego->cambiarAPrograma = 15;
                    juego->seleccionado = "imagenElectricidad";

                    juego->backspace = false;
                    juego->enter = false;
                    juego->esc = true;
                    juego->flechas = true;
                    juego->mouse = false;
                    juego->space = false;
                    juego->wasd = true;

                    juego->botones = false;
                    juego->instrucciones =  "Bienvenido a la especialidad de Electricidad, aca se extiende durante 4 programas: Mecatrónica (P4), Autotrónica (P7), Electrónica y control (P10) y Redes Eléctricas (P11). El elemento central de este taller es La conversión, distribución y control inteligente de la energía eléctrica. ¡Aprende de él mientras desarrollas tu razonamiento lógico!";
                    break;
                case 2:
                    juego->cambiarAPrograma = 16;
                    juego->botones = false;

                    juego->backspace = false;
                    juego->enter = false;
                    juego->esc = true;
                    juego->flechas = true;
                    juego->mouse = false;
                    juego->space = false;
                    juego->wasd = true;

                    juego->seleccionado = "imagenDiseno";
                    juego->instrucciones =  "Bienvenido a la especialidad de Metalmecánica, aca se extiende durante 3 programas: Diseño Arquitectónico (P6), Topografía (P8) y Diseño asistido por computador  (P9). El elemento central de este taller es la representación y materialización del espacio mediante herramientas tecnológicas y análisis del territorio.";
                    break;
                case 3:
                    juego->cambiarAPrograma = 17;
                    juego->botones = false;

                    juego->backspace = false;
                    juego->enter = false;
                    juego->esc = true;
                    juego->flechas = true;
                    juego->mouse = false;
                    juego->space = false;
                    juego->wasd = true;

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
    if (!logroMostrado)
    {
        if ((logroDesbloqueado.getPosition().y > (sf::VideoMode::getDesktopMode().height - (logroDesbloqueado.getGlobalBounds().height / 2))) /* && tituloLogro.getString() != "" */)
        {
            logroDesbloqueado.move(0, -3);
        } else {
            logroMostrado = true;
            tiempoLogro.restart();
            /* clock.restart(); */

        }
    } else {
        if (!(logroDesbloqueado.getPosition().y > (sf::VideoMode::getDesktopMode().height + (logroDesbloqueado.getGlobalBounds().height / 2))) && tiempoLogro.getElapsedTime().asSeconds() >= 3.0f){
            logroDesbloqueado.move(0, 2);
            /* float totalAnimacion = 5.0f;
            float decrementoAlpha = 255.0f / totalAnimacion;
            float deltaTime = clock.getElapsedTime().asMilliseconds();
            sf::Color colorActual = cambioPantalla.getFillColor();

            if (colorActual.a < 255) {
                colorActual.a += decrementoAlpha * deltaTime;
                if (colorActual.a > 255) {
                    colorActual.a = 255;
                }
                cambioPantalla.setFillColor(colorActual);
            } */
        }
        if ((logroDesbloqueado.getPosition().y > (sf::VideoMode::getDesktopMode().height + (logroDesbloqueado.getGlobalBounds().height / 2)))){
            if((juego->minijuegosPasados[0] && juego->minijuegosPasados[1] && juego->minijuegosPasados[2]) && (juego->minijuegosPasados[3] && juego->minijuegosPasados[4] && juego->minijuegosPasados[5] && juego->minijuegosPasados[6]) && (juego->minijuegosPasados[7] &&    juego->minijuegosPasados[8] && juego->minijuegosPasados[9]) && (juego->minijuegosPasados[10] && juego->minijuegosPasados[11])){
                sonidoLogro.play();
                juego->desbloquearLogro("Constructor de futuros");
                tituloLogro.setString(wrapTextString("Constructor de futuros", fuente, 20, 172));
                tituloLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y - 40);
                tituloLogro.setFillColor(sf::Color(96, 96, 96));
                descripcionLogro.setString(wrapTextString("Completaste los 4 talleres", fuente, 15, 172));
                descripcionLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y + 4);
                logroDesbloqueado.setTexture(tLogroGeneral);
                logroMostrado = false;
            }
        } 
    }

    tituloLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y - 40);
    descripcionLogro.setPosition(logroDesbloqueado.getPosition().x, logroDesbloqueado.getPosition().y + 4);


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

    // Solo dibujamos el banner de logro si se ha detectado el desbloqueo (tituloLogro no está vacío)
    if (tituloLogro.getString() != "")
    {
        window.draw(logroDesbloqueado);
        window.draw(tituloLogro);
        window.draw(descripcionLogro);
    }
    window.draw(cambioPantalla);
}