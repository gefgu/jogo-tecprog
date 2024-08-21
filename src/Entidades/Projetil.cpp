#include "Entidades/Projetil.hpp"

const char *PROJETIL_PATH = "./assets/images/bullet.png";

const float GRAVIDADE = 9.8f;    // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f; // Duração de cada frame (em segundos) - para 60 FPS

Projetil::Projetil(int px, int py, int direcao) : Entidade(px, py, tipoDeEntidade::PROJETIL),
                                                  visual(PROJETIL_PATH, false), direcao(direcao), dano(1), velocidadeY(0)
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
  x += direcao * (elapsedTime);
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
  velocidadeY += (GRAVIDADE * TEMPO_FRAME); // Aceleração devido à gravidade
  y += velocidadeY * TEMPO_FRAME / 12.0f;
}

void Projetil::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == tipoDeEntidade::FIGHTER && !static_cast<Fighter *>(other)->getMorto())
  {
    static_cast<Fighter *>(other)->recebeDano(dano);
    ativo = false;
  }

  if (other->getTipo() == tipoDeEntidade::PLATAFORMA)
  {
    ativo = false;
  }
}