#include "Entidades/Obstaculos/Obstaculo.hpp"

Obstaculo::Obstaculo(int px, int py, bool dano) : Entidade(tipoDeEntidade::OBSTACULO), danoso(dano) {}

Obstaculo::~Obstaculo() {}

void Obstaculo::executar()
{
    // Implementação genérica, pode ser sobrescrita pelas subclasses
}
