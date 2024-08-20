#include "Fases/Fase_Segunda.hpp"

Fase_Segunda::Fase_Segunda() : Fase(100)
{
  criarCenario();
}

Fase_Segunda::~Fase_Segunda() {}

void Fase_Segunda::criarCenario()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;
  sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_fase_2.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(-largura, -altura);
  fundo.setScale(static_cast<float>(largura) * 4 / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) * 4 / fundo.getTexture()->getSize().y);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Fase_Segunda::desenhar()
{
  pGG->draw(fundo);
  plataformas.desenhar();
  entidades.desenhar();
  pGG->draw(vidasJogador);
  pGG->draw(pontosText);
}

void Fase_Segunda::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
  atualizaVidaJogador();
  atualizaPontos();
  verificaFim();
  desenhar();
}