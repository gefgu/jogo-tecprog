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
  Gerenciador_Grafico();    // Singleton
  ~Gerenciador_Grafico();   // Singleton

  // Delete copy constructor and assignment operator to prevent copying
  Gerenciador_Grafico(const Gerenciador_Grafico &) = delete;
  Gerenciador_Grafico &operator=(const Gerenciador_Grafico &) = delete;

public:
  static Gerenciador_Grafico &getInstance()
  {
    static Gerenciador_Grafico instance;
    return instance;
  }
  // void desenharEnte(Ente *pE);
  void clear();
  void display();
  bool isWindowOpen();
  sf::Texture *carregaTextura(const char *textura_path);
  float getElapsedTime();
  sf::Vector2u getWindowSize() const;
  bool pollEvent(sf::Event &event);
  void fecharJanela();
  sf::RenderWindow &getWindow();
  void drawSprite(sf::Sprite s);
  void renderizar();
};

#endif // GERENCIADOR_GRAFICO_HPP