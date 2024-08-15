#include "Entidades/Personagens/Personagem.hpp"

Personagem::Personagem(float px, float py, int vidas) : Entidade(px, py), num_vidas(vidas), velocidadeX(50.0) {}

Personagem::~Personagem() {}

void Personagem::executar()
{
    // Implementação genérica, pode ser sobrescrita pelas subclasses
}

void Personagem::desenhar() {}