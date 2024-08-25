#include "Fases/Fase.hpp"
#include <cstring>
#include <fstream>
#include <json/json.h> // JSON library that supports C++03

Fase::Fase(int pontos_iniciais, int qty_plt, bool temP2) : pontos(pontos_iniciais), finalX(10000), caixaDeCorreio("./assets/images/caixa_de_correio.png"), segundosDesdeInicio(0), _gerenciadorInput(Gerenciador_Input::getInstance()), temPlayerDois(temP2), jogador(NULL), jogador2(NULL)
{
  clock.restart();
  _gerenciadorInput.Attach(this);
  Entidade::setFase(this);
  jogador = new Jogador(200, 100, 5, true);
  entidades.incluir(jogador);
  gerenciadorColisoes.incluirEntidadeMovel(jogador);
  if (temPlayerDois)
  {
    jogador2 = new Jogador(200, 100, 5, false);
    entidades.incluir(jogador2);
    gerenciadorColisoes.incluirEntidadeMovel(jogador2);
  }
  else
  {
    jogador2 = NULL;
  }

  criarPlataformas(qty_plt);
  criaEspinhos();
  criaLixos();
  criaMina();
  criaFighters();
  criaAtiradores();
  // sf::Font *fonte = pGG->carregaFonte("./assets/fonts/INVASION2000.TTF");
  sf::Font *fonte = pGG->carregaFonte("./assets/fonts/BACKTO1982.TTF");
  vidasJogador.setFont(*fonte);
  vidasJogador.setFillColor(sf::Color::White);
  vidasJogador.setCharacterSize(32);
  vidasJogador2.setFont(*fonte);
  vidasJogador2.setFillColor(sf::Color::White);
  vidasJogador2.setCharacterSize(32);

  pontosText.setFont(*fonte);
  pontosText.setFillColor(sf::Color::White);
  pontosText.setCharacterSize(32);

  caixaDeCorreio.setScale(3, 3);

  atualizaVidaJogador();
  atualizaPontos();
  saveEntitiesToJson();
}

Fase::~Fase()
{
  _gerenciadorInput.Detach(this);
}

void Fase::criarPlataformas(int qty_plt)
{
  int py = 1075;
  int i;
  for (i = -1; i < qty_plt; i++)
  {
    if (i % 5 == 0)
    {
      int val = rand() % 3; // 0 keeps the same
      if (val == 1)
        py += 64;
      else if (val == 2)
        py -= 64;
      if (val == 0 && i > 3)
        i += 2;
    }

    // inclui duas no mesmo nível sempre
    Plataforma *p = new Plataforma(PLATAFORMA_WIDTH * 3 * i, py);
    plataformas.incluir(p);
    gerenciadorColisoes.incluirEntidadeEstatica(p);
  }
  finalX = PLATAFORMA_WIDTH * 3 * (i - 1);
  caixaDeCorreio.setPosition(finalX, py - ((PLATAFORMA_HEIGHT * 3) / 2) + caixaDeCorreio.getSize().height / 2);
}

void Fase::desenhar()
{
  pGG->draw(fundo);
  plataformas.desenhar();
  entidades.desenhar();
  pGG->draw(vidasJogador);
  if (temPlayerDois)
    pGG->draw(vidasJogador2);
  pGG->draw(pontosText);
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
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (ESPINHO_HEIGHT * 3) / 2;
    Espinho *e = new Espinho(px, py);
    entidades.incluir(e);
    gerenciadorColisoes.incluirEntidadeEstatica(e);
  }
}

void Fase::criaLixos()
{
  int total_lixos = 3 + (rand() % 5);
  for (int i = 0; i < total_lixos; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getRandom());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (LIXO_HEIGHT * 3) / 2;
    Lixo *l = new Lixo(px, py);
    entidades.incluir(l);
    gerenciadorColisoes.incluirEntidadeEstatica(l);
  }
}

void Fase::criaMina()
{
  int total_minas = 10 + (rand() % 5);
  for (int i = 0; i < total_minas; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getRandom());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (MINA_HEIGHT * 2) / 2;
    Mina *m = new Mina(px, py);
    entidades.incluir(m);
    gerenciadorColisoes.incluirEntidadeEstatica(m);
  }
}

