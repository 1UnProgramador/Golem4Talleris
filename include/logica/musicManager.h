#pragma once
#include <SFML/Audio.hpp>
#include <string>

class MusicManager {
private:
    sf::Music musica;
    std::string musicaActual;

    MusicManager() = default; // constructor privado (singleton)
public:
    static MusicManager& getInstancia() {
        static MusicManager instancia;
        return instancia;
    }

    bool reproducir(const unsigned char* datos, unsigned int tamano, const std::string& id, bool loop = true, float volumen = 100.f);
    void pausar();
    void detener();
};
