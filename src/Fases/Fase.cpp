#include "Fases/Fase.hpp"

Fase::Fase() : gerenciadorGrafico(Gerenciador_Grafico::getInstance())
{
  jogador = new Jogador(200, 100, 5);
  entidades.incluir(jogador);
  gerenciadorColisoes.incluirEntidadeMovel(jogador);
  criarCenario();
  criarPlataformas();
  criaEspinhos();
  // sf::Font *fonte = gerenciadorGrafico.carregaFonte("./assets/fonts/INVASION2000.TTF");
  sf::Font *fonte = gerenciadorGrafico.carregaFonte("./assets/fonts/BACKTO1982.TTF");
  vidasJogador.setFont(*fonte);
  vidasJogador.setFillColor(sf::Color::White);
  vidasJogador.setCharacterSize(32);
  atualizaVidaJogador();
}

Fase::~Fase() {}

void Fase::criarCenario()
{
  int largura = gerenciadorGrafico.getWindowSize().x;
  int altura = gerenciadorGrafico.getWindowSize().y;
  sf::Texture *texturaFundo = gerenciadorGrafico.carregaTextura("./assets/images/funda_fase_1_2.png");
  fundo.setTexture(*texturaFundo);
  fundo.setPosition(-largura, -altura);
  fundo.setScale(static_cast<float>(largura) * 4 / fundo.getTexture()->getSize().x,
                 static_cast<float>(altura) * 4 / fundo.getTexture()->getSize().y);
  texturaFundo->setRepeated(true);
  fundo.setTextureRect(sf::IntRect(0, 0, largura * 10, altura * 10));
}

void Fase::criarPlataformas(int qty_plt)
{
  int py = 1075;
  for (int i = -1; i < qty_plt; i++)
  {
    if (i % 3 == 0)
    {
      int val = rand() % 3; // 0 keeps the same
      if (val == 1)
        py += 48;
      else if (val == 2)
        py -= 48;
      if (val == 0 && i > 3)
        i += 2;
    }

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
  gerenciadorGrafico.drawText(vidasJogador);
}

void Fase::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
  atualizaVidaJogador();
}

void Fase::atualizaVidaJogador()
{
  int vidas = jogador->getVidas();
  vidasJogador.setString(std::to_string(vidas) + " Vidas");
  sf::Vector2f pos = gerenciadorGrafico.getTopLeftPosition();
  vidasJogador.setPosition(pos.x + 25, pos.y + 25);
}

void Fase::criaEspinhos()
{
  int total_espinhos = 3 + (rand() % 5);
  for (int i = 0; i < total_espinhos; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getRandom());
    int px = p->getCenter().x - (16 * 3);
    int py = p->getCenter().y - (p->getSize().height);
    Espinho *e = new Espinho(px, py);
    entidades.incluir(e);
    gerenciadorColisoes.incluirEntidadeEstatica(e);
  }
}