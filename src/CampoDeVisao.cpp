#include "CampoDeVisao.hpp"

const int WIDTH = 1000;
const int HEIGHT = 300;

CampoDeVisao::CampoDeVisao() : Entidade(0, 0, tipoDeEntidade::VISAO), pJogador(NULL), visao(sf::Vector2f(WIDTH, HEIGHT))
{
  visao.setOrigin(WIDTH / 2.f, HEIGHT / 2.f);
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
  x = px;
  y = py;
  // cout << x << ", " << y << endl;
  // cout << getCenter().x << ", " << getCenter().y << endl;
  visao.setPosition(x, y);
}

Jogador *CampoDeVisao::getJogador()
{
  if (pJogador != NULL && pJogador->getMorto())
    pJogador = NULL;
  return pJogador;
}

void CampoDeVisao::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == tipoDeEntidade::JOGADOR && !static_cast<Jogador *>(other)->getMorto())
  {
    // cout << "JOGADOR AVISTADO: (" << intersecao.x << ", " << intersecao.y << ")" << endl;
    pJogador = static_cast<Jogador *>(other);
  }
}

void CampoDeVisao::executar() {}

void CampoDeVisao::desenhar()
{
  visao.setFillColor(sf::Color::Red);
  pGG->draw(visao);
}