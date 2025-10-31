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
    "¿Sabías que en P1 podrás revivir un computador que no enciende usando solo tu ingenio y un multímetro?",
    "En P1 descubrirás que detrás de cada luz LED hay una historia de electrones viajando a toda velocidad.",
    "Al estudiar P1 aprenderás a leer el lenguaje secreto de las placas electrónicas.",
    "Dicen que en P1 un tornillo mal puesto puede silenciar todo un sistema… y tú sabrás cómo hacerlo hablar de nuevo.",
    "En P1 conocerás qué ocurre dentro de un condensador cuando se carga de energía.",
    "En P1 repararás fuentes de poder que rugen como dragones eléctricos.",
    "¿Sabías que en P1 puedes construir tu propio tester con componentes reciclados?",
    "En P1 entenderás por qué los computadores se apagan solos cuando tienen miedo del sobrecalentamiento.",
    "Cada chip que toques en P1 será un pequeño cerebro esperando tus órdenes.",
    "En P1 descubrirás que reparar es una forma de ingeniería y también de paciencia.",

    "En P2 el código será tu pincel y la web tu lienzo.",
    "¿Sabías que en P2 puedes crear un sitio que cambie de color según la hora del día?",
    "En P2 descubrirás cómo hacer que una página web te salude por tu nombre.",
    "Los estudiantes de P2 no solo programan… diseñan experiencias interactivas.",
    "En P2 aprenderás que tres letras —HTML, CSS y JS— pueden construir mundos digitales enteros.",
    "En P2 podrás conectar una base de datos real a un sitio que tú mismo diseñes.",
    "¿Sabías que en P2 los botones no son solo clics, sino pequeñas decisiones de diseño?",
    "En P2 descubrirás cómo el backend y el frontend se comunican como dos cerebros sincronizados.",
    "Tu primera página web en P2 podría terminar siendo tu primer negocio digital.",
    "En P2 el internet dejará de ser algo que visitas, y se convertirá en algo que creas.",

    "En P3 aprenderás que un buen diseño puede hablar sin decir una sola palabra.",
    "¿Sabías que en P3 el color azul transmite confianza y por eso lo usan los bancos?",
    "En P3 descubrirás que los logos más simples son los que más duran.",
    "Los diseñadores de P3 convierten una idea en una imagen capaz de emocionar.",
    "En P3 tu ratón será una brocha digital con infinitas posibilidades.",
    "Un píxel mal ubicado puede arruinar una composición, pero tú sabrás domarlo en P3.",
    "¿Sabías que en P3 puedes crear carteles que parecen moverse aunque estén quietos?",
    "En P3 entenderás que cada fuente tiene una personalidad: seria, rebelde o elegante.",
    "Los programas que dominarás en P3 son las herramientas secretas del marketing moderno.",
    "En P3 descubrirás que el diseño gráfico es el idioma universal de la creatividad.",

    "En P4 un sensor ultrasónico puede convertirse en los ojos de tu robot.",
    "¿Sabías que en P4 puedes programar una mano robótica que imite tus movimientos?",
    "En P4 los motores obedecerán tus órdenes como si fueras su creador.",
    "Tu primera placa Arduino será el corazón de una máquina inteligente.",
    "En P4 descubrirás que un robot también puede tener reflejos y decisiones.",
    "Los proyectos de P4 mezclan metal, lógica y movimiento en perfecta armonía.",
    "¿Sabías que en P4 se pueden crear robots que esquiven obstáculos como un gato?",
    "En P4 aprenderás que la mecatrónica es el lenguaje que une todas las ingenierías.",
    "Cada tornillo que aprietes en P4 será una línea de código hecha materia.",
    "En P4 verás que construir un robot no es ciencia ficción, sino una ciencia exacta.",

    "En P5 el acero se convierte en arte cuando pasa por tus manos.",
    "¿Sabías que en P5 se fabrican piezas tan precisas que un cabello parece enorme a su lado?",
    "En P5 una máquina puede cortar metal con la suavidad de una hoja de papel.",
    "Los estudiantes de P5 aprenden que medir bien es tan importante como construir bien.",
    "En P5 la fuerza y la precisión conviven en cada pieza torneada.",
    "¿Sabías que un solo engranaje mal hecho puede detener toda una planta industrial?",
    "En P5 escucharás el sonido del metal al transformarse en productividad.",
    "Cada herramienta en P5 tiene un propósito exacto, y tú aprenderás a dominarla.",
    "En P5 la mecánica industrial es como un reloj gigante: tú harás que no se detenga.",
    "El olor del acero caliente será tu firma de trabajo en P5.",

    "En P6 los edificios comienzan como sueños dibujados en papel.",
    "¿Sabías que en P6 podrás diseñar espacios donde la luz se convierte en arte?",
    "En P6 aprenderás que una línea bien trazada puede convertirse en un hogar real.",
    "Los arquitectos de P6 no solo construyen lugares, crean sensaciones.",
    "En P6 estudiarás cómo el color y la forma afectan el ánimo de las personas.",
    "¿Sabías que los mejores diseños nacen entendiendo el terreno y su entorno?",
    "En P6 tus planos digitales serán la base de proyectos reales.",
    "Cada perspectiva que traces en P6 será una ventana hacia el futuro.",
    "En P6 la creatividad se mezcla con la técnica para construir belleza.",
    "Los espacios que imagines en P6 podrían algún día ser lugares donde otros vivan.",

    "¿Sabías que en P7 puedes leer la salud de un motor con solo escuchar su sonido?",
    "En P7 descubrirás cómo los autos modernos son laboratorios rodantes de electrónica.",
    "Los sensores automotrices son los nervios de cada vehículo, y tú sabrás interpretarlos.",
    "En P7 usarás escáneres OBD-II para descubrir fallas ocultas.",
    "¿Sabías que algunos carros tienen más líneas de código que un avión?",
    "En P7 aprenderás cómo funcionan los sistemas de frenos ABS y bolsas de aire.",
    "Los motores eléctricos y los híbridos también tendrán su espacio en P7.",
    "En P7 desmontarás, diagnosticarás y volverás a ensamblar vehículos como un médico mecánico.",
    "El olor a gasolina y el sonido de un motor bien calibrado serán tu sinfonía en P7.",
    "En P7 verás que la autotrónica es el puente entre la mecánica y la inteligencia digital.",

    "¿Sabías que en P8 un error de un milímetro puede cambiar todo un plano?",
    "En P8 caminarás con brújulas, GPS y teodolitos como un explorador del siglo XXI.",
    "En P8 aprenderás a convertir montañas y ríos en datos matemáticos.",
    "Los mapas que diseñes en P8 serán la base de obras de ingeniería reales.",
    "¿Sabías que la topografía fue clave para construir las pirámides y los rascacielos?",
    "En P8 descubrirás cómo se mide la Tierra sin moverse del sitio.",
    "Cada punto que marques en P8 es una coordenada en la historia del terreno.",
    "En P8 aprenderás que la topografía une la ciencia con la orientación del espacio.",
    "Tu cuaderno de campo en P8 será un diario de aventuras con números y alturas.",
    "En P8 el mundo será tu laboratorio al aire libre.",

    "¿Sabías que en P9 un simple clic puede generar planos de precisión milimétrica?",
    "En P9 los diseños cobran vida en 3D antes de existir en la realidad.",
    "En P9 podrás construir digitalmente desde una pieza hasta una ciudad.",
    "El software CAD será tu herramienta para transformar ideas en geometría pura.",
    "¿Sabías que en P9 se puede imprimir en 3D lo que primero nació en la pantalla?",
    "En P9 descubrirás cómo cada línea digital tiene sentido físico y estructural.",
    "Los modelos que hagas en P9 servirán para ingenieros, arquitectos y diseñadores.",
    "En P9 la imaginación se mide en coordenadas y capas de precisión.",
    "¿Sabías que con CAD puedes simular hasta cómo entra la luz por una ventana?",
    "En P9 verás que el diseño asistido por computador es el idioma universal de la técnica.",

    "En P10 los electrones obedecen tus órdenes para automatizar el mundo.",
    "¿Sabías que un microcontrolador puede reemplazar a todo un panel de relés?",
    "En P10 los sensores escuchan, los actuadores responden y tú orquestas la sinfonía.",
    "Los proyectos de P10 pueden controlar luces, motores y sistemas enteros.",
    "En P10 descubrirás que la electrónica y el control son el cerebro de las máquinas.",
    "¿Sabías que un circuito mal diseñado puede crear una orquesta de errores?",
    "En P10 aprenderás a leer diagramas eléctricos como si fueran partituras técnicas.",
    "Los sistemas de control que hagas en P10 podrán funcionar de forma autónoma.",
    "Cada LED que enciendas en P10 contará una historia de voltios y precisión.",
    "En P10 te convertirás en el arquitecto invisible detrás de cada máquina inteligente.",

    "¿Sabías que en P11 la electricidad viaja más rápido que cualquier transporte humano?",
    "En P11 aprenderás a domar la energía que ilumina ciudades enteras.",
    "Los circuitos que diseñes en P11 harán posible que todo funcione: desde un televisor hasta una fábrica.",
    "¿Sabías que un mal cálculo en P11 puede apagar todo un barrio?",
    "En P11 trabajarás con herramientas que miden, protegen y canalizan la energía.",
    "Los transformadores y tableros serán tu campo de batalla en P11.",
    "En P11 entenderás cómo fluye la corriente y cómo mantenerla bajo control.",
    "El sonido de un interruptor cerrándose será música para tus oídos en P11.",
    "En P11 aprenderás que la electricidad no se ve, pero se siente en cada chispa.",
    "Cada conexión que hagas en P11 será un acto de precisión y responsabilidad.",

    "En P12 el fuego y el metal bailan una coreografía de chispas y destreza.",
    "¿Sabías que un buen cordón de soldadura puede resistir toneladas de presión?",
    "En P12 descubrirás que la paciencia es tan importante como el calor.",
    "El sonido del arco eléctrico en P12 será la banda sonora de tu trabajo.",
    "En P12 aprenderás a elegir el tipo de electrodo según la unión que necesites.",
    "¿Sabías que soldar bajo el agua también es posible? En P12 sabrás cómo.",
    "Cada chispa que veas en P12 marcará el nacimiento de una estructura metálica.",
    "En P12 la seguridad es una disciplina tan precisa como el propio metal.",
    "El acero fundido se convertirá en arte técnico en tus manos en P12.",
    "En P12 comprenderás que unir metales es unir ideas, fuerza y técnica en una sola llama."
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
    texto.setString(utf8_to_wstring(wrapTextString("Dato curioso: " + Instrumentalizacion[rand()%size], fuente, 40, sf::VideoMode::getDesktopMode().width)));
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
            if (juego->minijuegoFacil) {
            juego->cambiarPantalla(std::make_unique<Topografia>(juego, DificultadTopo::FACIL));
            } else {
            juego->cambiarPantalla(std::make_unique<Topografia>(juego, DificultadTopo::DIFICIL));
            }
            break;
            case 9:
            if (juego->minijuegoFacil) {
            juego->cambiarPantalla(std::make_unique<minijuegorandomxd>(juego, Dificultad::FACIL));
            } else {
            juego->cambiarPantalla(std::make_unique<minijuegorandomxd>(juego, Dificultad::DIFICIL));
            }
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