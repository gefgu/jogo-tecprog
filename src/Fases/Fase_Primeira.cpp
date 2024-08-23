#include "Fases/Fase_Primeira.hpp"

Fase_Primeira::Fase_Primeira(int pontos_iniciais) : Fase(pontos_iniciais, 40)
{
  criarCenario();
}

Fase_Primeira::~Fase_Primeira() {}

void Fase_Primeira::criarCenario()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;
  sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_fase_1.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(-largura * 2, -altura * 2);
  float scaleX = static_cast<float>(largura) * 4 / fundo.getTexture()->getSize().x;
  float scaleY = static_cast<float>(altura) * 4 / fundo.getTexture()->getSize().y;
  fundo.setScale(scaleX, scaleY);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Fase_Primeira::desenhar()
{
  int tempo = clock.getElapsedTime().asSeconds();
  if (tempo > segundosDesdeInicio)
  {
    segundosDesdeInicio++;
    pontos--;
  }

  pGG->draw(fundo);
  plataformas.desenhar();
  entidades.desenhar();
  pGG->draw(vidasJogador);
  pGG->draw(pontosText);
  caixaDeCorreio.desenhar();
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