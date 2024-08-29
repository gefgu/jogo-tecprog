#ifndef ATIRADOR_HPP
#define ATIRADOR_HPP

#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Entidades/Projetil.hpp"

const int ATIRADOR_HEIGHT = 128 * 3;

class Atirador : public Inimigo
{
private:
  int dano_projetil;
  float tempoDisparo;

public:
  Atirador(int px, int py, int vidas);
  ~Atirador();
  void executar();
  void olhar();
  void atacar();
  void danificar(Jogador *pJ);
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};
#endif // ATIRADOR_HPP