#include "Entidades/Personagens/Inimigo.hpp"

Inimigo::Inimigo(int px, int py, int vidas, float atk) : Personagem(px, py, 0, 0, vidas)
{
}

Inimigo::~Inimigo() {}

void Inimigo::atacar()
{
    // Lógica de ataque do inimigo
}

void Inimigo::executar()
{
    // Lógica específica para o inimigo
}
