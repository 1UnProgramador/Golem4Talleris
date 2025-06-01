#include <SFML/Graphics.hpp>
class Golem : public sf::Drawable
{
    private:
    sf::Sprite sprite;
    sf::Texture texture;
    float velocidad = 10;
    float posicionX;
    float posicionY;

    public:
    Golem(float pInicialX, float pInicialY);
    void update(sf::VideoMode desktopMode);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

