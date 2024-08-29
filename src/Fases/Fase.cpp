#include "Fases/Fase.hpp"
#include <cstring>
#include <fstream>
#include <json/json.h> // JSON library that supports C++03
#include <ctime>
#include <sstream>
#include <iomanip>

Fase::Fase(string filename, int pontos_iniciais, int qty_plt, bool temP2) : pontos(pontos_iniciais), finalX(10000), caixaDeCorreio("./assets/images/caixa_de_correio.png"), segundosDesdeInicio(0), _gerenciadorInput(Gerenciador_Input::getInstance()), temPlayerDois(temP2), jogador(NULL), jogador2(NULL)
{
  clock.restart();
  _gerenciadorInput.Attach(this);
  Entidade::setFase(this);
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

  atualizaVidaJogador();
  atualizaPontos();
  caixaDeCorreio.setScale(3, 3);

  if (!filename.empty())
  {
    loadFromJson(filename);
  }
  else
  {
    criarPlataformas(qty_plt);
    criaEspinhos();
    criaLixos();
    criaFighters();
    jogador = new Jogador(200, 100, 10, true);
    entidades.incluir(jogador);
    gerenciadorColisoes.incluirEntidadeMovel(jogador);
    if (temPlayerDois)
    {
      jogador2 = new Jogador(200, 100, 10, false);
      entidades.incluir(jogador2);
      gerenciadorColisoes.incluirEntidadeMovel(jogador2);
    }
    else
    {
      jogador2 = NULL;
    }
  }
  // saveEntitiesToJson();
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
  caixaDeCorreio.setPosition(finalX, py - ((PLATAFORMA_HEIGHT * 3) / 2) + caixaDeCorreio.getSize().height / 4);
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
    Plataforma *p = static_cast<Plataforma *>(plataformas.getOneUsingNormalDistribution());
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
    Plataforma *p = static_cast<Plataforma *>(plataformas.getOneUsingNormalDistribution());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (LIXO_HEIGHT * 3) / 2;
    Lixo *l = new Lixo(px, py);
    entidades.incluir(l);
    gerenciadorColisoes.incluirEntidadeEstatica(l);
  }
}

void Fase::criaFighters()
{
  int total_fighters = 3 + (rand() % 3);
  for (int i = 0; i < total_fighters; i++)
  {
    Plataforma *p = static_cast<Plataforma *>(plataformas.getOneUsingNormalDistribution());
    int px = p->getCenter().x;
    int py = p->getCenter().y - (p->getSize().height / 2.f) - (FIGHTER_HEIGHT / 2.f);
    Fighter *f = new Fighter(px, py, 3 + (rand() % 3));
    entidades.incluir(f);
    gerenciadorColisoes.incluirEntidadeMovel(f);
    gerenciadorColisoes.incluirEntidadeMovel(f->getCampoDeVisao());
  }
}

