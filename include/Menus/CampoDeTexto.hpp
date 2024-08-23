#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.hpp"

class CampoDeTexto : public Ente
{
private:
  sf::String playerInput;
  sf::Text playerText;
  sf::RectangleShape fundo;

public:
  CampoDeTexto(int px, int py, int width, int height);
  ~CampoDeTexto();
  const char *getTexto();
  void executar();
  void desenhar();
  void receiveEvent(sf::Event event);
  void centralizaTexto();
};