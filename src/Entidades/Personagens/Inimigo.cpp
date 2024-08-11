#include "Entidades/Personagens/Inimigo.hpp"

Inimigo::Inimigo(int px, int py, int vidas, float atk) : Personagem(px, py, vidas), ataque(atk) {}

Inimigo::~Inimigo() {}

void Inimigo::atacar()
{
    // Lógica de ataque do inimigo
}

void Inimigo::executar()
{
    // Lógica específica para o inimigo
}
