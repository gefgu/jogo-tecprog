#include "Entidades/Personagens/Inimigo.hpp"

Inimigo::Inimigo(int px, int py, int vidas, tipoDeEntidade tipo) : Personagem(px, py, 0, 0, vidas, tipo)
{
}

Inimigo::~Inimigo() {}

CampoDeVisao *Inimigo::getCampoDeVisao()
{
  return &visao;
}