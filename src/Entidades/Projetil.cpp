#include "Entidades/Projetil.hpp"
#include "Entidades/Personagens/Atirador.hpp"

const char *PROJETIL_PATH = "./assets/images/bullet.png";

const float GRAVIDADE = 9.8f;    // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f; // Duração de cada frame (em segundos) - para 60 FPS

Projetil::Projetil(int px, int py, int direcao, tipoDeEntidade p) : Entidade(px, py, tipoDeEntidade::PROJETIL),
                                                                    visual(PROJETIL_PATH, false), direcao(direcao), dano(1), velocidadeY(0), atirador(p)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 14, 5));
  visual.setScale(3, 3);
}

Projetil::~Projetil()
{
}

void Projetil::desenhar()
{
  visual.desenhar();
}

void Projetil::executar()
{
  float elapsedTime = pGG->getElapsedTime();
  aplicarGravidade();
  x += direcao * (elapsedTime) * 1.5;
  y += velocidadeY;
  visual.setPosition(x, y);
}

sf::Vector2f Projetil::getCenter()
{
  return visual.getCenter();
}

sf::FloatRect Projetil::getSize()
{
  return visual.getSize();
}

void Projetil::aplicarGravidade()
{
  float elapsed_time = pGG->getElapsedTime();
  velocidadeY += 2 * GRAVIDADE * (elapsed_time / 1000.0f) / 10.f;
}

void Projetil::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == FIGHTER && !static_cast<Fighter *>(other)->getMorto() && atirador != ATIRADOR)
  {
    static_cast<Fighter *>(other)->recebeDano(dano);
    ativo = false;
  }

  if (other->getTipo() == ATIRADOR && !static_cast<Fighter *>(other)->getMorto() && atirador != ATIRADOR)
  {
    static_cast<Atirador *>(other)->recebeDano(dano);
    ativo = false;
  }
  if (other->getTipo() == JOGADOR && !static_cast<Jogador *>(other)->getMorto() && atirador != JOGADOR)
  {
    static_cast<Jogador *>(other)->recebeDano(dano);
    ativo = false;
  }

  if (other->getTipo() == tipoDeEntidade::PLATAFORMA || other->getTipo() == PROJETIL)
  {
    ativo = false;
  }
}

tipoDeEntidade Projetil::getAtirador()
{
  return atirador;
}

Json::Value Projetil::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  entityJson["atirador"] = getAtirador();
  return entityJson;
}