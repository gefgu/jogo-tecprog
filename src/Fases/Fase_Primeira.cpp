#include "Fases/Fase_Primeira.hpp"

Fase_Primeira::Fase_Primeira(bool temP2, string filename, int pontos_iniciais) : Fase(filename, pontos_iniciais, 40, temP2)
{
  criarCenario();
  if (filename.empty())
    criaAtiradores();
}

Fase_Primeira::~Fase_Primeira() {}

void Fase_Primeira::criarCenario()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;
  sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_fase_1.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(-largura * 2, -altura * 1);
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
  if (temPlayerDois)
    pGG->draw(vidasJogador2);
  pGG->draw(pontosText);
  caixaDeCorreio.desenhar();
}

void Fase_Primeira::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
  centralizaCamera();
  atualizaVidaJogador();
  atualizaPontos();
  verificaFim();
  desenhar();
}

void Fase_Primeira::criaAtiradores()
{
  int total_atiradores = 3 + (rand() % 2);
  for (int i = 0; i < total_atiradores; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getRandom());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (ATIRADOR_HEIGHT / 2.f);
    Atirador *a = new Atirador(px, py, 3 + (rand() % 3));
    entidades.incluir(a);
    gerenciadorColisoes.incluirEntidadeMovel(a);
    gerenciadorColisoes.incluirEntidadeMovel(a->getCampoDeVisao());
  }
}