void Fase::atualizaVidaJogador()
{
  if (jogador == NULL)
    return;
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
  if (jogador == NULL)
    return;
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

Projetil *Fase::addProjetil(int px, int py, int direcao, tipoDeEntidade atirador)
{
  Projetil *p = new Projetil(px, py, direcao, atirador);
  entidades.incluir(p);
  gerenciadorColisoes.incluirEntidadeMovel(p);
  return p;
}

Granada *Fase::addGranada(int px, int py, int direcao, tipoDeEntidade atirador)
{
  Granada *g = new Granada(px, py, direcao, atirador);
  entidades.incluir(g);
  gerenciadorColisoes.incluirEntidadeMovel(g);
  return g;
}

void Fase::alteraPontos(int soma)
{
  if (soma > 0)
  {
    pontos += soma;
    if (jogador)
    {
      ++(*jogador);
    }
    if (temPlayerDois && jogador2)
    {
      ++(*jogador2);
    }
  }
  else
  {
    pontos += soma;
  }
  pontos = std::max(pontos, 0);
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

  // Get the current time
  std::time_t now = std::time(0);
  std::tm *now_tm = std::localtime(&now);

  // Format the time to create a filename
  std::ostringstream filename;
  filename << "salvo_" << (now_tm->tm_year + 1900)
           << std::setw(2) << std::setfill('0') << (now_tm->tm_mon + 1)
           << std::setw(2) << std::setfill('0') << now_tm->tm_mday << "_"
           << std::setw(2) << std::setfill('0') << now_tm->tm_hour
           << std::setw(2) << std::setfill('0') << now_tm->tm_min
           << std::setw(2) << std::setfill('0') << now_tm->tm_sec << ".json";

  // Save to a file with the generated filename
  std::ofstream file(filename.str().c_str());
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

void Fase::loadFromJson(string filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    // Handle error: file could not be opened
    return;
  }

  Json::Value root;
  file >> root;
  file.close();

  // Load points
  if (root.isMember("points"))
  {
    pontos = root["points"].asInt();
  }

  // Load phase type
  if (root.isMember("fase"))
  {
    // Gerenciador_Estado::getInstance().setEstadoJogo(root["fase"].asString());
    cout << "Fase: " << root["fase"].asString() << endl;
  }

  // Load platforms
  if (root.isMember("platforms"))
  {
    // plataformas.clear(); // Clear existing platforms if any
    Json::Value platformJson;
    for (Json::Value::ArrayIndex i = 0; i < root["platforms"].size(); ++i)
    {
      platformJson = root["platforms"][i];
      Plataforma *plataforma = new Plataforma(platformJson["x"].asInt(), platformJson["y"].asInt());
      plataformas.incluir(plataforma);
      gerenciadorColisoes.incluirEntidadeEstatica(plataforma);
    }
    finalX = platformJson["x"].asInt() - PLATAFORMA_WIDTH * 3;
    caixaDeCorreio.setPosition(finalX, platformJson["y"].asInt() - ((PLATAFORMA_HEIGHT * 3) / 2) + caixaDeCorreio.getSize().height / 2);
  }
  cout << "Added " << root["platforms"].size() << " platforms" << endl;

  // Load other entities
  if (root.isMember("entities"))
  {
    // entidades.clear(); // Clear existing entities if any
    for (Json::Value::ArrayIndex i = 0; i < root["entities"].size(); ++i)
    {
      Json::Value entityJson = root["entities"][i];
      tipoDeEntidade entityType = (tipoDeEntidade)entityJson["type"].asInt();
      if (entityType == JOGADOR)
      {
        if ((bool)entityJson["is_p1"].asInt())
        {
          jogador = new Jogador(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["vidas"].asInt(), true);
          entidades.incluir(jogador);
          gerenciadorColisoes.incluirEntidadeMovel(jogador);
        }
        else
        {
          temPlayerDois = true;
          jogador2 = new Jogador(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["vidas"].asInt(), false);
          entidades.incluir(jogador2);
          gerenciadorColisoes.incluirEntidadeMovel(jogador2);
        }
        cout << "Loaded player" << endl;
      }
      if (entityType == ESPINHO)
      {
        Espinho *espinho = new Espinho(entityJson["x"].asInt(), entityJson["y"].asInt());
        entidades.incluir(espinho);
        gerenciadorColisoes.incluirEntidadeEstatica(espinho);
        cout << "Loaded espinho" << endl;
      }
      else if (entityType == LIXO)
      {
        Lixo *lixo = new Lixo(entityJson["x"].asInt(), entityJson["y"].asInt());
        entidades.incluir(lixo);
        gerenciadorColisoes.incluirEntidadeEstatica(lixo);
        cout << "Loaded lixo" << endl;
      }
      else if (entityType == MINA)
      {
        Mina *mina = new Mina(entityJson["x"].asInt(), entityJson["y"].asInt());
        entidades.incluir(mina);
        gerenciadorColisoes.incluirEntidadeEstatica(mina);
        cout << "Loaded mina" << endl;
      }

      else if (entityType == FIGHTER)
      {
        // cout << entityType["vidas"].asInt() << endl;
        Fighter *fighter = new Fighter(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["vidas"].asInt());
        entidades.incluir(fighter);
        gerenciadorColisoes.incluirEntidadeMovel(fighter);
        gerenciadorColisoes.incluirEntidadeMovel(fighter->getCampoDeVisao());
        cout << "Loaded figther" << endl;
      }
      else if (entityType == ATIRADOR)
      {
        Atirador *atirador = new Atirador(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["vidas"].asInt());
        entidades.incluir(atirador);
        gerenciadorColisoes.incluirEntidadeMovel(atirador);
        gerenciadorColisoes.incluirEntidadeMovel(atirador->getCampoDeVisao());
        cout << "Loaded atirador" << endl;
      }
      else if (entityType == SOLDADO)
      {
        SoldadoChefe *soldado = new SoldadoChefe(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["vidas"].asInt());
        entidades.incluir(soldado);
        gerenciadorColisoes.incluirEntidadeMovel(soldado);
        gerenciadorColisoes.incluirEntidadeMovel(soldado->getCampoDeVisao());
        cout << "Loaded soldado" << endl;
      }
      else if (entityType == PROJETIL)
      {
        Projetil *projetil = new Projetil(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["direcao"].asInt(), (tipoDeEntidade)entityJson["atirador"].asInt());
        entidades.incluir(projetil);
        gerenciadorColisoes.incluirEntidadeMovel(projetil);
        cout << "Loaded projetil" << endl;
      }
      else if (entityType == GRANADA)
      {
        Granada *granada = new Granada(entityJson["x"].asInt(), entityJson["y"].asInt(), entityJson["direcao"].asInt(), (tipoDeEntidade)entityJson["atirador"].asInt());
        entidades.incluir(granada);
        gerenciadorColisoes.incluirEntidadeMovel(granada);
        cout << "Loaded granada" << endl;
      }
    }
  }
}