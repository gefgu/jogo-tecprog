#ifndef ENTE_HPP
#define ENTE_HPP

#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include <SFML/Graphics.hpp>

class Gerenciador_Grafico;

class Ente
{
protected:
  int id;
  // sf::Sprite sprite;
  static Gerenciador_Grafico *pGG;
  static int cont;
  // Figura *pFig;

public:
  Ente();
  ~Ente();
  virtual void executar() = 0;
  void desenhar();
  static void setGerenciadorGrafico(Gerenciador_Grafico *pGerenciador);
  // sf::Sprite getSprite();
};

#endif // ENTE_HPP