#include "Entidades/Personagens/Personagem.hpp"

Personagem::Personagem(float px, float py, int vidas) : Entidade(tipoDeEntidade::JOGADOR), num_vidas(vidas), velocidadeX(50.0) {}

Personagem::~Personagem() {}

void Personagem::executar()
{
    // Implementação genérica, pode ser sobrescrita pelas subclasses
}

void Personagem::desenhar() {}

int Personagem::getVidas()
{
    return num_vidas;
}

void Personagem::recebeDano(int vidas_perdidas)
{
    num_vidas = min(0, num_vidas - vidas_perdidas);
}