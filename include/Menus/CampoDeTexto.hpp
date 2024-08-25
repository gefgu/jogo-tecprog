#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.hpp"
#include "Controladores/Observer.hpp"
#include "Gerenciadores/Gerenciador_Input.hpp"

class CampoDeTexto : public Ente, Observer
{
private:
  sf::String playerInput;
  std::string playerInputStr;
  sf::Text playerText;
  sf::RectangleShape fundo;
  Gerenciador_Input &_gerenciadorInput;

public:
  CampoDeTexto(int px, int py, int width, int height);
  ~CampoDeTexto();
  const char *getTexto();
  void executar();
  void desenhar();
  void centralizaTexto();
  void Update(const char *teclaPressionada);
};