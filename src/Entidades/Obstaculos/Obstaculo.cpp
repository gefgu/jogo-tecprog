#include "Entidades/Obstaculos/Obstaculo.hpp"

Obstaculo::Obstaculo(int px, int py, bool dano) : Entidade(px, py), danoso(dano) {}

Obstaculo::~Obstaculo() {}

void Obstaculo::executar()
{
    // Implementação genérica, pode ser sobrescrita pelas subclasses
}
