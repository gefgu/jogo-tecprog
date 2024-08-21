#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include "Entidades/Personagens/Personagem.hpp"
#include "CampoDeVisao.hpp"

class Inimigo : public Personagem
{
protected:
    CampoDeVisao visao;

public:
    Inimigo(int px, int py, int vidas, tipoDeEntidade tipo);
    ~Inimigo();
    virtual void atacar() = 0;
    virtual void executar() = 0;
    virtual void lidarColisao(sf::Vector2f intersecao, Entidade *other) = 0;
    CampoDeVisao *getCampoDeVisao();
};

#endif // INIMIGO_HPP
