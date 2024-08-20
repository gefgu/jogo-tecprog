#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"

class ObjetoEstatico : public Ente
{
private:
  sf::Sprite sprite;
  const char *image_path;

public:
  ObjetoEstatico(const char *path, bool repeat = false);
  ~ObjetoEstatico();
  void setPosition(int px, int py);
  void setScale(float sx, float sy);
  void setTextureRect(sf::IntRect rec);
  void desenhar();
  void executar();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
};