#include "../../include/logica/Juego.h"
#include "../../include/minijuegoElectronicaYControl/minijuegoElectronicaYControl.h"
#include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

minijuegoElectronicaYControl::minijuegoElectronicaYControl(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tImpresora.loadFromFile("../assets/minijuegoElectronicaYControl/chasis.png");
    impresora.setTexture(tImpresora);
    impresora.setOrigin(impresora.getGlobalBounds().width / 2, impresora.getGlobalBounds().height / 2);
    impresora.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    impresora.setScale(7.1, 7);

    tSoporte.loadFromFile("../assets/minijuegoElectronicaYControl/soporte.png");
    soporte.setTexture(tSoporte);
    soporte.setOrigin(soporte.getGlobalBounds().width / 2, soporte.getGlobalBounds().height / 2);
    soporte.setPosition(impresora.getPosition().x, impresora.getPosition().y);
    soporte.setScale(7, 7);

    tPuntero.loadFromFile("../assets/minijuegoElectronicaYControl/puntero.png");
    puntero.setTexture(tPuntero);
    puntero.setOrigin(puntero.getGlobalBounds().width / 2, puntero.getGlobalBounds().height / 2);
    puntero.setPosition(soporte.getPosition().x, soporte.getPosition().y + 12);
    puntero.setScale(3.5, 3.5);

    contorno.setSize(sf::Vector2f(impresora.getGlobalBounds().width, impresora.getGlobalBounds().height));
    contorno.setFillColor(sf::Color(128, 128, 128));
    contorno.setOrigin(contorno.getGlobalBounds().width / 2, contorno.getGlobalBounds().height / 2);
    contorno.setPosition(impresora.getPosition());

    float posicionXactual = impresora.getGlobalBounds().left;
    while (posicionXactual <= impresora.getPosition().x + (impresora.getGlobalBounds().width / 2)){
        sf::RectangleShape linea;
        linea.setSize(sf::Vector2f(1, impresora.getGlobalBounds().height));
        linea.setFillColor(sf::Color::Red);
        linea.setPosition(posicionXactual, impresora.getPosition().y - (impresora.getGlobalBounds().height / 2));
        lineasVerticales.push_back(linea);
        posicionXactual += movimiento;
    }
    for (int i = 0; i <= 5; i++)
    {
        lineasVerticales.erase(lineasVerticales.end());
        lineasVerticales.erase(lineasVerticales.begin());
    }


    float posicionYactual = impresora.getGlobalBounds().top;
    while (posicionYactual <= impresora.getPosition().y + (impresora.getGlobalBounds().height / 2)){
        sf::RectangleShape linea;
        linea.setSize(sf::Vector2f(impresora.getGlobalBounds().width - 100, 1));
        linea.setFillColor(sf::Color::Red);
        linea.setPosition(impresora.getPosition().x - (impresora.getGlobalBounds().width / 2) + 50, posicionYactual);
        lineasVerticales.push_back(linea);
        posicionYactual += movimiento;
    }

    puntero.setPosition((lineasVerticales[17].getPosition().x + movimiento / 2), puntero.getPosition().y);

    cubo cuadrado;
    cuadrado.forma.setSize(sf::Vector2f(movimiento, movimiento));
    cuadrado.forma.setOrigin(cuadrado.forma.getGlobalBounds().width / 2, cuadrado.forma.getGlobalBounds().height / 2);
    cuadrado.forma.setFillColor(sf::Color::Blue);
    cuadrado.forma.setPosition(-20, -20);
    std::cout << "cuadrado creado en: X:" << std::to_string(cuadrado.forma.getPosition().x) << " Y: " << std::to_string(cuadrado.forma.getPosition().y) << std::endl;
    cubos.push_back(cuadrado);

    for (int i = 0; i <= 42; i++)
    {
        cubo cuadrado;
        cuadrado.forma.setSize(sf::Vector2f(movimiento, movimiento));
        cuadrado.forma.setOrigin(cuadrado.forma.getGlobalBounds().width / 2, cuadrado.forma.getGlobalBounds().height / 2);
        cuadrado.forma.setFillColor(sf::Color(0, 0, 0, 150));

        cubosObjetivo.push_back(cuadrado);
    }
    cubosObjetivo[0].forma.setPosition(puntero.getPosition().x - (11 * movimiento), puntero.getPosition().y + (puntero.getGlobalBounds().height / 2) + (cubosObjetivo[0].forma.getGlobalBounds().height / 2) + (movimiento * 17));
    for (int i = 1; i <= 9; i++){
        cubosObjetivo[i].forma.setPosition(cubosObjetivo[0].forma.getPosition().x, cubosObjetivo[0].forma.getPosition().y - (movimiento * i));
    }
    for (int i = 0; i <= 8; i++){ /*10 - 18*/
        cubosObjetivo[i + 10].forma.setPosition(cubosObjetivo[9].forma.getPosition().x + (movimiento * (i + 1)), cubosObjetivo[9].forma.getPosition().y);
    }
    for (int i = 0; i <= 8; i++){ /*19 - 27*/
        cubosObjetivo[i + 19].forma.setPosition(cubosObjetivo[18].forma.getPosition().x, cubosObjetivo[18].forma.getPosition().y + (movimiento *(i + 1)));
    }
    for (int i = 0; i <= 14; i++){
        cubosObjetivo[i + 28].forma.setPosition(cubosObjetivo[9].forma.getPosition().x, cubosObjetivo[9].forma.getPosition().y - (movimiento * (i + 1)));
    }

}
void minijuegoElectronicaYControl::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed) {
        if(evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S){
            if(puntero.getPosition().y < impresora.getPosition().y + 182 ){
                puntero.move(0, movimiento);
                soporte.move(0, movimiento);
                std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x - impresora.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y - impresora.getPosition().y) << std::endl;
            }
        } else if(evento.key.code == sf::Keyboard::Up|| evento.key.code == sf::Keyboard::W){
            if(puntero.getPosition().y > impresora.getPosition().y - 168){
                puntero.move(0, -movimiento);
                soporte.move(0, -movimiento);
                std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x - impresora.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y - impresora.getPosition().y) << std::endl;
            }
        } else if(evento.key.code == sf::Keyboard::Left || evento.key.code == sf::Keyboard::A){
            if(puntero.getPosition().x > impresora.getPosition().x - 89){
                puntero.move(-movimiento, 0);
                std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x - impresora.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y - impresora.getPosition().y) << std::endl;
            }
        } else if(evento.key.code == sf::Keyboard::Right || evento.key.code == sf::Keyboard::D){
            if(puntero.getPosition().x < impresora.getPosition().x + 90){
                puntero.move(movimiento, 0);
                std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x - impresora.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y - impresora.getPosition().y) << std::endl;
            }
        } else if(evento.key.code == sf::Keyboard::Enter){
            size_t i = 0;
            for (auto &cuadrado : cubos){
                if(cuadrado.forma.getPosition() == sf::Vector2f(puntero.getPosition().x, puntero.getPosition().y + (puntero.getGlobalBounds().height / 2) + (cuadrado.forma.getGlobalBounds().height / 2))){
                    cubos.erase(cubos.begin() + i);
                } else {
                    if (i == cubos.size() - 1){
                        cubo cuadrado;
                        cuadrado.forma.setSize(sf::Vector2f(movimiento, movimiento));
                        cuadrado.forma.setOrigin(cuadrado.forma.getGlobalBounds().width / 2, cuadrado.forma.getGlobalBounds().height / 2);
                        cuadrado.forma.setFillColor(sf::Color::Blue);
                        cuadrado.forma.setPosition(puntero.getPosition().x, puntero.getPosition().y + (puntero.getGlobalBounds().height / 2) + (cuadrado.forma.getGlobalBounds().height / 2));
                        std::cout << "cuadrado creado en: X:" << std::to_string(cuadrado.forma.getPosition().x) << " Y: " << std::to_string(cuadrado.forma.getPosition().y) << std::endl;
                        cubos.push_back(cuadrado);
                    }
                }
                ++i;
            }

            int z = 1;
            for(auto &cuadrado : cubos){
                bool colision = false;
                for(auto &cuadradoO : cubosObjetivo){
                    if (z == 1){
                        break;
                    } else {
                        float dX = std::abs(cuadradoO.forma.getPosition().x - cuadrado.forma.getPosition().x);
                        float dY = std::abs(cuadradoO.forma.getPosition().y - cuadrado.forma.getPosition().y);
                        if((dX < 10) && (dY < 10)){
                            colision = true;
                            cuadrado.encajado = true;
                            std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
                            break;
                        } else {
                            colision = false;
                            cuadrado.encajado = false;
                            std::cout << "-";
                            continue;
                        }
                    }
                }

                z++;
                if(colision){
                    continue;
                }
            }
            size_t o = 0;
            for (auto &cuadrado : cubos){
                if(o == 0){
                    continue;
                }
                if(cuadrado.encajado){
                    if(o == cubos.size() - 1){
                        /* std::cout << "Ganaste"; */
                        prueba = true;
                    }
                } else {
                    break;
                }
                o++;
            }
        }
    }
}
void minijuegoElectronicaYControl::actualizar(){
    int a = 0;
    for (auto& cuadrado : cubos)
    {
        if(cuadrado.encajado){
            a++;
            if(a == 43){
                juego->cambiarPantalla(std::make_unique<minijuegoMecanicaIndustrial>(juego));
            }
        }
    }
    std::cout << "Actualmente hay: " << std::to_string(a) << std::endl;

}
void minijuegoElectronicaYControl::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(contorno);

    for(auto &linea : lineasVerticales){
        window.draw(linea);
    }
    for(auto &linea : lineasHorizontales){
        window.draw(linea);
    }

    for(auto &cuadrado : cubosObjetivo){
        window.draw(cuadrado.forma);
    }
    for (auto &cuadrado : cubos){
        window.draw(cuadrado.forma);
    }

    window.draw(impresora);
    window.draw(soporte);
    window.draw(puntero);


}