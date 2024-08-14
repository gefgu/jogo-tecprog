#include "Fases/Fase.hpp"

Fase::Fase() : gerenciadorGrafico(Gerenciador_Grafico::getInstance())
{
  int largura = gerenciadorGrafico.getWindowSize().x;
  int altura = gerenciadorGrafico.getWindowSize().y;
  sf::Texture *texturaFundo = gerenciadorGrafico.carregaTextura("./assets/images/fundo_fase_1.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(0, 0);
  fundo.setScale(static_cast<float>(largura) / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) / fundo.getTexture()->getSize().y);
}

Fase::~Fase() {}

void Fase::desenhar()
{
  gerenciadorGrafico.drawSprite(fundo);
}