#include "Entidades/Obstaculos/Mina.hpp"
#include <cmath>

const char *MINA_PATH = "./assets/images/lixo.png";

Mina::Mina(int px, int py) : Obstaculo(px, py, MINA_PATH, tipoDeEntidade::MINA), fator_de_repulsao(100.0f)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 30, MINA_HEIGHT));
  visual.setScale(3, 3);
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
        float forcaX = (intersecao.x > 0) ? fator_de_repulsao : -fator_de_repulsao;

        // Aplicar a força de repulsão no jogador
        jogador->aplicarForcaRepulsao(forcaX, -std::abs(fator_de_repulsao)); // Repulsão para cima

        ativo = false;
    }
}