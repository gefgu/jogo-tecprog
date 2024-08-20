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
    tipoDeEntidade tipo;

public:
    Entidade(int px, int py, tipoDeEntidade t);
    virtual ~Entidade();
    virtual void executar() = 0;
    virtual void desenhar() = 0;
    virtual sf::Vector2f getCenter() = 0;
    virtual sf::FloatRect getSize() = 0;
    virtual void lidarColisao(sf::Vector2f intersecao, Entidade *other) = 0;
    const tipoDeEntidade getTipo() const;
};

#endif // ENTIDADE_HPP
