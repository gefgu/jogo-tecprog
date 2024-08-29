#include "Entidades/Obstaculos/Mina.hpp"
#include <cmath>

const char *MINA_PATH = "./assets/mina/mina_3.png";


Mina::Mina(int px, int py) : Obstaculo(px, py, MINA_PATH, tipoDeEntidade::MINA), fator_de_repulsao(7.5f)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 32, MINA_HEIGHT));
  visual.setScale(2, 2);
}

Mina::~Mina()
{
}

void Mina::executar()
{
}

void Mina::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{
  if (other->getTipo() == tipoDeEntidade::JOGADOR)
  {
    Jogador *jogador = static_cast<Jogador *>(other);

    // Calcular a força de repulsão baseada na interseção
    float forcaX = (intersecao.x < 0) ? fator_de_repulsao : -fator_de_repulsao;

    // Aplicar a força de repulsão no jogador
    jogador->aplicarForcaRepulsao(forcaX, -std::abs(fator_de_repulsao)); // Repulsão para cima

    ativo = false;
  }
}

Json::Value Mina::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  return entityJson;
}