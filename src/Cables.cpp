#include "../include/Cables.h"
#include <SFML/Graphics.hpp>










void Cables::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(spriteCable, states);
}

sf::FloatRect Cables::getBounds() const{
    return spriteCable.getGlobalBounds();

}