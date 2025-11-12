#include "../../include/logica/musicManager.h"

#include "assetManager.h"

bool MusicManager::reproducir(const unsigned char* datos, unsigned int tamano, const std::string& id, bool loop, float volumen) {
    if (musicaActual != id) {
        musica.stop();

        if (!musica.openFromMemory(datos, tamano))
            return false;

        musica.setLoop(loop);
        musica.setVolume(volumen);
        musica.play();
        musicaActual = id;
    } else if (musica.getStatus() != sf::Music::Playing) {
        musica.play(); // reanudar si estaba pausada
    }

    return true;
}

void MusicManager::pausar() {
    if (musica.getStatus() == sf::Music::Playing)
        musica.pause();
}

void MusicManager::detener() {
    musica.stop();
    musicaActual.clear();
}