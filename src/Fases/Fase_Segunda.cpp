#include "Fases/Fase_Segunda.hpp"

Fase_Segunda::Fase_Segunda(bool temP2, int pontos_iniciais) : Fase(pontos_iniciais, 50, temP2)
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
  fundo.setPosition(-largura * 2, -altura * 2);
  fundo.setScale(static_cast<float>(largura) * 4 / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) * 4 / fundo.getTexture()->getSize().y);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Fase_Segunda::desenhar()
{
  int tempo = clock.getElapsedTime().asSeconds();
  if (tempo > segundosDesdeInicio)
  {
    segundosDesdeInicio++;
    pontos--;
  }
  pGG->draw(fundo);
  plataformas.desenhar();
  caixaDeCorreio.desenhar();
  entidades.desenhar();
  pGG->draw(vidasJogador);
  if (temPlayerDois)
    pGG->draw(vidasJogador2);
  pGG->draw(pontosText);
}

void Fase_Segunda::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
  centralizaCamera();
  atualizaVidaJogador();
  atualizaPontos();
  verificaFim();
  desenhar();
}