#ifndef SoldadoChefe_HPP
#define SoldadoChefe_HPP

#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Entidades/Projetil.hpp"

const int SOLDADO_HEIGHT = 128 * 3;

class SoldadoChefe : public Inimigo
{
private:
  int dano_projetil;
  int tirosDisparados;
  int maxTiros;
  void lancarGranada();
  float tempoUltimaGranada;
  int numeroGranadas;
  float tempoDisparo;

public:
  SoldadoChefe(int px, int py, int vidas);
  ~SoldadoChefe();
  void executar();
  void olhar();
  void atacar();
  void danificar(Jogador *pJ);
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
};
#endif // SoldadoChefe_HPP