#include "Entidades/Obstaculos/Lixo.hpp"

const char *LIXO_PATH = "./assets/images/lixo.png";

Lixo::Lixo(int px, int py) : Obstaculo(px, py, LIXO_PATH, tipoDeEntidade::LIXO), fator_de_impedimento(2)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 30, LIXO_HEIGHT));
  visual.setScale(3, 3);
}

Lixo::~Lixo()
{
}

void Lixo::executar()
{
}

void Lixo::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == tipoDeEntidade::JOGADOR)
  {
    static_cast<Jogador *>(other)->reduzirVelocidade(fator_de_impedimento);
  }
}