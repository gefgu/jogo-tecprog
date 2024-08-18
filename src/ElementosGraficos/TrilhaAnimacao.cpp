#include "ElementosGraficos/TrilhaAnimacao.hpp"

TrilhaAnimacao::TrilhaAnimacao(int frames, int t, int f_width, int f_height, int f_whitespace, float sx, float sy, const char *path)
    : animation_index(0), animation_time(0), animation_frames(frames), time_before_update(t),
      animation_path(path), frame_width(f_width), frame_height(f_height), frame_whitespace(f_whitespace)
{
  sf::Texture *tex = Gerenciador_Grafico::getInstance().carregaTextura(animation_path);
  sprite.setTexture(*tex);
  sprite.setTextureRect(sf::IntRect(frame_whitespace, 0, (frame_width - frame_whitespace * 2), frame_height));
  sprite.setScale(sx, sy);
  sprite.setOrigin((frame_width - frame_whitespace * 2) / 2.f, frame_height / 2.f); // Define a origem no centro da sprite
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
    sprite.setTextureRect(sf::IntRect(frame_width * animation_index + frame_whitespace, 0, frame_width - frame_whitespace * 2, frame_height));
  }
}

void TrilhaAnimacao::setPosition(int px, int py)
{
  sprite.setPosition(px, py);
}

void TrilhaAnimacao::setScale(float sx, float sy)
{
  sprite.setScale(sx, sy);
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

sf::Vector2f TrilhaAnimacao::getCenter()
{
  sf::FloatRect size = getSize();
  sf::Vector2f origin = sprite.getOrigin();
  return sf::Vector2f(size.left + origin.x, size.top + origin.y);
}

sf::FloatRect TrilhaAnimacao::getSize()
{
  return sprite.getGlobalBounds();
}