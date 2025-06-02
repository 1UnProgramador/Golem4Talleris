#include <SFML/Graphics.hpp>
class Obstaculo : public sf::Drawable
{
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        float velocidad = 10;
        float posicionX;
        float posicionY;

    public:
        Obstaculo(int plataformaHeight, float posicionYPlataforma);
        void update();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

