#include "Fases/Fase_Primeira.hpp"

Fase_Primeira::Fase_Primeira() : Fase()
{
}

Fase_Primeira::~Fase_Primeira() {}

void Fase_Primeira::desenhar()
{
  gerenciadorGrafico.drawSprite(fundo);
  plataformas.desenhar();
  entidades.desenhar();
}

void Fase_Primeira::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
}