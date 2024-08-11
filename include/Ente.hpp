#ifndef ENTE_HPP
#define ENTE_HPP

#include "Gerenciadores/Gerenciador_Grafico.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Gerenciador_Grafico;

class Ente
{
protected:
  int id;
  static Gerenciador_Grafico *pGG;
  static int cont;
  sf::Sprite sprite;
  sf::Texture textura;
  // Figura *pFig;

  void carregaTextura(string textura_path);

public:
  Ente();
  ~Ente();
  virtual void executar() = 0;
  void desenhar();
  static void setGerenciadorGrafico(Gerenciador_Grafico *pGerenciador);
  sf::Sprite getSprite();
};

#endif // ENTE_HPP