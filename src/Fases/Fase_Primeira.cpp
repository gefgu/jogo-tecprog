#include "Fases/Fase_Primeira.hpp"

Fase_Primeira::Fase_Primeira() : Fase(100)
{
  criarCenario();
}

Fase_Primeira::~Fase_Primeira() {}

void Fase_Primeira::criarCenario()
{
  int largura = gerenciadorGrafico.getWindowSize().x;
  int altura = gerenciadorGrafico.getWindowSize().y;
  sf::Texture *texturaFundo = gerenciadorGrafico.carregaTextura("./assets/images/fundo_fase_1.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(-largura, -altura);
  fundo.setScale(static_cast<float>(largura) * 4 / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) * 4 / fundo.getTexture()->getSize().y);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Fase_Primeira::desenhar()
{
  gerenciadorGrafico.drawSprite(fundo);
  plataformas.desenhar();
  entidades.desenhar();
  gerenciadorGrafico.drawText(vidasJogador);
  gerenciadorGrafico.drawText(pontosText);
}

void Fase_Primeira::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
  atualizaVidaJogador();
  atualizaPontos();
  verificaFim();
  desenhar();
}