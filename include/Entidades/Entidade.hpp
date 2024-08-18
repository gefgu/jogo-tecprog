#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <SFML/Graphics.hpp>
#include "Ente.hpp"

enum tipoDeEntidade
{
    PLATAFORMA = 0,
    JOGADOR,
    OBSTACULO,
    ESPINHO
};

class Entidade : public Ente
{
protected:
    int x, y;
    sf::RectangleShape shape;
    tipoDeEntidade tipo;

public:
    Entidade(tipoDeEntidade t);
    virtual ~Entidade();
    virtual void executar() = 0;
    void desenhar(sf::RenderWindow &window);
    virtual void desenhar();
    virtual sf::Vector2f getCenter();
    virtual sf::FloatRect getSize();
    virtual void lidarColisao(sf::Vector2f intersecao, Entidade *other) = 0;
    const tipoDeEntidade getTipo() const;
};

#endif // ENTIDADE_HPP
