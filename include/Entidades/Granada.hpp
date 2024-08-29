#ifndef Granada_HPP
#define Granada_HPP

#include <SFML/Graphics.hpp>
#include "Entidades/Entidade.hpp"
#include "ElementosGraficos/ObjetoEstatico.hpp"
#include "Entidades/Personagens/Fighter.hpp"
#include "Entidades/Personagens/Atirador.hpp"
#include "Entidades/Personagens/SoldadoChefe.hpp"

const int GRANADA_WIDTH = 80;
const int GRANADA_HEIGHT = 64 * 2;
class Granada : public Entidade
{
private:
  ObjetoEstatico visual;
  int dano;
  int direcao;
  float velocidadeY;
  float velocidadeX;
  float forca;
  tipoDeEntidade atirador;
  void aplicarGravidade();

public:
  Granada(int px, int py, int direcao, tipoDeEntidade p); // posição e escala não mudam
  ~Granada();
  void desenhar();
  void executar();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
  void lidarColisao(sf::Vector2f intersecao, Entidade *other);
  tipoDeEntidade getAtirador();
};
#endif // Granada_HPP