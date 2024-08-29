#pragma once

#include "Entidades/Personagens/Personagem.hpp"
#include "Controladores/Observer.hpp"
#include "Gerenciadores/Gerenciador_Input.hpp"

class Jogador : public Personagem, Observer
{
private:
    Gerenciador_Input &_gerenciadorInput;
    float tempoDesdeUltimoPulo;
    float tempoDesdeUltimoEspinho;
    float tempoDesdeUltimoLixo;
    float tempoDesdeUltimoTiro;
    float tempoDesdeUltimaMina;
    float tempoDesdeUltimaAcao;
    float slowness;
    const char *teclaEsquerda;
    const char *teclaDireita;
    const char *teclaPulo;
    const char *teclaCorrida;
    const char *teclaTiro;
    bool isP1;

    void
    mover();
    void correr();
    void pular();
    void andar(int newDirection);
    void limitMovementByCamera(); // don't go past the view

public:
    Jogador(int px, int py, int vidas, bool player1 = true);
    ~Jogador();
    void atacar() override;
    void executar();
    void lidarColisao(sf::Vector2f intersecao, Entidade *other);
    void reduzirVelocidade(float fator);
    Jogador& operator++(); 
    void aplicarForcaRepulsao(float forcaX, float forcaY);
    void Update(const char *teclaPressionada);
    bool getP1();
    Json::Value gravar();
};
