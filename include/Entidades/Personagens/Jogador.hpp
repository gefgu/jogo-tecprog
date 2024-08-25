#pragma once

#include "Entidades/Personagens/Personagem.hpp"
#include "Controladores/Observer.hpp"
#include "Gerenciadores/Gerenciador_Input.hpp"

class Jogador : public Personagem, Observer
{
private:
    float tempoDesdeUltimoPulo;
    float tempoDesdeUltimoEspinho;
    float tempoDesdeUltimoLixo;
    float tempoDesdeUltimoTiro;
    float tempoDesdeUltimaMina;
    float tempoDesdeUltimaAcao;
    float slowness;
    Gerenciador_Input &_gerenciadorInput;

    void
    mover();
    void correr();
    void pular();
    void andar(int newDirection);

public:
    Jogador(int px, int py, int vidas);
    ~Jogador();
    void atacar() override;
    void executar();
    void lidarColisao(sf::Vector2f intersecao, Entidade *other);
    void reduzirVelocidade(float fator);
    void aplicarForcaRepulsao(float forcaX, float forcaY);
    void Update(const char *teclaPressionada);
};
