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
  int scale_x; // scale
  int scale_y; // scale
  sf::Sprite sprite;
  const char *animation_path;

public:
  TrilhaAnimacao(int frames, int t, int width, int height, int sx, int sy, const char *path);
  ~TrilhaAnimacao();
  void update();
  void setPosition(int px, int py);
  void setScale(float sx, float sy);
  void desenhar();
  void reset();
};