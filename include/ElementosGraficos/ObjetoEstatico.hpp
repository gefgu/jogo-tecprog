#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"

class ObjetoEstatico
{
private:
  sf::Sprite sprite;
  const char *image_path;

public:
  ObjetoEstatico(const char *path);
  ~ObjetoEstatico();
  void setPosition(int px, int py);
  void setScale(float sx, float sy);
  void setTextureRect(sf::IntRect rec);
  void desenhar();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
};