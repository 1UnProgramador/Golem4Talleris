#pragma once
#include <SFML/Graphics.hpp>

class objColisionable
{
private:
    
public:
    virtual sf::FloatRect getBounds() const = 0;  //Se obliga al heredador a implementarlo
    virtual bool isCollision(const objColisionable& col) const;
    virtual ~objColisionable();
};


