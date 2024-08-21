#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include "Entidades/Personagens/Personagem.hpp"

class Jogador : public Personagem
{
private:
    float tempoDesdeUltimoPulo;
    float tempoDesdeUltimoEspinho;
    float tempoDesdeUltimoLixo;
    float slowness;
    void mover();

public:
    Jogador(int px, int py, int vidas);
    void atacar() override;
    void executar();
    void lidarColisao(sf::Vector2f intersecao, Entidade *other);
    void reduzirVelocidade(float fator);
};
#endif // JOGADOR_HPP
