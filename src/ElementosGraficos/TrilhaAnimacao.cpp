#include "ElementosGraficos/TrilhaAnimacao.hpp"

TrilhaAnimacao::TrilhaAnimacao(int frames, int t, int width, int height, int sx, int sy, const char *path) : animation_index(0), animation_time(0), animation_frames(frames), time_before_update(t), animation_path(path), frame_width(width), frame_height(height), scale_x(sx), scale_y(sy)
{
  sf::Texture *tex = Gerenciador_Grafico::getInstance().carregaTextura(animation_path);
  sprite.setTexture(*tex);
  sprite.setTextureRect(sf::IntRect(0, 0, width, height));
  sprite.setScale(scale_x, scale_y);
}

TrilhaAnimacao::~TrilhaAnimacao() {}

void TrilhaAnimacao::update()
{
  animation_time++;
  bool changed = false;
  if ((animation_time / (int)time_before_update) > animation_index)
  {
    animation_index++;
    changed = true;
  }

  if (animation_index > animation_frames)
  {
    reset();
  }

  if (changed)
  {
    sprite.setTextureRect(sf::IntRect(frame_width * animation_index, 0, frame_width, frame_height));
  }
}

void TrilhaAnimacao::setPosition(int px, int py)
{
  sprite.setPosition(px, py);
}

void TrilhaAnimacao::desenhar()
{
  Gerenciador_Grafico::getInstance().drawSprite(sprite);
}

void TrilhaAnimacao::reset()
{
  animation_index = 0;
  animation_time = 0;
}