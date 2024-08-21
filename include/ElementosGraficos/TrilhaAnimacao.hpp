#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciadores/Gerenciador_Grafico.hpp"

class TrilhaAnimacao
{
private:
  int animation_index;
  int animation_time;
  int animation_frames;
  int time_before_update;
  int frame_width;
  int frame_height;
  bool should_repeat;
  sf::Sprite sprite;
  const char *animation_path;

public:
  TrilhaAnimacao(int frames, int t, int f_width, int f_height, float sx, float sy, const char *path, bool repeat = true);
  ~TrilhaAnimacao();
  void update();
  void setPosition(int px, int py);
  void setScale(float sx, float sy);
  void desenhar();
  void reset();
  sf::Vector2f getCenter();
  sf::FloatRect getSize();
};