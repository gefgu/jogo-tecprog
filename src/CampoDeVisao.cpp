#include "CampoDeVisao.hpp"

CampoDeVisao::CampoDeVisao() : pJogador(NULL), visao(sf::Vector2f(500, 300))
{
}

CampoDeVisao::~CampoDeVisao()
{
  pJogador = NULL;
}

sf::Vector2f CampoDeVisao::getCenter()
{
  sf::FloatRect size = getSize();
  return sf::Vector2f(size.left + size.width / 2.0f, size.top + size.height / 2.0f);
}

sf::FloatRect CampoDeVisao::getSize()
{
  return visao.getGlobalBounds();
}

void CampoDeVisao::setPosition(int px, int py)
{
  visao.setPosition(px, py);
}

Jogador *CampoDeVisao::getJogador()
{
  return pJogador;
}

void CampoDeVisao::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == tipoDeEntidade::JOGADOR)
  {
    pJogador = static_cast<Jogador *>(other);
  }
}

void CampoDeVisao::executar() {}

void CampoDeVisao::desenhar() {}