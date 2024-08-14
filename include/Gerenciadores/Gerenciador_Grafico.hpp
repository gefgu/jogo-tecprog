#ifndef GERENCIADOR_GRAFICO_HPP
#define GERENCIADOR_GRAFICO_HPP

// class Ente;
#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Ente;

class Gerenciador_Grafico
{
private:
  sf::RenderWindow window;
  sf::Clock clock;
  float elapsed_time; // since last re-render
  map<const char *, sf::Texture *> texturesMap;

  void updateElapsedTime(); // it updates on the display

public:
  Gerenciador_Grafico();
  ~Gerenciador_Grafico();
  void desenharEnte(Ente *pE);
  void clear();
  void display();
  bool isWindowOpen();
  sf::Texture *carregaTextura(const char *textura_path);
  float getElapsedTime();
  sf::Vector2u getWindowSize() const;
  bool pollEvent(sf::Event &event);
  void fecharJanela();
  sf::RenderWindow &getWindow();
};

#endif // GERENCIADOR_GRAFICO_HPP