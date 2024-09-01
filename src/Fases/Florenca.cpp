#include "Fases/Florenca.hpp"

Florenca::Florenca(bool temP2, string filename, int pontos_iniciais) : Fase(filename, pontos_iniciais, 75, temP2)
{
  criarCenario();

  if (filename.empty())
  {
    criaMina();
    criaSoldadoChefe();
  }
}

Florenca::~Florenca() {}

void Florenca::criarCenario()
{
  int largura = pGG->getWindowSize().x;
  int altura = pGG->getWindowSize().y;
  sf::Texture *texturaFundo = pGG->carregaTextura("./assets/images/fundo_fase_2.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(-largura * 2, -altura * 1);
  fundo.setScale(static_cast<float>(largura) * 4 / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) * 4 / fundo.getTexture()->getSize().y);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Florenca::criaMina()
{
  int total_minas = 10 + (rand() % 5);
  for (int i = 0; i < total_minas; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getOneUsingNormalDistribution());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (MINA_HEIGHT * 2) / 2;
    Mina *m = new Mina(px, py);
    entidades.incluir(m);
    gerenciadorColisoes.incluirEntidadeEstatica(m);
  }
}

void Florenca::criaSoldadoChefe()
{
  int total_soldados = 3;
  for (int i = 0; i < total_soldados; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getOneUsingNormalDistribution());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (SOLDADO_HEIGHT / 2.f);
    SoldadoChefe *s = new SoldadoChefe(px, py, 7 + (rand() % 3));
    entidades.incluir(s);
    gerenciadorColisoes.incluirEntidadeMovel(s);
    gerenciadorColisoes.incluirEntidadeMovel(s->getCampoDeVisao());
  }
}

void Florenca::desenhar()
{
  pGG->draw(fundo);
  plataformas.desenhar();
  caixaDeCorreio.desenhar();
  entidades.desenhar();
  pGG->draw(vidasJogador);
  if (temPlayerDois)
    pGG->draw(vidasJogador2);
  pGG->draw(pontosText);
}

void Florenca::executar()
{
  int tempo = clock.getElapsedTime().asSeconds();
  if (tempo > segundosDesdeInicio)
  {
    segundosDesdeInicio++;
    pontos--;
    pontos = max(pontos, 0);
  }
  gerenciadorColisoes.executar();
  entidades.executar();
  centralizaCamera();
  atualizaVidaJogador();
  atualizaPontos();
  verificaFim();
  desenhar();
}