void Fase::criaFighters()
{
  int total_fighters = 3 + (rand() % 3);
  for (int i = 0; i < total_fighters; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getRandom());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (FIGHTER_HEIGHT / 2.f);
    Fighter *f = new Fighter(px, py, 3 + (rand() % 4));
    entidades.incluir(f);
    gerenciadorColisoes.incluirEntidadeMovel(f);
    gerenciadorColisoes.incluirEntidadeMovel(f->getCampoDeVisao());
  }
}

void Fase::criaAtiradores()
{
  int total_atiradores = 1 + (rand() % 3);
  for (int i = 0; i < total_atiradores; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getRandom());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (ATIRADOR_HEIGHT / 2.f);
    Atirador *a = new Atirador(px, py, 3 + (rand() % 4));
    entidades.incluir(a);
    gerenciadorColisoes.incluirEntidadeMovel(a);
    gerenciadorColisoes.incluirEntidadeMovel(a->getCampoDeVisao());
  }
}

void Fase::atualizaVidaJogador()
{
  int vidas = jogador->getVidas();
  vidasJogador.setString(std::to_string(vidas) + " Vidas");
  sf::Vector2f pos = pGG->getTopLeftPosition();
  vidasJogador.setPosition(pos.x + 25, pos.y + 25);
  if (temPlayerDois)
  {
    vidas = jogador2->getVidas();
    vidasJogador2.setString(std::to_string(vidas) + " Vidas");
    sf::Vector2f pos = pGG->getTopRightPosition();
    vidasJogador2.setPosition(pos.x - vidasJogador2.getGlobalBounds().width - 25, pos.y + 25);
  }
}

void Fase::atualizaPontos()
{
  pontosText.setString(std::to_string(pontos) + " Pontos");
  sf::Vector2f pos = pGG->getTopLeftPosition();
  pontosText.setPosition(pos.x + 25, pos.y + 75);
}

void Fase::verificaFim()
{
  bool deadCondition = (jogador->getMorto() && !temPlayerDois) || (temPlayerDois && jogador->getMorto() && jogador2->getMorto());
  bool endCondition = (jogador->getCenter().x >= finalX && !temPlayerDois) || (temPlayerDois && jogador->getCenter().x >= finalX && jogador2->getCenter().x >= finalX);
  if (deadCondition || endCondition)
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

void Fase::addProjetil(int px, int py, int direcao, tipoDeEntidade atirador)
{
  Projetil *p = new Projetil(px, py, direcao, atirador);
  entidades.incluir(p);
  gerenciadorColisoes.incluirEntidadeMovel(p);
}

void Fase::alteraPontos(int soma)
{
  pontos += soma;
  pontos = max(pontos, 0);
}

void Fase::Update(const char *teclaPressionada)
{
  if (strcmp(teclaPressionada, "Escape") == 0)
    Gerenciador_Estado::getInstance().setEstadoJogo(PAUSE);
}

void Fase::centralizaCamera()
{
  int x, y;
  if (temPlayerDois)
  {
    if (!jogador->getMorto() && !jogador2->getMorto())
    {
      x = (jogador->getCenter().x + jogador2->getCenter().x) / 2;
      y = (jogador->getCenter().y + jogador2->getCenter().y) / 2;
    }
    else if (!jogador->getMorto())
    {
      x = jogador->getCenter().x;
      y = jogador->getCenter().y;
    }
    else
    {
      x = jogador2->getCenter().x;
      y = jogador2->getCenter().y;
    }
  }
  else
  {
    x = jogador->getCenter().x;
    y = jogador->getCenter().y;
  }
  pGG->centerCamera(sf::Vector2f(x, y));
}

void Fase::saveEntitiesToJson()
{
  Json::Value root;

  root["points"] = getPontos();
  root["fase"] = Gerenciador_Estado::getInstance().getEstadoJogo();

  // Save platforms using the toJsonArray() method
  root["platforms"] = plataformas.toJsonArray();

  // Save other entities using the toJsonArray() method
  root["entities"] = entidades.toJsonArray();

  // Save to a file
  std::ofstream file("salvo.json");
  if (file.is_open())
  {
    file << root;
    file.close();
  }
  else
  {
    // Handle error: file could not be opened
  }
}