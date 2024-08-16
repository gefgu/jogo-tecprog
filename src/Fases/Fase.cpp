#include "Fases/Fase.hpp"

Fase::Fase() : gerenciadorGrafico(Gerenciador_Grafico::getInstance())
{
  jogador = new Jogador(200, 100, 3);
  entidades.incluir(jogador);
  gerenciadorColisoes.incluirEntidadeMovel(jogador);
  criarCenario();
  criarPlataformas();
}

Fase::~Fase() {}

void Fase::criarCenario()
{
  int largura = gerenciadorGrafico.getWindowSize().x;
  int altura = gerenciadorGrafico.getWindowSize().y;
  sf::Texture *texturaFundo = gerenciadorGrafico.carregaTextura("./assets/images/funda_fase_1_2.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(0, 0);
  fundo.setScale(static_cast<float>(largura) / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) / fundo.getTexture()->getSize().y);
}

void Fase::criarPlataformas()
{
  for (int i = 0; i < 30; i++)
  {
    Plataforma *p = new Plataforma(66 * i, 1075);
    plataformas.incluir(p);
    gerenciadorColisoes.incluirEntidadeEstatica(p);
  }
}

void Fase::desenhar()
{
  gerenciadorGrafico.drawSprite(fundo);
  plataformas.desenhar();
  entidades.desenhar();
}

void Fase::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
}