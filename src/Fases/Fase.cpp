#include "Fases/Fase.hpp"

Fase::Fase(int qty_plt) : gerenciadorGrafico(Gerenciador_Grafico::getInstance()), pontos(1000), finalX(10000)
{
  clock.restart();
  jogador = new Jogador(200, 100, 5);
  entidades.incluir(jogador);
  gerenciadorColisoes.incluirEntidadeMovel(jogador);
  criarPlataformas(qty_plt);
  criaEspinhos();
  // sf::Font *fonte = gerenciadorGrafico.carregaFonte("./assets/fonts/INVASION2000.TTF");
  sf::Font *fonte = gerenciadorGrafico.carregaFonte("./assets/fonts/BACKTO1982.TTF");
  vidasJogador.setFont(*fonte);
  vidasJogador.setFillColor(sf::Color::White);
  vidasJogador.setCharacterSize(32);

  pontosText.setFont(*fonte);
  pontosText.setFillColor(sf::Color::White);
  pontosText.setCharacterSize(32);

  atualizaVidaJogador();
  atualizaPontos();
}

Fase::~Fase() {}

void Fase::criarPlataformas(int qty_plt)
{
  int py = 1075;
  int i;
  for (i = -1; i < qty_plt; i++)
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
  finalX = 32 * 3 * (i - 1);
}

void Fase::desenhar()
{
  gerenciadorGrafico.drawSprite(fundo);
  plataformas.desenhar();
  entidades.desenhar();
  gerenciadorGrafico.drawText(vidasJogador);
  gerenciadorGrafico.drawText(pontosText);
}

void Fase::executar()
{
  gerenciadorColisoes.executar();
  entidades.executar();
  atualizaVidaJogador();
  atualizaPontos();
  verificaFim();
  desenhar();
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

void Fase::atualizaVidaJogador()
{
  int vidas = jogador->getVidas();
  vidasJogador.setString(std::to_string(vidas) + " Vidas");
  sf::Vector2f pos = gerenciadorGrafico.getTopLeftPosition();
  vidasJogador.setPosition(pos.x + 25, pos.y + 25);
}

void Fase::atualizaPontos()
{
  int tempo = clock.getElapsedTime().asSeconds();
  pontos = 1000 - tempo;
  pontosText.setString(std::to_string(pontos) + " Pontos");
  sf::Vector2f pos = gerenciadorGrafico.getTopLeftPosition();
  pontosText.setPosition(pos.x + 25, pos.y + 75);
}

void Fase::verificaFim()
{
  if (jogador->getVidas() <= 0 || jogador->getCenter().x >= finalX)
  {
    fimDeJogo();
  }
}

void Fase::fimDeJogo()
{
  Gerenciador_Estado::getInstance().setEstadoJogo(estadoJogo::GAMEOVER);
}

int Fase::getPontos()
{
  return pontos;
}