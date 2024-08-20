#include "Entidades/Personagens/Personagem.hpp"

Personagem::Personagem(int px, int py, float vx, float vy, int vidas) : Entidade(px, py, tipoDeEntidade::JOGADOR), num_vidas(vidas), velocidadeX(vx), velocidadeY(vy) {}

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
    num_vidas = max(0, num_vidas - vidas_perdidas);
}