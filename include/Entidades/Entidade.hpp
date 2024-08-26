#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <SFML/Graphics.hpp>
#include "Ente.hpp"
// #include "Fases/Fase.hpp"

class Fase;

enum tipoDeEntidade
{
    PLATAFORMA = 0,
    JOGADOR,
    FIGHTER,
    ATIRADOR,
    OBSTACULO,
    ESPINHO,
    LIXO,
    MINA,
    VISAO,
    PROJETIL
};

class Entidade : public Ente
{
protected:
    int x, y;
    tipoDeEntidade tipo;
    bool ativo;
    static Fase *pFase;

public:
    Entidade(int px, int py, tipoDeEntidade t);
    virtual ~Entidade();
    virtual void executar() = 0;
    virtual void desenhar() = 0;
    virtual sf::Vector2f getCenter() = 0;
    virtual sf::FloatRect getSize() = 0;
    virtual void lidarColisao(sf::Vector2f intersecao, Entidade *other) = 0;
    const tipoDeEntidade getTipo() const;
    static void setFase(Fase *pF);
    const bool getAtivo() const;
    sf::Vector2f getPosition();
};

#endif // ENTIDADE_HPP
