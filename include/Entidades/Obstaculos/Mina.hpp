#ifndef MINA_HPP
#define MINA_HPP

#include "Entidades/Obstaculos/Obstaculo.hpp"
#include "Entidades/Personagens/Jogador.hpp"

const int MINA_HEIGHT = 26;

class Mina : public Obstaculo
{
private:
    float fator_de_repulsao;

public:
    Mina(int px, int py);
    ~Mina();

    void executar() override;
    void lidarColisao(sf::Vector2f intersecao, Entidade *other) override;
};

#endif
