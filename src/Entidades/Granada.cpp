#include "Entidades/Granada.hpp"
#include <cmath>

const char *Granada_PATH = "./assets/mina/mina_3.png";

const float GRAVIDADE = 9.8f;    // Aceleração da gravidade (em unidades por segundo^2)
const float TEMPO_FRAME = 0.16f; // Duração de cada frame (em segundos) - para 60 FPS

Granada::Granada(int px, int py, int direcao, tipoDeEntidade p) : Entidade(px, py, tipoDeEntidade::GRANADA),
                                                                  visual(Granada_PATH, false), direcao(direcao), dano(1), velocidadeX(0.2), velocidadeY(-5), atirador(p), forca(7.5f)
{
  visual.setPosition(px, py);
  visual.setTextureRect(sf::IntRect(0, 0, 32, 20));
  visual.setScale(2, 2);
}

Granada::~Granada()
{
}

void Granada::desenhar()
{
  visual.desenhar();
}

void Granada::executar()
{
  float elapsedTime = pGG->getElapsedTime();
  aplicarGravidade();
  x += direcao * elapsedTime * velocidadeX;
  y += velocidadeY;
  visual.setPosition(x, y);
}

sf::Vector2f Granada::getCenter()
{
  return visual.getCenter();
}

sf::FloatRect Granada::getSize()
{
  return visual.getSize();
}

void Granada::aplicarGravidade()
{
  float elapsed_time = pGG->getElapsedTime();
  velocidadeY += 2 * GRAVIDADE * (elapsed_time / 200.0f) / 10.f;
}

void Granada::lidarColisao(sf::Vector2f intersecao, Entidade *other)
{

  if (other == nullptr)
    return;
  else if (other->getTipo() == JOGADOR && !static_cast<Jogador *>(other)->getMorto() && velocidadeX == 0 && velocidadeY == 0)
  {
    auto *jogador = static_cast<Jogador *>(other);
    // Calcular a força de repulsão baseada na interseção
    float forcaX = (intersecao.x < 0) ? forca : -forca;

    // Aplicar a força de repulsão no jogador
    jogador->aplicarForcaRepulsao(forcaX, -std::abs(forca));
    // jogador->recebeDano(dano);
    ativo = false;
  }
  else if (other->getTipo() == tipoDeEntidade::PLATAFORMA)
  {
    if (intersecao.y > 0)
    {
      // Corrige a posição da granada para que ela não atravesse a plataforma
      y -= intersecao.y - 1;

      // Fator de conservação de energia (ajustável)
      float fatorConservacaoEnergia = 0.3f;

      // Calcula a nova velocidade após a perda de energia no impacto
      velocidadeY = -std::sqrt(fatorConservacaoEnergia) * std::abs(velocidadeY);
      velocidadeX = std::sqrt(fatorConservacaoEnergia) * std::abs(velocidadeX);

      // Se a velocidade for muito pequena, pare o movimento
      if (std::abs(velocidadeY) < 2.0f)
      {
        velocidadeY = 0;
        velocidadeX = 0;
      }
    }
  }
}

tipoDeEntidade Granada::getAtirador()
{
  return atirador;
}

Json::Value Granada::gravar()
{
  Json::Value entityJson;

  entityJson["type"] = getTipo();
  entityJson["x"] = getPosition().x;
  entityJson["y"] = getPosition().y;
  entityJson["atirador"] = getAtirador();
  entityJson["direcao"] = direcao;
  return entityJson;
}
