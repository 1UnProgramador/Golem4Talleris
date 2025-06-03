#include "../include/objColisionable.h"

bool objColisionable::isCollision(const objColisionable& obj) const{
    return getBounds().intersects(obj.getBounds());
}

objColisionable::~objColisionable() {}