#include "Fases/Fase.hpp"

Fase::Fase() : gerenciadorGrafico(Gerenciador_Grafico::getInstance())
{
  jogador = new Jogador(200, 100, 5);
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
  fundo.setPosition(-largura, -altura);
  fundo.setScale(static_cast<float>(largura) * 3 / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) * 3 / fundo.getTexture()->getSize().y);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Fase::criarPlataformas(int qty_plt)
{
  int py = 1075;
  for (int i = 0; i < qty_plt; i++)
  {
    int val = rand() % 3; // 0 keeps the same
    if (val == 1)
      py += 48;
    else if (val == 2)
      py -= 48;
    if (val > 0 && i > 3)
      i++;

    // inclui duas no mesmo nível sempre
    Plataforma *p = new Plataforma(32 * 3 * i, py);
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

void Fase::mostraVidaJogador()
{
}