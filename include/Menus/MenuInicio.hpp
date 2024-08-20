#pragma once

#include "Menu.hpp"

class MenuInicio : public Menu
{
private:
  std::vector<sf::RectangleShape> botoes; // Botões
  std::vector<sf::Text> textos;           // Textos nos botões
  int itemSelecionado;

  void setBotaoTexto(int index, const std::string &texto, sf::Font *fonte);

public:
  MenuInicio();
  ~MenuInicio();
  void moveUp();
  void moveDown();
  int getSelectedItemIndex() const;
  void centralizaTextoNoBotao(sf::Text &texto, const sf::RectangleShape &botao);
  void desenhar();
  void executar();
};