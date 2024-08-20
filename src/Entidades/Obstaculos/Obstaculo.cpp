#include "Entidades/Obstaculos/Obstaculo.hpp"

Obstaculo::Obstaculo(int px, int py, tipoDeEntidade tipo) : Entidade(px, py, tipo) {}

Obstaculo::~Obstaculo() {}

void Obstaculo::executar()
{
    // Implementação genérica, pode ser sobrescrita pelas subclasses
}
