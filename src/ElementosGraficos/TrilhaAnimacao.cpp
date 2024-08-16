#include "ElementosGraficos/TrilhaAnimacao.hpp"

TrilhaAnimacao::TrilhaAnimacao(int frames, int t, int width, int height, float sx, float sy, const char *path)
    : animation_index(0), animation_time(0), animation_frames(frames), time_before_update(t),
      animation_path(path), frame_width(width), frame_height(height)
{
  sf::Texture *tex = Gerenciador_Grafico::getInstance().carregaTextura(animation_path);
  sprite.setTexture(*tex);
  sprite.setTextureRect(sf::IntRect(0, 0, width, height));
  sprite.setScale(sx, sy);
  sprite.setOrigin(width / 2.f, height / 2.f); // Define a origem no centro da sprite
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